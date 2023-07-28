/*
 * stderr是标准错误输出流
 * 用于将错误消息和其他诊断信息输出到控制台或日志文件中
 * 错误消息会立即输出到控制台或日志文件中
 * 而不需要等待缓冲区满或手动刷新。
 * */
#include <stdio.h>

int main(void) {
    FILE *fp;
    int num1 = 0, num2 = 20;

    if(num1 == 0) {
        fprintf(stderr, "Error: division is zero!\n");
        return -1;
    }

    printf("Result : %d\n", num2 / num1);
    return 0;
}
