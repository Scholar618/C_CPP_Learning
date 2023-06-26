#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>

// 存放12张图片
IMAGE img[12];

// 定义图片
int imgIndex[12] = { 0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };

// 循环变量遍历
int i, j;

// 加载资源
void loadResource() {
	for (i = 0; i < 12; i++) {
		//批量加载
		//加入名字
		char filename[20] = "";
		sprintf(filename, "%d.bmp", imgIndex[i]);
		loadimage(img + i, filename);
	}
}

// 定义一个4×4的地图格式
int map[4][4] = { 0 };

// 设置背景
void drawMap() {
	setbkcolor(RGB(244, 215, 215)); //设置颜色
	cleardevice(); //刷新文字颜色
	settextcolor(WHITE); //设置字体颜色
	settextstyle(35, 0, "楷体"); //设置文字格式
	outtextxy(50, 10, "2048游戏"); //输出文字

	// 根据二维数组的值贴图片
	int x, y, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			x = 60 * j;
			y = 60 * i + 60;
			// 求出贴哪一张图片
			for (k = 0; k < 12; k++) {
				if (imgIndex[k] == map[i][j]) {
					break;
				}
			}
			//贴相应图片
			putimage(x, y, img + k);
		}
	}
}

// 随机生成数字
void randIntNum() {
    int i, j, count = 0;
    int empty[16][2];    //用于存储空白位置的数组
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (map[i][j] == 0) {    //如果该位置上的数字为0，则认为该位置为空白位置
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }
        }
    }
    if (count == 0)    //如果没有空白位置，则不需要生成数字
        return;
    int index = rand() % count;    //在空白位置中随机选择一个位置
    int x = empty[index][0];
    int y = empty[index][1];
    map[x][y] = rand() % 2 ? 2 : 4;    //在选定的位置上生成一个数字（2或4）
}


int moveRight() {
	int row, col, flag = 0, i, j;
	for (row = 0; row < 4; row++) {
		//将非0元素移到右侧
		for (i = 3; i > 0; i--) {
			if (map[row][i] == 0) {
				for (j = i - 1; j >= 0; j--) {
					if (map[row][j] != 0) {
						map[row][i] = map[row][j];
						map[row][j] = 0;
						flag = 1;
						break;
					}
				}
			}
		}
		//合并相同元素
		for (col = 3; col > 0; col--) {
			if (map[row][col] == map[row][col - 1]) {
				map[row][col] += map[row][col - 1];
				map[row][col - 1] = 0;
				flag = 1;
			}
		}
		//再次将非0元素移到右侧
		for (i = 3; i > 0; i--) {
			if (map[row][i] == 0) {
				for (j = i - 1; j >= 0; j--) {
					if (map[row][j] != 0) {
						map[row][i] = map[row][j];
						map[row][j] = 0;
						flag = 1;
						break;
					}
				}
			}
		}
	}
	if (flag)
		return 0;
	else
		return 4;
}

int moveLeft() {
	int row, col, flag = 0, i, j;
	for (row = 0; row < 4; row++) {
		//将非0元素移到左侧
		for (i = 0; i < 3; i++) {
			if (map[row][i] == 0) {
				for (j = i + 1; j <= 3; j++) {
					if (map[row][j] != 0) {
						map[row][i] = map[row][j];
						map[row][j] = 0;
						flag = 1;
						break;
					}
				}
			}
		}
		//合并相同元素
		for (col = 0; col < 3; col++) {
			if (map[row][col] == map[row][col + 1]) {
				map[row][col] += map[row][col + 1];
				map[row][col + 1] = 0;
				flag = 1;
			}
		}
		//再次将非0元素移到左侧
		for (i = 0; i < 3; i++) {
			if (map[row][i] == 0) {
				for (j = i + 1; j <= 3; j++) {
					if (map[row][j] != 0) {
						map[row][i] = map[row][j];
						map[row][j] = 0;
						flag = 1;
						break;
					}
				}
			}
		}
	}
	if (flag)
		return 0;
	else
		return 4;
}

int moveUp() {
	int row, col, flag = 0, i, j;
	for (col = 0; col < 4; col++) {
		//将非0元素移到上侧
		for (i = 0; i < 3; i++) {
			if (map[i][col] == 0) {
				for (j = i + 1; j <= 3; j++) {
					if (map[j][col] != 0) {
						map[i][col] = map[j][col];
						map[j][col] = 0;
						flag = 1;
						break;
					}
				}
			}
		}
		//合并相同元素
		for (row = 0; row < 3; row++) {
			if (map[row][col] == map[row + 1][col]) {
				map[row][col] += map[row + 1][col];
				map[row + 1][col] = 0;
				flag = 1;
			}
		}
		//再次将非0元素移到上侧
		for (i = 0; i < 3; i++) {
			if (map[i][col] == 0) {
				for (j = i + 1; j <= 3; j++) {
					if (map[j][col] != 0) {
						map[i][col] = map[j][col];
						map[j][col] = 0;
						flag = 1;
						break;
					}
				}
			}
		}
	}
	if (flag)
		return 0;
	else
		return 4;
}

int moveDown() {
	int row, col, flag = 0, i, j;
	for (col = 0; col < 4; col++) {
		//将非0元素移到下侧
		for (i = 3; i > 0; i--) {
			if (map[i][col] == 0) {
				for (j = i - 1; j >= 0; j--) {
					if (map[j][col] != 0) {
						map[i][col] = map[j][col];
						map[j][col] = 0;
						flag = 1;
						break;
					}
				}
			}
		}
		//合并相同元素
		for (row = 3; row > 0; row--) {
			if (map[row][col] == map[row - 1][col]) {
				map[row][col] += map[row - 1][col];
				map[row - 1][col] = 0;
				flag = 1;
			}
		}
		//再次将非0元素移到下侧
		for (i = 3; i > 0; i--) {
			if (map[i][col] == 0) {
				for (j = i - 1; j >= 0; j--) {
					if (map[j][col] != 0) {
						map[i][col] = map[j][col];
						map[j][col] = 0;
						flag = 1;
						break;
					}
				}
			}
		}
	}
	if (flag)
		return 0;
	else
		return 4;
}

// 获取用户的按键
void keyDown() {
	char key = _getch(); //用来接收用户的按键
	switch (key) {
	case 'W':
	case 'w':
	case 72:	//小键盘的上
		randIntNum();
		moveUp();
		drawMap();
		break;
	case 'S':
	case 's':
	case 80:	//小键盘的下
		randIntNum();
		moveDown();
		drawMap();
		break;
	case 'A':
	case 'a':
	case 75:	//小键盘的左
		randIntNum();
		moveLeft();
		drawMap();
		break;
	case 'D':
	case 'd':
	case 77:	//小键盘的右
		randIntNum();
		moveRight();
		drawMap();
		break;
	}

}



int main() {

	// 程序显示图片
	loadResource();
	initgraph(60*4, 60*5);
	drawMap();
	while (1) {
		keyDown();
		drawMap();
	}
	// 初始化图形窗口，并设置大小
	// 声明图片变量
	// 加载图片资源到loadImage中
	// putImage显示图片
	//initgraph(800, 400);
	IMAGE background;
	//loadimage(&background, "./rec.jpg", 800, 400);
	//putimage(0, 0, &background);
	
	
	// 避免闪屏
	getchar();
	closegraph();
	system("pause");
	return 0;
}
