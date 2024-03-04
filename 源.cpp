#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<graphics.h>

ExMessage snake_ctrl_n;
//定时器
void time_gap(int time_g)
{
	clock_t start_time = clock();
	while (!(peekmessage(&snake_ctrl_n, EX_CHAR)))
	{
		clock_t end_time = clock();
		if (end_time - start_time > time_g)
			return;
	}
	return;
}
//蛇的控制及移动
void snake_ctrl(int *snake_xy)
{
	time_gap(600);
	printf("%d%c\n", snake_ctrl_n.ch, snake_ctrl_n.ch);
	switch (snake_ctrl_n.ch)
	{
	case 'a':(*snake_xy)--; break;
	case 'd':(*snake_xy)++; break;
	case 's':(*(snake_xy + 1))++; break;
	case 'w':(*(snake_xy + 1))--; break;
	default:break;
	}
}
void print_map(int snake_xy[][2], int apple_x, int apple_y, int eat_n)
{
	int apple_n = 0;
	cleardevice();
	setbkcolor(WHITE);
	setfillcolor(RED);
	fillrectangle(apple_x * 64, apple_y * 64, apple_x * 64 + 63, apple_y * 64 + 63);
	setfillcolor(GREEN);
	for (; apple_n <= eat_n; apple_n++)
	{
		fillrectangle((snake_xy[apple_n][0]) * 64, (snake_xy[apple_n][1]) * 64, (snake_xy[apple_n][0]) * 64 + 63, (snake_xy[apple_n][1]) * 64 + 63);
	}
	return;
}
int main()
{
	int snake_xy[100][2]={0}, snake_n, eat_n, apple_x, apple_y, snake_die;
	initgraph(640, 640, NULL);
	while (1)
	{
		snake_xy[0][0] = 2;
		snake_xy[0][1] = 2;
		eat_n = 0;
		apple_x = rand() % 7 + 3;
		apple_y = rand() % 7 + 3;
		snake_die = 0;
		while (1)
		{
			if (snake_xy[0][0] == apple_x && snake_xy[0][1] == apple_y)
			{
				eat_n++;
				apple_x = 10;
				while (apple_x == 10)
				{
					apple_x = rand() % 7 + 3;
					apple_y = rand() % 7 + 3;
					snake_n = 0;
					for (; snake_n <= eat_n; snake_n++)
					{
						if (snake_xy[snake_n][0] == apple_x && snake_xy[snake_n][1] == apple_y)
							apple_x = 10;
					}
				}
			}
			snake_n = eat_n;
			for (; snake_n >0; snake_n--)
			{
				snake_xy[snake_n][0] = snake_xy[snake_n-1][0];
				snake_xy[snake_n][1] = snake_xy[snake_n-1][1];
			}
			do
			{
				snake_ctrl(snake_xy[0]);
			} while (snake_ctrl_n.ch != 'a' && snake_ctrl_n.ch != 'd' && snake_ctrl_n.ch != 'w' && snake_ctrl_n.ch != 's');
			if (snake_xy[0][0] < 0 || snake_xy[0][0]>9 || snake_xy[0][1] < 0 || snake_xy[0][1]>9)
				break;
			snake_n = 1;
			for (; snake_n <= eat_n; snake_n++)
			{
				if (snake_xy[snake_n][0] == snake_xy[0][0] && snake_xy[snake_n][1] == snake_xy[0][1])
				{
					snake_die = 1;
					break;
				}
			}
			if (snake_die == 1)
				break;
			print_map(snake_xy, apple_x, apple_y, eat_n);
		}
	}
	exit(0);
}