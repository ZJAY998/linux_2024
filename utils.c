#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h>
static double
str2float(const char *p){
    const char *str = "3.14159111 This is some text";
    char *endptr = "some";
    double num;

    num = strtod(str, &endptr);

    if (endptr == str) {
        printf("没有找到有效的浮点数。\n");
    } else {
        printf("转换后的数字为: %f\n", num);
        printf("剩余的字符串部分为: %s\n", endptr);
    }

    return num;
}




int main(){
  printf("---------\n");
  double d1 = str2float("ttest1");
  printf("d1 is %lf \n",d1);


  unsigned char x = 0x3A;
  printf("get ~x is %02X\n",(unsigned char)~x);



  /*make fd non-blocking 
  F_GETFL: 获取文件状态标志。
  F_SETFL: 设置文件状态标志。
  F_GETFD: 获取文件描述符标志。
  F_SETFD: 设置文件描述符标志。
  F_GETLK, F_SETLK, F_SETLKW: 获取或设置文件锁定状态。
  设置文件状态属性*/
  int fd;
  int flags = fcntl(fd,F_GETFL);
  fcntl(fd,F_SETFL,flags | O_NONBLOCK);


  return 0;
}