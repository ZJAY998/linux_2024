#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<string.h>
//epoll 特点
//1.可以有效的处理大量的文件描述符  不会因为监视的描述符数量增加而导致性能下降 时间复杂度O(log n)

//2.高效的事件通知机制  使用了事件就绪通知机制，epoll wait 函数堵塞等待事件发生 不像select 和 poll 那样需要轮询所有文件的文件描述符 可以避免轮询的开销 当实践发生才能唤醒

//3.支持边缘触发   epoll提供水平触发和边缘触发  边缘触发只在状态变化时通知应用程序
//相比水平触发可以减少事件的通知次数 减轻cpu负载 提升效率

//4.零拷贝技术支持
//系统调用像splice和tee 系统调用 能够直接在内核中移动数据 无需在用户空间和内核空间复制数据 从而提高了数据传输的效率和性能

//5.资源占用比较少
//监听大量文件描述符号时，占用的系统资源较少，内核消耗和cpu使用相对较低，能够有效的支持高并发的网络场景。

#define MAX_EVENTS 10

int main(){

    int epfd, nfds;
    struct epoll_event ev,events[MAX_EVENTS];
    char buf[1024]={0};

    //create epoll
    epfd = epoll_create(1);// contain 2 (0 1)
    if(epfd == -1){
        perror("epoll create error");
	exit(EXIT_FAILURE);
    }

    // 监听标准输入的可读事件
    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO;
    /*
     *  epoll_ctl 函数用于控制 epoll 实例中的文件描述符。通过 op 参数指定操作类型：
        EPOLL_CTL_ADD：向 epoll 实例中添加文件描述符 fd。
        EPOLL_CTL_MOD：修改已经添加的文件描述符 fd 的事件 event。
        EPOLL_CTL_DEL：从 epoll 实例中删除文件描述符 fd。
        event 参数指定关注的事件类型，例如 EPOLLIN（可读事件）、EPOLLOUT（可写事件）等。
    */
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&ev) == -1){
        perror("epoll_ctl: stdin");
	exit(EXIT_FAILURE);
    }
    
    while(1){
    /*
     *     epoll_wait 函数阻塞等待注册在 epoll 实例中的文件描述符上发生的事件。
           maxevents 参数指定 events 数组的大小，即最多可以返回多少个事件。
           timeout 参数指定等待的超时时间，单位为毫秒（如果为 -1 则无限等待）。
           函数返回时，将返回已经发生的事件数量，并将事件信息存储在 events 数组中。

	   struct epoll_event {
           uint32_t events;   // 发生的事件类型
           epoll_data_t data; // 用户数据，通常是一个指针
	   };
     */
        nfds = epoll_wait(epfd,events,MAX_EVENTS,-1);
        if(nfds == -1){
	    perror("epoll wait");
	    exit(EXIT_FAILURE);
	}
    
	for(int i = 0; i < nfds; i++){
	    if(events[i].data.fd == STDIN_FILENO){
	        //从标准输入读取数据
		int nbytes = read(STDIN_FILENO, buf,sizeof(buf));
	        if(nbytes == -1){
		    perror("read nbytes");
		}else if (nbytes == 0){
		    printf("EOF\n");
		    exit(EXIT_FAILURE);
		}else{
		    printf("Read %d bytes %s\n",nbytes,buf);
		    memset(buf, 0, sizeof(buf));
		}
	    }
	}
    }

    close(epfd);
    return 0;
}
