#include <curses.h>
 
 
/*
	关于游戏区域的常量定义
*/
 
#define TOP 1			// 游戏区域的上边界
#define BOTTOM LINES - 2		// 游戏区域的下边界
#define LEFT 1			// 游戏区域的左边界
#define RIGHT COLS - 2    // 游戏区域的右边界
 
 
 
/*
 * 关于挡板的常量定义
*/
 
#define BLANK_BAFFLE "        "    // 用于擦除使用
#define SYMBOL_BAFFLE "========"   // 挡板的字符化表示
#define X_INIT_LEFT COLS / 2 - 4		// 挡板左部 X 坐标的初始值
#define X_INIT_RIGHT COLS / 2 + 3   		// 挡板右部 X 坐标的初始值
#define SPEED_INIT_BAFFLE 1
 
 
 
/*
	关于球的常量定义
*/
 
#define BLANK_BALL ' '		// 用于擦除使用
#define SYMBOL_BALL 'O'		// 球的字符化表示
#define X_INIT_BALL COLS / 2		// 球 X 坐标的初始值
#define Y_INIT_BALL LINES - 3		// 球 Y 坐标的初始值
#define X_INIT_SPEED 1		// 球 X 坐标上的速度初始值
#define Y_INIT_SPEED -1		// 球 Y 坐标上的速度初始值
 
 
 
/*
	关于砖块区域的常量定义
*/
 
#define BRICK_LEFT 30
#define BRICK_RIGHT 44
#define BRICK_TOP 2
#define BRICK_BOTTOM 6
#define BRICK_SYMBOL "   "
 
 
 
struct Ball
{
	int x_poi, y_poi;		// 球的 X,Y 坐标
	int	x_speed, y_speed;	// 球在 X,Y 方向的速度
	
	char symbol;			// 球的字符化表示
};
 
 
struct Baffle
{
	int x_left, x_right;		// 挡板的 X,Y 坐标
	int length;				// 挡板的长度
	int speed;				// 挡板的速度(仅在 X 方向上)
	char *symbol;			// 挡板的字符化表示
};