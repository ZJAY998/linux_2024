#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
  return 0;
}