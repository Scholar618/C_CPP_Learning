/* 使用'\0'分离字符串 */
#include <string.h>
#include <stdio.h>

int main(void) {
    char str[20] = "Hello World!!";
    char *p = str;
    char str1[10], str2[10];
    // 分割字符串
    while (1)
    {
        if(*p == ' ') {
            *p = '\0';
            strcpy(str1, str);
            strcpy(str2, p+1);
            break;
        }
        p++;
    }
    printf("str1 = %s\n", str1);
    printf("str2 = %s\n", str2);
    
}
