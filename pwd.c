/*
* 在Linux系统中，终端下输入密码时，将密码隐藏，用字符'*'代替
*/
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define MAX 20

int main(void)
{
	char pwd[MAX+1];
	int i = 0;
	char ch;

	// 禁用终端回显和行缓冲
	struct termios old_term, new_term;
	tcgetattr(STDIN_FILENO, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ECHO | ICANON); // 禁用回显和行缓冲两个属性
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

	printf("Enter password : ");

	while((ch = getchar()) != '\n' && i < MAX) {
		pwd[i++] = ch;
		printf("*");
	}

	pwd[i] = '\0';

	printf("\nYour password is %s\n", pwd);

	// 恢复终端属性
	tcsetattr(STDIN_FILENO, TCSANOW,&old_term);
	
	return 0;
}
