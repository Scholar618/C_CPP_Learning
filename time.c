#include <stdio.h>
#include <time.h>

int main() {
    // 获取当前时间的时间戳
    time_t newTime;
    time(&newTime);

    // 将时间戳转换格式
    struct tm* localTime = localtime(&newTime);
    char timeString[20];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", localTime);
    printf("当前系统时间：%s\n", timeString);
    
}
