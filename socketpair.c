#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>

int main(){
    int sv[2]; //存2个套接字描述符
    char buf[1024]={0};
    ssize_t len;

    // 创建socket
    if(socketpair(AF_LOCAL,SOCK_STREAM,0,sv) == -1){
        perror("socketpair");
        exit(1);
    }

    //send
    const char *msg = "send test message";
    printf("%d\n",sizeof(msg));
    if(write(sv[0],msg,strlen(msg)) == -1){
        perror("write");
        exit(1);
    }

    printf("buf size is %d\n",sizeof(buf));
    //recv
    if((len = read(sv[1],buf,sizeof(buf)-1)) == -1){
        perror("read");
        exit(1);
    }
    buf[len] = '\0';  // 加上字符串结束符
    printf("recv: %s\n",buf);

    close(sv[0]);
    close(sv[1]);

    return 0;

}