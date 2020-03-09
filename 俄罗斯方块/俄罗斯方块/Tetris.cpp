#pragma once
#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "Tetris.h"

using namespace std;



//欢迎界面
void Welcome() {
	//初始化界面
	initgraph(550, 660);
	HWND windows = GetHWnd();
	SetWindowText(windows, _T("Classical Tetris"));
	//在窗口中显示欢迎界面的说明
	setcolor(WHITE);
	settextstyle(30, 0, _T("楷体"));
	outtextxy(205, 200, _T("俄罗斯方块"));
	outtextxy(175, 300, _T("你能得到1000分吗?"));
	Sleep(3000);
}
//初始化游戏界面
void initGameScene() {
	char str[16];
	cleardevice();
	
	rectangle(27, 27, 336, 635);
	rectangle(29, 29, 334, 633);
	rectangle(370, 50, 515, 195);

	settextcolor(LIGHTGRAY);
	settextstyle(24, 0, _T("微软雅黑"));
	outtextxy(405, 215, _T("下一个:"));

	settextcolor(RED);
	outtextxy(405, 280, _T("分数:"));
	sprintf_s(str, "%d", Rank);
	outtextxy(415, 310, str);
	outtextxy(405, 375, _T("等级:"));
	sprintf_s(str, "%d", Score);
	outtextxy(425, 405, str);

	settextcolor(LIGHTBLUE);
	outtextxy(390, 475, _T("操作说明:"));
	outtextxy(390, 500, _T("↑: 旋转"));
	outtextxy(390, 525, _T("↓: 下降"));
	outtextxy(390, 550, _T("←: 左移"));
	outtextxy(390, 575, _T("→: 右移"));
	outtextxy(390, 600, _T("空格: 暂停"));
	Sleep(1000);
}
//清除右上角方框内的内容
void clearBlock(void) {
	settextcolor(BLACK);
	settextstyle(23, 0, "正楷");
	for(int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			//■int x = 391, y = 71;
			outtextxy(391 + j * UNIT_SIZE, 71 + i * UNIT_SIZE, "■");
		}
	}
}
//清除指定位置的方块（给定方块样式是为了加快效率，即不需要在黑背景处绘制黑方块）
void clearBlock(int x, int y, _Block_Dir direct) {
	int tmp = CurrentIndex * 4 + direct;
	
	settextcolor(BLACK);
	settextstyle(23, 0, "正楷");
	for (int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			//■
			if (block[tmp][i][j] == 1) {
				outtextxy(x + j * UNIT_SIZE, y + i * UNIT_SIZE, "■");
			}
		}
	}
}
//在右上角方框中画出新方块样式
void drawBlock(int x, int y) {
	settextcolor(Color[NextIndex]);
	settextstyle(23, 0, "正楷");
	for (int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			//■
			if (block[NextIndex * 4][i][j] == 1) {
				outtextxy(x + j * UNIT_SIZE, y + i * UNIT_SIZE, "■");
			}
		}
	}
}
//在给定的位置画出指定样式的方块
void drawBlock(int x, int y, _Block_Dir direct) {

	int tmp = CurrentIndex * 4 + direct;
	
	settextcolor(Color[CurrentIndex]);
	settextstyle(23, 0, "正楷");
	for (int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			//■
			if (block[tmp][i][j] == 1) {
				outtextxy(x + j * UNIT_SIZE, y + i * UNIT_SIZE, "■");
			}
		}
	}
}
//在右上角显示新的方块
void nextBlock() {
	int x = 391, y = 71;
	//清楚方框内容
	clearBlock();
	//在方框中画出下一个方块的图样
	
	srand(time(NULL));
	NextIndex = rand() % BLOCK_KIND;
	
	drawBlock(x,y);

}
//判断能否向特定方向移动
bool Movable(int x, int y, _Block_Dir b_Dir, _Move_Dir m_Dir) {
	//当前块左上角所在的行和列
	int Row    = (y - MIN_Y) / UNIT_SIZE;
	int Column = (x - MIN_X) / UNIT_SIZE;
	//行和列的偏移量
	int change_R = 0, change_C = 0;
	int tmp = CurrentIndex * 4 + b_Dir;
	switch (m_Dir) {
		case MOVE_DOWN:
			change_C = 1;
			break;
		case MOVE_LEFT:
			change_R = -1;
			break;
		case MOVE_RIGHT:
			change_R = 1;
			break;
	}
	//如果移动，移动之后行和列的边界
	int changed_Column = 0, changed_Row = 0;
	for (int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			changed_Row = Row + i + change_C;
			changed_Column = Column + j + change_R;
			if (block[tmp][i][j] == 1 &&
				((!isValid(changed_Row, changed_Column))||
				((isValid(changed_Row, changed_Column) && 
				  Gamearea[changed_Row][changed_Column] == 1)))) {
				return false;
				
			}
		}
	}
	return true;
}
//检测游戏是否结束
void EndCheck() {
	if (!Movable(START_X, START_Y, UP, MOVE_DOWN)) {
		settextcolor(WHITE);
		settextstyle(45, 0, "Arial");
		outtextxy(75, 300, "Game Over");
		system("pause");
		closegraph();
		exit(0);
	}
}
//方块降落
void Move() {
	int x = START_X, y = START_Y;
	_Block_Dir block_direct = UP;
	//先检测游戏是否结束
	EndCheck();

	int i = 0, j = 0;
	while (1) {
		//先判断能否暂停是为了提高暂停的优先级
		if (_kbhit()) {
			int key = _getch();
			if (key == KEY_SPACE) {
				int i = _getch();
			}
		}
		//清除现在位置的方块
		clearBlock(x + j * UNIT_SIZE, y + i * UNIT_SIZE, block_direct);
		if (_kbhit()) {
			int key = _getch();
			if (key == KEY_UP) {
				//block_direct
			}
			else if (key==KEY_LEFT) {
				if (Movable(x + j * UNIT_SIZE, y + i * UNIT_SIZE, block_direct, MOVE_LEFT)) {
					j--;
				}
			}
			else if (key == KEY_DOWN) {

				i += 2;
			}
			else if (key == KEY_RIGHT) {
				if (Movable(x + j * UNIT_SIZE, y + i * UNIT_SIZE, block_direct, MOVE_RIGHT)) {
					j++;
				}
			}
		}
		if (Movable(x + j * UNIT_SIZE, y + i * UNIT_SIZE, block_direct, MOVE_DOWN)) {
			i++;
		}
		drawBlock(x + j * UNIT_SIZE, y + i * UNIT_SIZE, block_direct);
		Sleep(300);
		//等待  to do。。。
		
	}
}
//游戏主要的函数
void newBlock() {
	//改变当前方块为即将要降落的方块
	CurrentIndex = NextIndex;
	//绘制从顶部下降的方块
	drawBlock(START_X, START_Y);
	//暂停以便让玩家识别新方块
	Sleep(100);
	//右上角变换方块
	nextBlock();
	//方块降落
	Move();

}
int main() {
	//开始前的准备
	Welcome();
	initGameScene();
	nextBlock();
	memset(Gamearea, 0, sizeof(Gamearea));//初始化游戏区域
	Sleep(500);//缓冲时间1秒
	//游戏主体 死循环
	while (1) {
		newBlock();
	}

	//system("pause");
	//closegraph();
	return 0;
}