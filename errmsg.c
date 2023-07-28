#include <stdio.h>
#include <stdlib.h>

// 反斜线符号被用来将一行代码分成多行，以提高代码的可读性。
#define ERR_MSG(msg) do{\ 
    fprintf(stderr, "__%d__:", __LINE__);\
    perror(msg);\
}while(0)

int main() {
    FILE* fp = fopen("nonexistent.txt", "r");
    if (fp == NULL) {
        ERR_MSG("Failed to open file");
        exit(EXIT_FAILURE);
    }
    // 执行文件操作...
    fclose(fp);
    return 0;
}

