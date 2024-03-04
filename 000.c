//█背景墙
//囗蛇
//〇果
int static now_s = 0;//初始化目前得分
int static record_s = 0;//初始化记录
int static set_range_a = 2;//初始化地图大小选项(默认中地图选项)
int static set_range_map = 2;//初始化地图大小
int static set_level_a = 2;//初始化游戏难度选项(默认普通选项)
int static set_level_speed = 600;//初始化游戏难度(默认普通)

#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

int time_gap(int time_g)
{
	clock_t start_time = clock();
	while(!_kbhit())
	{
		clock_t end_time = clock();
		if (end_time - start_time >= time_g)
			return 0;
	}
	return 1;
}
//定时器
void switch_core(char switch_ctrl,int *x,int switch_key)//这里指针x原本使用x形参，但是发现改变不了实参，这是因为形参的改变影响不了实参。尝试使用返回值发现有缺陷。所以使用指针，形参指针虽然是形参，但却指向实参本体，所以对*指针的改变，就是对实参本体的改变。
{
	int main();
	void set_ctrl_intetface();
	void set_ctrl_range_intetface();
	void set_ctrl_level_intetface();
	if(switch_ctrl == 27)
		switch (switch_key)
		{
		case 1:main(); return;
		case 2:set_ctrl_intetface(); return;
		case 3:set_ctrl_intetface(); return;
		default:printf("返回失败");
		}
	else if (switch_ctrl == 's' || switch_ctrl == 'a')
	{
		--*x;
	}
	else if (switch_ctrl == 'w' || switch_ctrl == 'd')
	{
		++*x;
	}
	else if (switch_ctrl == '\r')
	{
		switch (switch_key)
		{
		case 1:
			switch (*x)
			{
			case 1:set_ctrl_level_intetface(); return;//前往设置游戏难度等级
			case 2:set_ctrl_range_intetface(); return;//前往设置地图大小
			case 3:main(); return;//返回主界面
			default:printf("选择失败");
			}
			return;
			//设置交互
		case 2:
			switch (*x)
			{
			case 1:set_range_map = 1; set_ctrl_intetface(); return;
			case 2:set_range_map = 2; set_ctrl_intetface(); return;
			case 3:set_range_map = 3; set_ctrl_intetface(); return;
			default:printf("选择失败");
			}
			return;
			//地图大小交互
		case 3:
			switch (*x)
			{
			case 1:set_level_speed = 900; set_ctrl_intetface(); return;
			case 2:set_level_speed = 600; set_ctrl_intetface(); return;
			case 3:set_level_speed = 300; set_ctrl_intetface(); return;
			default:printf("选择失败");
			}
			//游戏的难度交互
		default:printf("类别识别失败");
		}
		switch_key = 0;
	}
	if (*x == 0)
		*x = 3;
	else if (*x == 4)
		*x = 1;
}
//主界面交互中心
void print_eg()
{
	int idpt_eg = 1;
	for (; idpt_eg < 50; idpt_eg++)
	{
		if (idpt_eg == 1 || idpt_eg == 49)
			printf("██");
		else
			printf("  ");
	}
	printf("\n");
}
//打印单个侧边框
void print_ud()
{
	int idpt_ud = 1;
	for (; idpt_ud < 50; idpt_ud++)
		printf("██");
	printf("\n");
}
//打印上下边框
void print_tips() 
{
	printf("      W       上        P   暂停        Esc   返回      目前得分：%d\n    A S D   左下右      Enter   确定                      记录：%d\n", now_s, record_s);
}
//打印提示栏
void set_level_intetface(int x)
{
	int set_level_x, set_level_y;
	print_ud();
	//上边框
	set_level_y = 1;
	while (set_level_y < 26)
	{
		while (set_level_y != 13 && set_level_y != 12 && set_level_y != 14 && set_level_y < 26)
		{
			print_eg();
			//单个侧边框
			set_level_y++;
		}
		if (set_level_y == 12 || set_level_y == 13 || set_level_y == 14)
		{
			set_level_x = 1;
			for (; set_level_x < 36; set_level_x++)
			{
				if (set_level_x == 1 || set_level_x == 35)
					printf("██");
				else if (set_level_x == 18 && set_level_y == 12)
					printf("           游戏难度           ");
				else if (set_level_x == 18 && set_level_y == 13 && x == 1)
					printf("》 简单 《   普通      困难   ");
				else if (set_level_x == 18 && set_level_y == 13 && x == 2)
					printf("   简单   》 普通 《   困难   ");//28字节
				else if (set_level_x == 18 && set_level_y == 13 && x == 3)
					printf("   简单      普通   》 困难 《");
				else if (set_level_x == 18 && set_level_y == 14)
					printf("   .900      .600      .300   ");
				else
					printf("  ");
			}
			printf("\n");
			//交互栏
			set_level_y++;
		}
	}
	print_ud();
	//下边框
	print_tips();
	//提示栏
}
//游戏的难度界面
void set_ctrl_level_intetface()
{
	switch (set_level_speed)
	{
	case 300:set_level_a = 3; break;
	case 600:set_level_a = 2; break;
	case 900:set_level_a = 1; break;
	default:printf("修正失败");
	}
	//若交互未确定,再次进入时会导致set_level_a与set_level_speed不对应,看不到当前的难度,但选择难度不会出现问题
	char set_ctrl_level;
	set_ctrl_level = '\0';
	while (1)
	{
		set_level_intetface(set_level_a);
		set_ctrl_level = _getch();
		switch_core(set_ctrl_level, &set_level_a, 3);
	}
}
//游戏的难度界面控制
void set_range_intetface(int x)
{
	int set_range_x, set_range_y;
	print_ud();
	//上边框
	set_range_y = 1;
	while (set_range_y < 26)
	{
		while (set_range_y != 13 && set_range_y != 12 && set_range_y != 14 && set_range_y < 26)
		{
			print_eg();
			//单个侧边框
			set_range_y++;
		}
		if (set_range_y == 12 || set_range_y == 13 || set_range_y == 14)
		{
			set_range_x = 1;
			for (; set_range_x < 36 ; set_range_x++)
			{
				if (set_range_x == 1 || set_range_x == 35)
					printf("██");
				else if (set_range_x == 18 && set_range_y == 12)
					printf("           地图大小           ");
				else if (set_range_x == 18 && set_range_y == 13 && x == 1)
					printf("》 小 《      中         大   ");
				else if (set_range_x == 18 && set_range_y == 13 && x == 2)
					printf("   小      》 中 《      大   ");//28字节
				else if (set_range_x == 18 && set_range_y == 13 && x == 3)
					printf("   小         中      》 大 《");
				else if (set_range_x == 18 && set_range_y == 14)
					printf(" 13一33     19一41     25一49 ");
				else
					printf("  ");
			}
			printf("\n");
			//交互栏
			set_range_y++;
		}
	}
	print_ud();
	//下边框
	print_tips();
	//提示栏
}
//游戏的地图大小界面
void set_ctrl_range_intetface()
{
	switch (set_range_map)
	{
	case 1:set_range_a = 1; break;
	case 2:set_range_a = 2; break;
	case 3:set_range_a = 3; break;
	default:printf("修正失败");
	}
	//若交互未确定,再次进入时会导致set_range_a与set_range_map不对应,看不到当前的地图大小,但选择地图大小不会出现问题
	char set_ctrl_range;
	set_ctrl_range = '\0';
	while (1)
	{
		set_range_intetface(set_range_a);
		set_ctrl_range = _getch();
		switch_core(set_ctrl_range, &set_range_a, 2);
	}
}
//游戏的地图大小界面控制
void set_intetface(int x)
{
	int set_x, set_y;
	print_ud();
	//上边框
	set_y = 1;
	while (set_y < 26)
	{
		while (set_y != 13 && set_y != 12 && set_y != 14 && set_y < 26)
		{
			print_eg();
			//单个侧边框
			set_y++;
		}
		if (set_y == 12 || set_y == 13 || set_y == 14)
		{
			set_x = 1;
			for (; set_x < 45 && x == 1; set_x++)
			{
				if (set_x == 1 || set_x == 44)
					printf("██");
				else if (set_x == 23 && set_y == 12)
					printf("  地图大小  ");
				else if (set_x == 23 && set_y == 13)
					printf("》游戏难度《");
				else if (set_x == 23 && set_y == 14)
					printf("    返回    ");
				else
					printf("  ");
			}
			for (; set_x < 45 && x == 2; set_x++)
			{
				if (set_x == 1 || set_x == 44)
					printf("██");
				else if (set_x == 23 && set_y == 12)
					printf("    返回    ");
				else if (set_x == 23 && set_y == 13)
					printf("》地图大小《");
				else if (set_x == 23 && set_y == 14)
					printf("  游戏难度  ");
				else
					printf("  ");
			}
			for (; set_x < 45 && x == 3; set_x++)
			{
				if (set_x == 1 || set_x == 44)
					printf("██");
				else if (set_x == 23 && set_y == 12)
					printf("  游戏难度  ");
				else if (set_x == 23 && set_y == 13)
					printf("》  返回  《");
				else if (set_x == 23 && set_y == 14)
					printf("  地图大小  ");
				else
					printf("  ");
			}
			printf("\n");
			//交互栏
			set_y++;
		}
	}
	print_ud();
	//下边框
	print_tips();
	//提示栏
}
//设置界面
void set_ctrl_intetface() 
{
	int set_a;
	char set_ctrl;
	set_a = 1;
	set_ctrl = '\0';
	while (1)
	{
		set_intetface(set_a);//进入设置界面打印模块
		set_ctrl = _getch();
		switch_core(set_ctrl, &set_a, 1);
	}
}
//设置控制
void map_print(int map_key, int snake_state, int *snake_map, int apple_x, int apple_y)
{
	int map_print_x, map_print_y, print_n, print_n_n;
	switch (snake_state)
	{
	case 0:
		print_ud();
		//上边框
		map_print_y = 1;
		while (map_print_y < 26)
		{
			while (map_print_y != 13 && map_print_y != 12 && map_print_y != 14 && map_print_y < 26)
			{
				print_eg();
				//单个侧边框
				map_print_y++;
			}
			if (map_print_y == 12 || map_print_y == 13 || map_print_y == 14)
			{
				map_print_x = 1;
				for (; map_print_x < 45; map_print_x++)
				{
					if (map_print_x == 1 || map_print_x == 44)
						printf("██");
					else if (map_print_x == 23 && map_print_y == 12)
						printf("! 你完蛋了 !");
					else if (map_print_x == 23 && map_print_y == 13)
						printf("》重新游戏《");
					else if (map_print_x == 23 && map_print_y == 14)
						printf("! 你完蛋了 !");
					else
						printf("  ");
				}
				printf("\n");
				//交互栏
				map_print_y++;
			}
		}
		print_ud();
		//下边框
		print_tips();
		//提示栏
		break;
	case 1:
		switch (map_key)
		{
		case 1:
			print_ud();
			//上边框
			map_print_y = 1;
			while (map_print_y < 26)
			{
				for (; 0 < map_print_y && map_print_y < 7; map_print_y++)
				{
					print_eg();
					//单个侧边框
				}
				for (; 19 < map_print_y && map_print_y < 26; map_print_y++)
				{
					print_eg();
					//单个侧边框
				}
				for (; 6 < map_print_y && map_print_y < 20; map_print_y++)
				{
					map_print_x = 1;
					while (0 < map_print_x && map_print_x < 50)
					{
						for (; 0 < map_print_x && map_print_x < 9; map_print_x++)
						{
							if (map_print_x == 1)
								printf("██");
							else
								printf("  ");
						}
						for (; 41 < map_print_x && map_print_x < 50; map_print_x++)
						{
							if (map_print_x == 49)
								printf("██\n");
							else
								printf("  ");
						}
						for (; 8 < map_print_x && map_print_x < 42; map_print_x++)
						{
							if (map_print_x - 8 == apple_x && map_print_y - 6 == apple_y)
								printf("〇");
							else
							{
								print_n = now_s;
								if (print_n == 0)
									if (*snake_map == map_print_x - 8 && *(snake_map + 1) == map_print_y - 6)
										printf("囧");
									else
										printf("、");
								else
									if (*snake_map == map_print_x - 8 && *(snake_map + 1) == map_print_y - 6)
										printf("囧");
									else
									{
										print_n_n = 0;//重置记录数
										for (; print_n > 0; print_n--)
										{
											if (*(snake_map + print_n * 2) == map_print_x - 8 && *(snake_map + print_n * 2 + 1) == map_print_y - 6)
											{
												print_n_n = 1;
												printf("囗");
												break;
											}
											//检测是否是蛇囗,有则记录,并输出蛇囗
										}
										if (print_n_n == 0)//无记录则输出背景
											printf("、");
									}
							}
						}
					}
				}
				//交互栏
			}
			print_ud();
			//下边框
			print_tips();
			//提示栏
			break;
		case 2:
			print_ud();
			//上边框
			map_print_y = 1;
			while (map_print_y < 26)
			{
				for (; 0 < map_print_y && map_print_y < 4; map_print_y++)
				{
					print_eg();
					//单个侧边框
				}
				for (; 22 < map_print_y && map_print_y < 26; map_print_y++)
				{
					print_eg();
					//单个侧边框
				}
				for (; 3 < map_print_y && map_print_y < 23; map_print_y++)
				{
					map_print_x = 1;
					while (0 < map_print_x && map_print_x < 50)
					{
						for (; 0 < map_print_x && map_print_x < 5; map_print_x++)
						{
							if (map_print_x == 1)
								printf("██");
							else
								printf("  ");
						}
						for (; 45 < map_print_x && map_print_x < 50; map_print_x++)
						{
							if (map_print_x == 49)
								printf("██\n");
							else
								printf("  ");
						}
						for (; 4 < map_print_x && map_print_x < 46; map_print_x++)
						{
							if (map_print_x - 4 == apple_x && map_print_y - 3 == apple_y)
								printf("〇");
							else
							{
								print_n = now_s;
								if (print_n == 0)
									if (*snake_map == map_print_x - 4 && *(snake_map + 1) == map_print_y - 3)
										printf("囧");
									else
										printf("、");
								else
									if (*snake_map == map_print_x - 4 && *(snake_map + 1) == map_print_y - 3)
										printf("囧");
									else
									{
										print_n_n = 0;//重置记录数
										for (; print_n > 0; print_n--)
										{
											if (*(snake_map + print_n * 2) == map_print_x - 4 && *(snake_map + print_n * 2 + 1) == map_print_y - 3)
											{
												print_n_n = 1;
												printf("囗");
												break;
											}
											//检测是否是蛇囗,有则记录,并输出蛇囗
										}
										if (print_n_n == 0)//无记录则输出背景
											printf("、");
									}
							}
						}
					}
				}
				//交互栏
			}
			print_ud();
			//下边框
			print_tips();
			//提示栏
			break;
		case 3:
			print_ud();
			//上边框
			map_print_y = 1;
			while (map_print_y < 26)
			{
				for (; 1 < map_print_y && map_print_y < 25; map_print_y++)
				{
					map_print_x = 1;
					while (0 < map_print_x && map_print_x < 50)
					{
						if (map_print_x == 1 || map_print_x == 49)
						{
							printf("██");
							map_print_x++;
						}
						for (; 1 < map_print_x && map_print_x < 49; map_print_x++)
						{
							if (map_print_x - 1 == apple_x && map_print_y - 1 == apple_y)
								printf("〇");
							else
							{
								print_n = now_s;
								if (print_n == 0)
									if (*snake_map == map_print_x - 1 && *(snake_map + 1) == map_print_y - 1)
										printf("囧");
									else
										printf("、");
								else
									if (*snake_map == map_print_x - 1 && *(snake_map + 1) == map_print_y - 1)
										printf("囧");
									else
									{
										print_n_n = 0;//重置记录数
										for (; print_n > 0; print_n--)
										{
											if (*(snake_map + print_n * 2) == map_print_x - 1 && *(snake_map + print_n * 2 + 1) == map_print_y - 1)
											{
												print_n_n = 1;
												printf("囗");
												break;
											}
											//检测是否是蛇囗,有则记录,并输出蛇囗
										}
										if (print_n_n == 0)//无记录则输出背景
											printf("、");
									}
							}
						}
					}
					printf("\n");
				}
				//交互栏
				if (map_print_y == 1 || map_print_y == 25)
					map_print_y++;
			}
			print_ud();
			//下边框
			print_tips();
			//提示栏
			break;
		}
		break;
	}
}
//打印
void apple_x_y(int map_n, int* apple_x, int* apple_y,int *snake_map)
{
	int apple_n=now_s;
	for (; apple_n > 0; apple_n--)
	{
		switch (map_n)
		{
		case 1:
			*apple_x = rand() % 32 + 1;
			*apple_y = rand() % 12 + 1; return;
		case 2:
			*apple_x = rand() % 40 + 1;
			*apple_y = rand() % 18 + 1; return;
		case 3:
			*apple_x = rand() % 48 + 1;
			*apple_y = rand() % 24 + 1; return;
		default:printf("生成果子失败");
		}
	if (*(snake_map + apple_n * 2) != *apple_x || *(snake_map + apple_n * 2 + 1) != * apple_x)
			return;
	}
}
//生成果子坐标,并检验是否在蛇身上,不在蛇身上就输出
int snake_self(int* snake_map, int snake_x, int snake_y)
{
	int self_n = now_s;
	for (; self_n > 0; self_n--)
	{
		if (*(snake_map + self_n * 2) == snake_x && *(snake_map + self_n * 2 + 1) == snake_y)
			return 1;
	}
	return 0;
}
//蛇撞自身判定
void snake_ctrl(int* snake_x, int* snake_y, char* snake_ctrl_a)
{
	*snake_ctrl_a = _getch();
	if (*snake_ctrl_a == 27)
	{
		main();
		return;
	}
	switch (*snake_ctrl_a)
	{
	case 27:main(); return;
	case 'a':--*snake_x; break;
	case 'd':++*snake_x; break;
	case 's':++*snake_y; break;
	case 'w':--*snake_y; break;
	case 'p':while (!_kbhit()); break;
	default:break;
	}
}
//蛇头的控制,游戏界面的控制
void map_1(int set_range_map)
{
	int eat_1_n, apple_1_x = 21, apple_1_y = 7, snake_1_x = 10, snake_1_y = 7, snake_1_s[1081][2] = {0};//初始化
	char snake_ctrl_1='d';
	now_s = 0;
	while (1)
	{
		eat_1_n = now_s;
		switch (time_gap(set_level_speed))//根据难度限制时间
		{
		case 0:
			switch (snake_ctrl_1)//自动化前进
			{
			case 'a':--snake_1_x; break;
			case 'd':++snake_1_x; break;
			case 's':++snake_1_y; break;
			case 'w':--snake_1_y; break;
			default:;
			}
			break;
		case 1:
			snake_ctrl(&snake_1_x, &snake_1_y, &snake_ctrl_1);//获得控制
			break;
		default:;
		}
		if (snake_1_x == apple_1_x && snake_1_y == apple_1_y)
		{
			now_s++;
			apple_x_y(set_range_map, &apple_1_x, &apple_1_y, snake_1_s);
			if (now_s > record_s)
				record_s = now_s;
		}
		//判定蛇吃果，并生成新果子
		for (; eat_1_n > 0; eat_1_n--)
		{
			snake_1_s[eat_1_n][0] = snake_1_s[eat_1_n - 1][0];
			snake_1_s[eat_1_n][1] = snake_1_s[eat_1_n - 1][1];
		}
		//记录蛇身的位置
		snake_1_s[0][0] = snake_1_x;
		snake_1_s[0][1] = snake_1_y;
		//定位蛇头
		if (set_range_map == 1)
		{
			if (snake_1_x < 1 || 33 < snake_1_x || snake_1_y < 1 || 13 < snake_1_y || snake_self(snake_1_s, snake_1_x, snake_1_y))
			{
				map_print(1, 0, snake_1_s, apple_1_x, apple_1_y);
				if (_getch() == '\r')
					break;
			}
		}
		if (set_range_map == 2)
		{
			if (snake_1_x < 1 || 41 < snake_1_x || snake_1_y < 1 || 19 < snake_1_y || snake_self(snake_1_s, snake_1_x, snake_1_y))
			{
				map_print(2, 0, snake_1_s, apple_1_x, apple_1_y);
				if (_getch() == '\r')
					break;
			}
		}
		if (set_range_map == 3)
		{
			if (snake_1_x < 1 || 47 < snake_1_x || snake_1_y < 1 || 23 < snake_1_y || snake_self(snake_1_s, snake_1_x, snake_1_y))
			{
				map_print(3, 0, snake_1_s, apple_1_x, apple_1_y);
				if (_getch() == '\r')
					break;


			}
		}
		//判定撞墙和撞自身
		map_print(set_range_map, 1, snake_1_s, apple_1_x, apple_1_y);
	}
}
//地图
void main_intetface(int x)
{
	int main_x, main_y;
	print_ud();
	//上边框
	main_y = 1;
	while (main_y < 26)
	{
		while (main_y != 13 && main_y != 12 && main_y != 14 && main_y < 26)
		{
			print_eg();
			//单个侧边框
			main_y++;
		}
		if (main_y == 12 || main_y == 13 || main_y == 14)
		{
			main_x = 1;
			for (; main_x < 45 && x == 1; main_x++)
			{
				if (main_x == 1 || main_x == 44)
					printf("██");
				else if (main_x == 23 && main_y == 12)
					printf("    设置    ");
				else if (main_x == 23 && main_y == 13)
					printf("》开始游戏《");
				else if (main_x == 23 && main_y == 14)
					printf("    退出    ");
				else
					printf("  ");
			}
			for (; main_x < 45 && x == 2; main_x++)
			{
				if (main_x == 1 || main_x == 44)
					printf("██");
				else if (main_x == 23 && main_y == 12)
					printf("    退出    ");
				else if (main_x == 23 && main_y == 13)
					printf("》  设置  《");
				else if (main_x == 23 && main_y == 14)
					printf("  开始游戏  ");
				else
					printf("  ");
			}
			for (; main_x < 45 && x == 3; main_x++)
			{
				if (main_x == 1 || main_x == 44)
					printf("██");
				else if (main_x == 23 && main_y == 12)
					printf("  开始游戏  ");
				else if (main_x == 23 && main_y == 13)
					printf("》  退出  《");
				else if (main_x == 23 && main_y == 14)
					printf("    设置    ");
				else
					printf("  ");
			}
			printf("\n");
			//交互栏
			main_y++;
		}
	}
	print_ud();
	//下边框
	print_tips();
	//提示栏
}
//主界面
int main()
{
	int main_a;
	char main_ctrl;
	main_a = 1;
	main_ctrl = '\0';
	while (1)
	{
		main_intetface(main_a);
		main_ctrl = _getch();
		if (main_ctrl == '\r')
		{
			switch (main_a)
			{
			case 1:
				map_1(set_range_map); break;
			case 2:
				set_ctrl_intetface(); break;//进入设置控制
			case 3:
				exit(0); break;
			default:printf("选择失败");
			}
		}
		else if (main_ctrl == 's')
			--main_a;
		else if (main_ctrl == 'w')
			++main_a;
		if (main_a == 0)
			main_a = 3;
		else if (main_a == 4)
			main_a = 1;
	}
	return 0;
}
//主界面控制