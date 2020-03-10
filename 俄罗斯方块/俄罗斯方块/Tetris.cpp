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
	outtextxy(195, 250, _T("你能在这里"));
	outtextxy(175, 300, _T("得到1000分吗?"));
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
	sprintf_s(str, sizeof(str), "%d", Rank);
	outtextxy(415, 310, str);
	outtextxy(405, 375, _T("等级:"));
	sprintf_s(str, sizeof(str), "%d", Score);
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
			if (block[tmp][i][j]) {
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
			if (block[NextIndex * 4][i][j]) {
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
			if (block[tmp][i][j]) {
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
	
	srand((int)time(NULL));
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
			if (block[tmp][i][j] &&
				((!isValid(changed_Row, changed_Column)) ||
				(isValid(changed_Row, changed_Column) &&
					Gamearea[changed_Row][changed_Column] == 1))) {
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
bool rotatable(int x, int y, _Block_Dir Dir) {
	int tmp = CurrentIndex * 4 + Dir;
	int x0 = (y - START_Y) / UNIT_SIZE;
	int y0 = (x - START_X) / UNIT_SIZE;
	if (!Movable(x, y, Dir, MOVE_DOWN)) {
		return false;
	}
	for (int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			if (block[tmp][i][j] &&
				(/*y0 + j < 0 || y0 + j >= 15 || */Gamearea[x0 + i][y0 + j] == 1)) {
				return false;
			}
		}
	}
	return true;
}
//固定方块
void mark(int x, int y, _Block_Dir Dir) {
	int x0 = (x - MIN_X) / UNIT_SIZE;
	int y0 = (y - MIN_Y) / UNIT_SIZE;
	int tmp = CurrentIndex * 4 + Dir;
	for (int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			if (block[tmp][i][j] ) {
				Gamearea[y0 + i][x0 + j] = 1;
				areaColor[y0 + i][x0 + j] = Color[CurrentIndex];
			}
		}
	}
	settextcolor(Color[CurrentIndex]);
	settextstyle(23, 0, "正楷");
	for (int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			//■
			if (block[tmp][i][j]) {
				outtextxy(x + j * UNIT_SIZE, y + i * UNIT_SIZE, "■");
			}
		}
	}
}
//等待延时函数
void wait(int speed) {
	if (speed < 0)speed = 50;
	int count = speed / TIME_INTERVAL;
	for (int n = 0; n < count; n++) {
		Sleep(TIME_INTERVAL);
		if (_kbhit()) {
			return;
		}
	}
}
//方块降落
void Move() {
	int x = START_X, y = START_Y;
	int curSpeed = dropSpeed;//保证每次方块刚生成的降落速度一致
	_Block_Dir block_direct = UP;
	//先检测游戏是否结束
	EndCheck();

	int i = 0, j = 0;
	while (1) {
		//先判断能否暂停是为了提高暂停的优先级
		if (_kbhit()) {
			int key = _getch();
			if (key == KEY_SPACE) {
				int x = _getch();
			}
		}
		//清除现在位置的方块
		clearBlock(x + i * UNIT_SIZE, y + j * UNIT_SIZE, block_direct);
		if (_kbhit()) {
			int key = _getch();
			if (key == KEY_UP) {
				_Block_Dir next_Dir = (_Block_Dir)((block_direct + 1) % 4);
				if (rotatable(x + i * UNIT_SIZE, y + j * UNIT_SIZE, next_Dir)) {
					block_direct = next_Dir;
				}
			}
			else if(key == KEY_LEFT) {
				if (Movable(x + i * UNIT_SIZE, y + j * UNIT_SIZE, block_direct, MOVE_LEFT)) {
					i--;
				}
			}
			else if (key == KEY_DOWN) {
				curSpeed -= 5 * TIME_INTERVAL;
			}
			else if (key == KEY_RIGHT) {
				if (Movable(x + i * UNIT_SIZE, y + j * UNIT_SIZE, block_direct, MOVE_RIGHT)) {
					i++;
				}
			}
				
				
		}
		j++;
		
		
		drawBlock(x + i * UNIT_SIZE, y + j * UNIT_SIZE, block_direct);
		
		//根据降落速度进行等待
		wait(curSpeed);
		//固化处理
		if (!Movable(x + i * UNIT_SIZE, y + j * UNIT_SIZE, block_direct, MOVE_DOWN)) {
			mark(x + i * UNIT_SIZE, y + j * UNIT_SIZE, block_direct);
			return;
		}
		
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
//清除某一行并让上面数行降落一行
void clearLine(int x) {
	for (int i = x; i >= 0; i--) {
		for (int j = 0; j < 15; j++) {
			if (Gamearea[i - 1][j]) {
				Gamearea[i][j] = Gamearea[i - 1][j];
				areaColor[i][j] = areaColor[i - 1][j];
				setcolor(areaColor[i][j]);
				outtextxy(j * UNIT_SIZE + MIN_X, i * UNIT_SIZE + MIN_Y, "■");
			}
			else {
				Gamearea[i][j] = 0;
				areaColor[i][j] = BLACK;
				setcolor(BLACK);
				outtextxy(j * UNIT_SIZE + MIN_X, i * UNIT_SIZE + MIN_Y, "■");
			}
		}
	}
	for (int j = 0; j < 15; j++) {
		Gamearea[0][j] = 0;
		areaColor[0][j] = BLACK;
		setcolor(BLACK);
		outtextxy(j * UNIT_SIZE + MIN_X, MIN_Y, "■");
	}

}
//更新分数
void updateScore(int count) {
	char str[32];
	Score += count * 10;

	setcolor(RED);
	settextstyle(24, 0, _T("微软雅黑"));
	sprintf_s(str, sizeof(str), "%d", Score);
	outtextxy(415, 310, str);
}
//更新等级并加速下落
void upgradeRank() {
	char str[32];
	Rank = Score / 100;
	dropSpeed = 500 - Rank * 80;
	if (dropSpeed <= 100) {
		dropSpeed = 100;
	}

	setcolor(RED);
	settextstyle(24, 0, _T("微软雅黑"));
	sprintf_s(str, sizeof(str), "%d", Rank);
	outtextxy(425, 405, str);
}
//判断能否消除某一行
void clearCheck() {
	int i = 0, j = 0;
	int cleared_Line = 0;
	for (i = 29; i >= 0; i--) {
		for (j = 0; j < 15 && Gamearea[i][j]; j++);
		if (j >= 15) {
			clearLine(i);
			cleared_Line++;
			i++;
		}
	}
	updateScore(cleared_Line);//更新分数
	if (cleared_Line > 0) {
		upgradeRank();//更新等级并加速下落
	}
}
int main() {
	//开始前的准备
	Welcome();
	initGameScene();
	nextBlock();
	memset(Gamearea, 0, sizeof(Gamearea));//初始化游戏区域
	memset(areaColor,BLACK, sizeof(Gamearea));
	Sleep(500);//缓冲时间1秒
	//游戏主体 死循环
	while (1) {
		newBlock();
		clearCheck();
	}

	//system("pause");
	//closegraph();
	return 0;
}