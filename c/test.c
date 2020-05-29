#if 0

#include <signal.h>
#include <sys/time.h>  
#include <stdio.h>  
#include <sys/time.h>  
#include "header.h"
 
void init();
void ball_move();
 
struct Ball ball;	// 小球
struct Baffle baffle;   // 挡板
int matrix[5][15];		// 记录砖块区域信息的矩阵
 
int is_lose = 0;   // 是否输掉比赛
int num_bricks = 0;   // 砖块的数量
 
 
int main()
{
	int ch;
	
	init();
 
	while(1)
	{
		if( !is_lose && num_bricks > 0)  // 如果没赢也没输，游戏继续
		{
			ch = getch();
			if(ch == 'q')
				break;
			if(ch == 'j')  // 挡板左移
			{
				if(baffle.x_left > LEFT)
				{
					move(BOTTOM, baffle.x_right);
					addch(' ');
					baffle.x_left--;
					baffle.x_right--;
					move(BOTTOM, baffle.x_left);
					addch('=');
					move(LINES - 1, 0);
					refresh();
				}
			}
 
			else if(ch == 'k')		// 挡板右移
			{
				if(baffle.x_right < RIGHT)
				{
					move(BOTTOM, baffle.x_left);
					addch(' ');
					baffle.x_left++;
					baffle.x_right++;
					move(BOTTOM, baffle.x_right);
					addch('=');
					move(LINES - 1, 0);
					refresh();
				}
			}
		}
 
		else
		{
			int flag = 1;  
      char choice;  
      move(6, 10);
			clear();
			if(is_lose)  
				addstr("You lose.Try again？(y/n):");
			else
				addstr("You win，Try again？(y/n)");  
      refresh();  
      choice=getch();
 
			while(flag)
			{  
      	if(choice == 'y'|| choice == 'Y' || choice=='n' || choice == 'N')  
					flag=0;  
         else  
					choice=getch();  
      }  
      if(choice=='y'||choice=='Y'){  
         init();  
         continue;  
       }  
       else if(choice=='n'||choice=='N'){  
           break;  
       }    
		}
	}
 
 
endwin();
return 0;
}
 
 
void init()
{
	/*
		该函数主要完成初始化的工作
	*/
 
	int i,j,k;
 
	initscr();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	crmode();
	noecho();
 
	// 初始小球信息
	ball.x_poi = X_INIT_BALL;
	ball.y_poi = Y_INIT_BALL;
	ball.x_speed = X_INIT_SPEED; 
	ball.y_speed = Y_INIT_SPEED;
	ball.symbol = 'O';
 
	// 初始挡板信息
	baffle.x_left = X_INIT_LEFT;
	baffle.x_right = X_INIT_RIGHT;
	baffle.speed = SPEED_INIT_BAFFLE;
 
 
	// 绘制砖块,并修改矩阵的值（左上到右下的部分）
	attron(A_REVERSE);
	for(i = BRICK_TOP, j = BRICK_LEFT; i <= BRICK_BOTTOM; i++, j += 3)
	{
		move(i, j);
		addstr(BRICK_SYMBOL);
		move(LINES - 1, 0);	
		refresh();
		for(k = 0; k < 3; k++)
			matrix[i - BRICK_TOP][j - BRICK_LEFT + k] = 1;
		num_bricks++;
	}
 
	// 左下到右上的部分
	for(i = BRICK_BOTTOM, j = BRICK_LEFT; i >= BRICK_TOP; i--, j += 3)
	{
		move(i, j);
		addstr(BRICK_SYMBOL);
		move(LINES - 1, 0);		
		refresh();
		for(k = 0; k < 3; k++)
			matrix[i - BRICK_TOP][j - BRICK_LEFT + k] = 1;
		num_bricks++;
	}
 
	// 中间横向的部分
	for(i = (BRICK_TOP + BRICK_BOTTOM) / 2, j = BRICK_LEFT; j <= BRICK_RIGHT; j += 6)
	{
		move(i, j);
		addstr(BRICK_SYMBOL);
		move(LINES - 1, 0);	
		refresh();
		for(k = 0; k < 3; k++)
			matrix[i - BRICK_TOP][j - BRICK_LEFT + k] = 1;
		num_bricks++;
	}
	attroff(A_REVERSE);
	move(LINES - 1, 0);	
	refresh();
 
	// 绘制小球和挡板
	move(ball.y_poi, ball.x_poi);
	addch(SYMBOL_BALL);
 
	move(BOTTOM, baffle.x_left);
	addstr(SYMBOL_BAFFLE);
 
	move(LINES - 1, 0);
	refresh();
 
	signal(SIGALRM, ball_move);
	set_ticker(100);
 
 
}
 
 
 
 
void ball_move()
{
	/*
	该函数用于实现小球移动的功能
	*/  
 
	int x_index, y_index;
	int differ;
	int i;
 
	signal(SIGALRM, ball_move);
	move(ball.y_poi, ball.x_poi);
	addch(BLANK_BALL);
	ball.x_poi += ball.x_speed;
	ball.y_poi += ball.y_speed;
 
	if(ball.x_poi >= RIGHT || ball.x_poi <= LEFT)
		ball.x_speed = -ball.x_speed;
	if(ball.y_poi <= TOP)
		ball.y_speed = -ball.y_speed;
 
	if(ball.y_poi >= BOTTOM - 1)
	{
		if(ball.x_poi >= baffle.x_left && ball.x_poi <= baffle.x_right)
			ball.y_speed = -ball.y_speed;
		else
		{
			// 输掉游戏
			 is_lose=1;  
		}
	}
 
	// 假如小球落入砖块区域内
	if(ball.x_poi >= BRICK_LEFT && ball.x_poi <= BRICK_RIGHT && ball.y_poi >= BRICK_TOP && ball.y_poi <= BRICK_BOTTOM)
	{
		x_index = ball.x_poi - BRICK_LEFT;
		y_index = ball.y_poi - BRICK_TOP;
		if(matrix[y_index][x_index] == 1)
		{
			differ = x_index % 3;
			for(i = 0; i < 3; i++)
				matrix[y_index][x_index - differ + i] = 0;
			move(ball.y_poi, ball.x_poi - differ);
			addstr("   ");
			move(LINES - 1, 0);
			refresh();
			num_bricks--;
 
			ball.y_speed = -ball.y_speed;
		}
	}
 
	move(ball.y_poi, ball.x_poi);
	addch(SYMBOL_BALL);
	move(LINES - 1, 0);
	refresh();
 
}
 
 
 
int set_ticker(int n_msecs){
	struct itimerval new_timeset;	
	long n_sec,n_usecs;
	n_sec=n_msecs/1000;
	n_usecs=(n_msecs%1000)*1000L;
	new_timeset.it_interval.tv_sec=n_sec;
	new_timeset.it_interval.tv_usec=n_usecs;
	new_timeset.it_value.tv_sec=n_sec;
	new_timeset.it_value.tv_usec=n_usecs;
	return setitimer(ITIMER_REAL,&new_timeset,NULL);
 
}

#endif


#if 1
#include <stdio.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>
 
// 游戏区域的定义
#define GAME_WIDTH 500
#define GAME_LENGTH 600
 
 
struct ball
{
    int x, y;        // 小球的坐标(圆心)
    int speed_x, speed_y;        // 小球的速度
    int radius;        // 半径
    int exist;			// 是否存在
};
 
 
struct Baffle
{
    int x, y;        // 挡板的坐标（挡板左上角）
    int width, length;        // 挡板的长和宽
};
 
 
struct Bricks
{
    int matrix[8][12];   // 记录砖块群信息的矩阵
    int scores[8][12];  // 记录砖块群分数值的矩阵
    int reward[8][12];	// 记录砖块群奖励情况的矩阵
    int width, length;   // 每一块砖块的长和宽
};
 
 
 
 
// 全局变量
struct ball ball1, ball2;        // 小球
struct Baffle baffle;    // 挡板
struct Bricks bricks;    // 砖块
 
GtkWidget *window = NULL;  // 游戏主窗口
GtkWidget *fixed = NULL;
GtkWidget *start = NULL;
GtkWidget *lose = NULL;    // 游戏失败提示窗口
GtkWidget *win = NULL;	   // 游戏胜利窗口
GtkWidget *score_label = NULL;		// 记录分数的标签
GtkWidget *border_down = NULL;		// 下边界
GtkWidget *dialog=NULL;//是否继续游戏对话框
GtkWidget *button;//对话框按钮
 
 
int break_off;            // 处理暂停的变量。0代表游戏继续，1代表游戏暂停
int score;		// 记录得分的变量
int done = 0;		// 对应提升难度的
 
// 函数声明
void play(int argc,char **argv);//开始游戏
void init(void);
static gboolean expose_handler(GtkWidget * widget,
                GdkEventExpose * event, gpointer data);
 
static gboolean time_handler(GtkWidget *widget);
 
void press_handler(GtkWidget *widget, GdkEventKey *event);
 
void play_music();
void give_reward(int reward);
 
void yes(GtkWidget *widget,gpointer *data,int argc, char **argv);//按钮“YES”
void no(GtkWidget *widget,gpointer *data);//按钮“NO”
 
 
int main(int argc, char **argv)
{
    play(argc,argv);
    return 0;
}
 
void play(int argc,char **argv)//开始游戏函数
{
    init();
    gtk_init(&argc,&argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
 
    fixed = gtk_fixed_new();
    gtk_container_add (GTK_CONTAINER (window), fixed);
	gtk_widget_show (fixed);
 
    border_down = gtk_button_new();
    gtk_widget_set_sensitive(border_down, FALSE);
 
    gtk_widget_set_size_request(border_down, 600, 5);
    gtk_fixed_put(GTK_FIXED(fixed), border_down, 0, GAME_WIDTH);
		gtk_widget_show(border_down);
 
	score_label = gtk_label_new("目前得分为： ");
	gtk_fixed_put(GTK_FIXED(fixed), score_label, 0, 505);
	gtk_widget_show(score_label);
 
 
    win = gtk_label_new("恭喜你，已通关");
    gtk_widget_set_size_request(win, 200, 100);
 
    lose = gtk_label_new("真遗憾，你输了，是否重新开始");
 
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),
                        NULL);
    g_signal_connect(G_OBJECT(window), "expose_event", G_CALLBACK(expose_handler),
                        NULL);
    g_signal_connect ( G_OBJECT ( window) , "key_press_event" ,
                        G_CALLBACK (press_handler) , NULL );
 
    gtk_window_set_position ( GTK_WINDOW ( window) ,
                                 GTK_WIN_POS_CENTER);
 
    gtk_window_set_default_size ( GTK_WINDOW ( window) , GAME_LENGTH, GAME_WIDTH + 40);
    gtk_widget_set_app_paintable ( window, TRUE );
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE); //禁止窗口最大化
    gtk_widget_show_all(window);
 
    g_timeout_add(10, (GSourceFunc)time_handler, NULL);
    gtk_main();
}
 
/*
 *
 * name: init
 * @param
 * @return
 *
 * 完成初始化
 */
void init()
{
    int i,j;
 
 
    break_off = 0;
    score = 0;
 
    // 挡板的初始化
    baffle.length = 100;
    baffle.width = 10;
    baffle.x = GAME_LENGTH / 2 - baffle.length / 2;
    baffle.y = GAME_WIDTH - baffle.width;
 
    // 小球的初始化
    ball1.radius = 5;
    ball1.x = GAME_LENGTH / 2;
    ball1.y = baffle.y - ball1.radius;
    ball1.speed_x = 1;
    ball1.speed_y = -1;
    ball1.exist = 1;
 
	ball2.radius = 5;
	ball2.exist = 0;
 
    // 砖块群的初始化
    bricks.length = 50;
    bricks.width = 20;
 
 
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 12; j++)
			bricks.matrix[i][j] = bricks.scores[i][j] = bricks.reward[i][j] = 0;
	}
 
 
 
	for(i = 0; i < 8; i++)
		bricks.matrix[i][0] = bricks.scores[i][0] = 1;
	for(i = 0; i < 12; i++)
		bricks.matrix[7][i] = bricks.scores[7][i] = 1;
	for(i = 0; i < 8; i++)
		bricks.matrix[i][11] = bricks.scores[i][11] = 1;
	for(i = 2; i < 12; i++)
		bricks.matrix[0][i] = bricks.scores[0][i] = 1;
	for(i = 0; i < 6; i++)
		bricks.matrix[i][2] = bricks.scores[i][2] = 2;
	for(i = 2; i < 10; i++)
		bricks.matrix[5][i] = bricks.scores[5][i] = 2;
	for(i = 2; i < 6; i++)
		bricks.matrix[i][9] = bricks.scores[i][9] = 2;
	for(i = 4; i < 10; i ++)
		bricks.matrix[2][i] = bricks.scores[2][i] = 3;
 
 
		bricks.reward[7][9] = 1;
		bricks.reward[7][0] = 2;
}
 
 
 
static gboolean expose_handler(GtkWidget * widget,
                GdkEventExpose * event, gpointer data)
{
    cairo_t *cr;
    int i,j;
    int count = 0;
 
    cr = gdk_cairo_create(widget ->window);
 
    // 先画出挡板（矩形）
    cairo_set_line_width(cr, 2);
    cairo_set_source_rgb(cr, 0.69, 0.19, 0);
    cairo_rectangle(cr, baffle.x, baffle.y, baffle.length, baffle.width);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 0.3, 0.4, 0.6);
    cairo_fill(cr);
 
 
    // 再画出小球
 
    if(ball1.exist == 1)
    {
    cairo_set_line_width(cr, 0);
    cairo_arc(cr, ball1.x, ball1.y, ball1.radius, 0, 2 * M_PI);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_fill(cr);
    }
 
 
    if(ball2.exist == 1)
    {
    cairo_set_line_width(cr, 0);
    cairo_arc(cr, ball2.x, ball2.y, ball2.radius, 0, 2 * M_PI);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_fill(cr);
    }
 
 
    for(i = 0; i < 8; i++)
    {
		if(bricks.matrix[i][0] != 0)
		{
 
 
			cairo_set_line_width(cr, 1);
            cairo_set_source_rgb(cr, 1, 1, 0);
            cairo_rectangle(cr,  0 * bricks.length, i * bricks.width, bricks.length, bricks.width);
            cairo_stroke_preserve(cr);
 
				cairo_set_source_rgb(cr, 0.016 * count, 0.1 * count, 0.2);
            cairo_fill(cr);
 
		}
			count++;
	}
 
	for(i = 0; i < 12; i++)
	{
		if(bricks.matrix[7][i] != 0)
		{
			cairo_set_line_width(cr, 1);
            cairo_set_source_rgb(cr, 1, 1, 0);
            cairo_rectangle(cr,  i * bricks.length, 7 * bricks.width, bricks.length, bricks.width);
            cairo_stroke_preserve(cr);
 
		if(bricks.reward[7][i] != 0)
			cairo_set_source_rgb(cr, 0.8, 0.1, 0.9);
		else
			cairo_set_source_rgb(cr, 0.016 * count, 0.8, 0.018 * count);
            cairo_fill(cr);
		}
		count++;
	}
 
	for(i = 1; i < 8; i++)
	{
		if(bricks.matrix[i][11] != 0)
		{
			cairo_set_line_width(cr, 1);
            cairo_set_source_rgb(cr, 1, 1, 0);
            cairo_rectangle(cr,  11 * bricks.length, i * bricks.width, bricks.length, bricks.width);
            cairo_stroke_preserve(cr);
            cairo_set_source_rgb(cr, 0.016 * count, 0.8, 0.2);
            cairo_fill(cr);
		}
		count++;
	}
 
	for(i = 2; i < 12; i++)
	{
		if(bricks.matrix[0][i] != 0)
		{
			cairo_set_line_width(cr, 1);
            cairo_set_source_rgb(cr, 1, 1, 0);
            cairo_rectangle(cr,  i * bricks.length, 0 * bricks.width, bricks.length, bricks.width);
            cairo_stroke_preserve(cr);
            cairo_set_source_rgb(cr, 0.016 * count, 0.8, 0.2);
            cairo_fill(cr);
		}
		count++;
	}
 
	for(i = 0; i < 6; i++)
	{
		if(bricks.matrix[i][2] != 0)
		{
			cairo_set_line_width(cr, 1);
            cairo_set_source_rgb(cr, 1, 1, 0);
            cairo_rectangle(cr,  2 * bricks.length, i * bricks.width, bricks.length, bricks.width);
            cairo_stroke_preserve(cr);
            cairo_set_source_rgb(cr, 0.016 * count, 0.8, 0.2);
            cairo_fill(cr);
		}
		count++;
	}
 
 
	for(i = 2; i < 10; i++)
	{
		if(bricks.matrix[5][i] != 0)
		{
			cairo_set_line_width(cr, 1);
            cairo_set_source_rgb(cr, 1, 1, 0);
            cairo_rectangle(cr,  i * bricks.length, 5 * bricks.width, bricks.length, bricks.width);
            cairo_stroke_preserve(cr);
            cairo_set_source_rgb(cr, 0.016 * count, 0.8, 0.2);
            cairo_fill(cr);
		}
		count++;
	}
 
 
	for(i = 2; i < 6; i++)
	{
		if(bricks.matrix[i][9] != 0)
		{
			cairo_set_line_width(cr, 1);
            cairo_set_source_rgb(cr, 1, 1, 0);
            cairo_rectangle(cr,  9 * bricks.length, i * bricks.width, bricks.length, bricks.width);
            cairo_stroke_preserve(cr);
            cairo_set_source_rgb(cr, 0.016 * count, 0.8, 0.2);
            cairo_fill(cr);
		}
		count++;
	}
 
 
	for(i = 4; i < 10; i ++)
	{
		if(bricks.matrix[2][i] != 0)
		{
			cairo_set_line_width(cr, 1);
            cairo_set_source_rgb(cr, 1, 1, 0);
            cairo_rectangle(cr,  i * bricks.length, 2 * bricks.width, bricks.length, bricks.width);
            cairo_stroke_preserve(cr);
            cairo_set_source_rgb(cr, 0.016 * count, 0.8, 0.2);
            cairo_fill(cr);
		}
		count++;
    }
    cairo_destroy(cr);
    return FALSE;
}
 
 
static gboolean time_handler(GtkWidget *widget)
{
    int top_ball1, bottom_ball1, right_ball1, left_ball1;
int top_ball2, bottom_ball2, right_ball2, left_ball2;
    int virtual_x, virtual_y;
	char buffer[40], choice;
	double index;
    if(break_off == 1)
        return TRUE;
 
 
    // 赢了
    if(score == 100)
    {
		gtk_fixed_put(GTK_FIXED(fixed), win, 200, 200);
		gtk_widget_show(win);
		return FALSE;
	}
 
 
	// 分数达到一定级别提升难度
	if(score >= 20 && done == 0)
	{
		baffle.length = baffle.length / 2;
		ball1.speed_x = 2 * ball1.speed_x;
		ball1.speed_y = 2 * ball1.speed_y;
		ball2.speed_x = 2 * ball2.speed_x;
		ball2.speed_y = 2 * ball2.speed_y;
		done = 1;
	}
 
	// 输了
	if(ball1.exist == 0 && ball2.exist == 0)
	{
        dialog=gtk_dialog_new();//初始化对话框
 
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),lose,TRUE,TRUE,0);//添加文本组件并显示
        gtk_widget_show(lose);
 
        button=gtk_button_new_with_label("Yes");//添加“YES”按钮
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),button,TRUE,TRUE,0);
        gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK(yes),dialog);//添加“YES”按钮事件驱动
        gtk_widget_show(button);
 
        button=gtk_button_new_with_label("No");//添加“NO”按钮
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),button,TRUE,TRUE,0);
		gtk_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK(no),NULL);//添加“NO”按钮事件驱动
		gtk_widget_show(button);
 
		gtk_widget_show(dialog);//显示对话框
		return FALSE;
	}
 
	if(ball1.exist != 0)
	{
 
 
		ball1.x += ball1.speed_x;
		ball1.y += ball1.speed_y;
		if(ball1.x <= 0 + ball1.radius || ball1.x >= GAME_LENGTH - ball1.radius)
			ball1.speed_x = -ball1.speed_x;
 
		if(ball1.y <= 0 + ball1.radius)
			ball1.speed_y = -ball1.speed_y;
 
 
		if(ball1.y >= GAME_WIDTH - baffle.width - ball1.radius)
		{
			if(ball1.x >= baffle.x && ball1.x <= baffle.x + baffle.length)
			{
				ball1.speed_y = -ball1.speed_y;
			}
		}
 
		//  小球落入最下方，停止游戏
		if(ball1.y >= GAME_WIDTH - ball1.radius)
		{
			ball1.exist = 0;
		}
 
    // 检测碰撞
 
		// 当小球向右下方移动时,小球的右方和下方可能碰到砖块
		if(ball1.speed_x > 0 && ball1.speed_y > 0)
		{
			bottom_ball1 = ball1.y + ball1.radius;
			virtual_x = ball1.x / bricks.length;
			virtual_y = bottom_ball1 / bricks.width;
 
			// 小球下方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball1.speed_y = -ball1.speed_y;
 
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();	//  播放音效
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
								give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
 
			right_ball1 = ball1.x + ball1.radius;
			virtual_x = right_ball1 / bricks.length;
			virtual_y = ball1.y / bricks.width;
 
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0)
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball1.speed_x = -ball1.speed_x;
 
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
		}
 
		// 当小球向右上方移动时
		else if(ball1.speed_x > 0 && ball1.speed_y < 0)
		{
			top_ball1 = ball1.y - ball1.radius;
			virtual_x = ball1.x / bricks.length;
			virtual_y = top_ball1 / bricks.width;
 
			// 小球上方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball1.speed_y = -ball1.speed_y;
 
 
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
 
 
 
			right_ball1 = ball1.x + ball1.radius;
			virtual_x = right_ball1 / bricks.length;
			virtual_y = ball1.y / bricks.width;
 
			// 小球右方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball1.speed_x = -ball1.speed_x;
 
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
 
		}
 
		// 当小球向左下方移动时
		else if(ball1.speed_x < 0 && ball1.speed_y > 0)
		{
 
			bottom_ball1 = ball1.y + ball1.radius;
			virtual_x = ball1.x / bricks.length;
			virtual_y = bottom_ball1 / bricks.width;
 
			// 小球下方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball1.speed_y = -ball1.speed_y;
 
 
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
 
 
 
			left_ball1 = ball1.x - ball1.radius;
			virtual_x = left_ball1 / bricks.length;
			virtual_y = ball1.y / bricks.width;
 
			// 小球左方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball1.speed_x = -ball1.speed_x;
 
 
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
		}
 
 
		// 当小球向左上方移动时
		else
		{
			top_ball1 = ball1.y - ball1.radius;
			virtual_x = ball1.x / bricks.length;
			virtual_y = top_ball1 / bricks.width;
 
			// 小球上方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball1.speed_y = -ball1.speed_y;
 
 
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
 
 
 
			left_ball1 = ball1.x - ball1.radius;
			virtual_x = left_ball1 / bricks.length;
			virtual_y = ball1.y / bricks.width;
 
			// 小球左方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball1.speed_x = -ball1.speed_x;
 
 
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
		}
	}
/////////////////////////////////
 
	if(ball2.exist == 1)
	{
		ball2.x += ball2.speed_x;
		ball2.y += ball2.speed_y;
		if(ball2.x <= 0 + ball2.radius || ball2.x >= GAME_LENGTH - ball2.radius)
			ball2.speed_x = -ball2.speed_x;
 
		if(ball2.y <= 0 + ball2.radius)
			ball2.speed_y = -ball2.speed_y;
		if(ball2.y >= GAME_WIDTH - baffle.width - ball2.radius)
		{
			if(ball2.x >= baffle.x && ball2.x <= baffle.x + baffle.length)
			{
				ball2.speed_y = -ball2.speed_y;
			}
		}
 
		//  小球落入最下方，停止游戏
		if(ball2.y >= GAME_WIDTH - ball2.radius)
		{
			ball2.exist = 0;
		}
 
		// 检测碰撞
 
		// 当小球向右下方移动时,小球的右方和下方可能碰到砖块
		if(ball2.speed_x > 0 && ball2.speed_y > 0)
		{
			bottom_ball2 = ball2.y + ball2.radius;
			virtual_x = ball2.x / bricks.length;
			virtual_y = bottom_ball2 / bricks.width;
 
			// 小球下方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball2.speed_y = -ball2.speed_y;
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();	//  播放音效
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
 
				}
			}
 
			right_ball2 = ball2.x + ball2.radius;
			virtual_x = right_ball2 / bricks.length;
			virtual_y = ball2.y / bricks.width;
		//
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0)
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball2.speed_x = -ball2.speed_x;
 
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();	//  播放音效
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
		}
 
		// 当小球向右上方移动时
		else if(ball2.speed_x > 0 && ball2.speed_y < 0)
		{
			top_ball2 = ball2.y - ball2.radius;
			virtual_x = ball2.x / bricks.length;
			virtual_y = top_ball2 / bricks.width;
 
			// 小球上方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball2.speed_y = -ball2.speed_y;
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();	//  播放音效
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
 
 
 
			right_ball2 = ball2.x + ball2.radius;
			virtual_x = right_ball2 / bricks.length;
			virtual_y = ball2.y / bricks.width;
 
			// 小球右方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball2.speed_x = -ball2.speed_x;
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();	//  播放音效
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
 
		}
 
		// 当小球向左下方移动时
		else if(ball2.speed_x < 0 && ball2.speed_y > 0)
		{
 
			bottom_ball2 = ball2.y + ball2.radius;
			virtual_x = ball2.x / bricks.length;
			virtual_y = bottom_ball2 / bricks.width;
 
			// 小球下方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball2.speed_y = -ball2.speed_y;
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();	//  播放音效
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
 
 
 
			left_ball2 = ball2.x - ball2.radius;
			virtual_x = left_ball2 / bricks.length;
			virtual_y = ball2.y / bricks.width;
 
			// 小球左方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball2.speed_x = -ball2.speed_x;
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();	//  播放音效
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
		}
 
 
		// 当小球向左上方移动时
		else
		{
			top_ball2 = ball2.y - ball2.radius;
			virtual_x = ball2.x / bricks.length;
			virtual_y = top_ball2 / bricks.width;
 
			// 小球下方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball2.speed_y = -ball2.speed_y;
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();	//  播放音效
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
 
 
 
			left_ball2 = ball2.x - ball2.radius;
			virtual_x = left_ball2 / bricks.length;
			virtual_y = ball2.y / bricks.width;
 
			// 小球左方碰撞到砖块
			if(virtual_x >= 0 && virtual_x <= 11 && virtual_y >= 0 && virtual_y <= 7)
			{
				if(bricks.matrix[virtual_y][virtual_x] != 0) // 该砖块存在
				{
					bricks.matrix[virtual_y][virtual_x]--;
					ball2.speed_x = -ball2.speed_x;
 
					if(bricks.matrix[virtual_y][virtual_x] == 0)
					{
						score += bricks.scores[virtual_y][virtual_x];
						play_music();	//  播放音效
 
						if(bricks.reward[virtual_y][virtual_x] != 0)
							give_reward(bricks.reward[virtual_y][virtual_x]);
					}
				}
			}
		}
 
	}
 
	sprintf(buffer, "目前得分为%d", score);
    gtk_label_set_text(GTK_LABEL(score_label), buffer);
    gdk_window_invalidate_rect(window ->window, NULL, FALSE);
    return TRUE ;
}
 
void press_handler(GtkWidget *widget, GdkEventKey *event)
{
    switch(event ->keyval)
    {
        case 65361:  // 左键
            if(baffle.x > 0)
                baffle.x -= 10;
            break;
 
        case 65363:  // 右键
            if(baffle.x < 600 - baffle.length)
                baffle.x += 10;
            break;
 
        case 32:    // 空格（暂停）
            break_off = 1;
            break;
 
        case 65293:        // 回车
            break_off = 0;
            break;
 
        default:
            break;
    }
 
}
 
 
void play_music()
{
	system("sh voice");
}
 
 
void give_reward(int reward)
{
	if(reward == 1)			// 挡板加长
		baffle.length += 40;
 
	else
	{
		ball2.exist = 1;
		ball2.x = ball1.x;
		ball2.y = ball1.y;
 
		ball2.speed_x = -ball1.speed_x;
		ball2.speed_y = ball1.speed_y;
	}
}
 
void yes(GtkWidget *widget,gpointer *data,int argc, char **argv)//按钮“YES”
{
    gtk_widget_destroy(GTK_WIDGET(data));//删除选择对话框
    gtk_widget_destroy(window);//删除游戏框
    play(argc,argv);//重新开始游戏
}
 
void no(GtkWidget *widget,gpointer *data)//按钮“NO”
{
	exit(0);//退出游戏
}
#endif