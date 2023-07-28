/*int fprintf(FILE *stream, const char *format, ...);*/
#include <stdio.h>

int main(void) {
    FILE *fp;
    int num1 = 20, num2 = 30;
    float f1 = 3.14;

    fp = fopen("output.txt", "w");
    if(fp == NULL) {
        printf("Failed to open file!\n");
        return -1;
    }
    
    fprintf(fp, "num1=%d, num2=%d, f1=%f\n", num1, num2, f1);
    fclose(fp);
    return 0;
}
