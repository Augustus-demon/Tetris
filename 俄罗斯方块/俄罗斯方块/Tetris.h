#pragma once
#ifndef __TETRIS_H__
#define __TETRIS_H__

#define BLOCK_KIND   5
#define BLOCK_HEIGHT 5
#define BLOCK_WIDTH  5
#define UNIT_SIZE    20

#define START_X 130
#define START_Y 30

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_DOWN  80
#define KEY_RIGHT 77
#define KEY_SPACE 32

#define MIN_X 30
#define MIN_Y 30

#define TIME_INTERVAL 10

#define isValid(x,y) (x >= 0 && x < 30 && y >= 0 && y < 15)//判断坐标是否合法

int Rank = 0;//级别
int Score = 0;//分数

int Gamearea[30][15]; //游戏区域
int areaColor[30][15];//固化区域的颜色
int dropSpeed = 50 * TIME_INTERVAL;//方块降落速度
int CurrentIndex = -1;             //当前方块种类
int NextIndex    = -1;             //下一方块种类
//方块的颜色
int Color[BLOCK_KIND ] = {
	CYAN,MAGENTA,YELLOW,BROWN,GREEN
};
typedef enum  {
	UP,
	LEFT,
	DOWN,
	RIGHT
}_Block_Dir;
typedef enum {
	MOVE_UP,
	MOVE_LEFT,
	MOVE_DOWN,
	MOVE_RIGHT
}_Move_Dir;

//表示方块的样式
int block[BLOCK_KIND * 4][BLOCK_HEIGHT][BLOCK_WIDTH] = {
	// | 型方块
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0,},//向上

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0,},//向左

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0,},//向下

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0,},//向右
	//T型方块
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,1,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,1,0,
	 0,0,1,0,0,
	 0,0,0,0,0,},
	 //田字形
	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0,},
	 //L型
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,1,0,
	 0,1,0,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,0,0,1,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0,},
	 //Z型
	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,0,0,
	 0,1,0,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0,},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,0,0,
	 0,1,0,0,0,
	 0,0,0,0,0,},

};

void Welcome();
void initGameScene();
void nextBlock();
void newBlock();
void drawBlock(int x, int y, _Block_Dir direct);
void drawBlock(int x, int y);
void clearBlock();
void clearBlock(int x, int y, _Block_Dir direct);
void Move();
bool rotatable(int x, int y, _Block_Dir Dir);
bool Movable(int x, int y, _Block_Dir b_Dir, _Move_Dir m_Dir);
void EndCheck();
void mark(int x, int y, _Block_Dir Dir);

#endif // !__TETRIS_H__
