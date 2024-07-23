#include<stdio.h>
#include<time.h>
/*
1.time_t 表示1970年1月1号0时0秒以来的秒数
time_t now = time(NULL);
time_t now;
time(&now);

2.struct tm 结构体
#include <time.h>
struct tm {
int tm_sec; //秒 – 取值区间为[0,59]
int tm_min; //分 - 取值区间为[0,59]
int tm_hour; //时 - 取值区间为[0,23]
int tm_mday; //一个月中的日期 - 取值区间为[1,31]
int tm_mon; //月份（从一月开始，0代表一月） - 取值区间为[0,11]
int tm_year; //年份，其值等于实际年份减去1900
int tm_wday; //星期 – 取值区间为[0,6]，其中0代表星期天，1代表星期一，以此类推
int tm_yday; //从每年的1月1日开始的天数 – 取值区间为[0,365]，其中0代表1月1日，1代表1月2日，以此类推
int tm_isdst; //夏令时标识符，实行夏令时的时候，tm_isdst为正。不实行夏令时的进候，tm_isdst为0;不了解情况时，tm_isdst()为负
};


struct tm 结构体通常由 gmtime, localtime, mktime 等时间函数返回。
3.获取微秒级时间精度
#include <sys/time.h>
#include <unistd.h>
int gettimeofday(struct timeval *tv ,struct timezone *tz);


 */


int main(){

    struct tm result;
    struct tm *gmt;
    time_t     fix_time;
    
    //time_t now = time(NULL);
    time_t now;
    time(&now);
    
    
    //gmt = gmtime_r(&now,&result);
    //gmt = gmtime(&now);//time 秒类型转为tm 结构体类型
    gmt = localtime(&now);
  
    //格林威治时间（GMT，即UTC）  东八区+8
    if(gmt!=NULL){
       printf("time is %d-%02d-%02d %02d:%02d:%02d\n",gmt->tm_year+1900,gmt->tm_mon+1,gmt->tm_mday,
       gmt->tm_hour,gmt->tm_min,gmt->tm_sec);
    }else{
        printf("failed to get time");
    }

    fix_time = timegm(&now);

    return 0;
}