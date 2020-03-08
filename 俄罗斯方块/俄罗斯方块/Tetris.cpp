#pragma once
#include <iostream>
#include <graphics.h>
#include <stdlib.h>

#include "Tetris.h"

int rank = 0;
int score = 0;

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
	sprintf_s(str, "%d", rank);
	outtextxy(415, 310, str);
	outtextxy(405, 375, _T("等级:"));
	sprintf_s(str, "%d", score);
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
int main() {
	Welcome();
	initGameScene();


	system("pause");
	closegraph();
	return 0;
}