#include<graphics.h>
#include<windows.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<math.h>

struct BLOCK {
	int x;
	int y;
}block[4], block1[4];//方块的四个方块的坐标

struct CHART {
	int num[4][4];
}chart[19];//19种方块的坐标

int gridding[28][12], gridd[4][4];//存储网格信息
int i, j, k, m, n, p, q;//循环中的变量名
int chart_num;//19种方块的编号
int grade = 0; char s[11];//分数 
int x, flag = 0;//方块是否到底的判断标志 

void init_Gridding()//初始化网格
{
	for (i = 0; i < 28; i++) {
		for (j = 0; j < 12; j++) {
			gridding[i][j] = 0;
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			gridd[i][j] = 0;
		}
	}
}

void draw_GriddingAndBlocks()//画出网格内的格子
{
	for (i = 4; i < 28; i++) {
		for (j = 0; j < 12; j++) {
			if (gridding[i][j] == 0) {
				setfillcolor(RGB(190, 190, 190));
				fillrectangle(j * 20, (i - 4) * 20, (j + 1) * 20, (i - 3) * 20);
			}
			else {
				setfillcolor(RGB(50, 150, 200));
				fillrectangle(j * 20, (i - 4) * 20, (j + 1) * 20, (i - 3) * 20);
			}
		}
	}
}

void draw_GriddingAndBlocks1()//画出预测网格内的格子
{
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (gridd[i][j] == 0) {
				setfillcolor(RGB(190, 190, 190));
				fillrectangle((j + 13) * 20, (i + 1) * 20, (j + 14) * 20, (i + 2) * 20);
			}
			else {
				setfillcolor(RGB(50, 150, 200));
				fillrectangle((j + 13) * 20, (i + 1) * 20, (j + 14) * 20, (i + 2) * 20);
			}
		}
	}
}

void Read_Chart() {//将所有图形读进数组chart
	FILE* fp;
	fp = fopen("E:\\dazuoye/chart.txt", "r");
	if (fp == NULL) {
		exit(-1);
	}
	else {
		for (i = 0; i < 19; i++) {
			for (j = 0; j < 4; j++) {
				for (k = 0; k < 4; k++) {
					fscanf(fp, "%d", &chart[i].num[j][k]);
				}
			}
		}
	}
}

void initRandomNum() {//生成随机数
	srand((unsigned)time(NULL));
	x = rand() % 19;
}

void GetBlockX_Y() {//获取随机图形四个方块的对应坐标
	int count = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (chart[chart_num].num[i][j] == 2) {
				block[count].x = i;
				block[count].y = j + 4;//向右移动四个单位，保证生成方块在屏幕中间
				gridding[block[count].x][block[count].y] = 2;//刷新方块在网格位置
				count++;
			}
		}
	}
}

void GetBlock1X_Y() {//获取预测随机图形四个方块的对应坐标
	int count = 0;
	memset(gridd, 0, sizeof(gridd));
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (chart[x].num[i][j] == 2) {
				block1[count].x = i;
				block1[count].y = j;//向右移动四个单位，保证生成方块在屏幕中间
				gridd[block1[count].x][block1[count].y] = 2;//刷新方块在网格位置
				count++;
			}
		}
	}
}

int MoveBlockDown() {//控制方块向下加速移动
	for (i = 0; i < 4; i++) {
		if (block[i].x == 27) {
			for (k = 0; k < 4; k++) {
				gridding[block[k].x][block[k].y] = 1;
			}
			return 0;
		}
	}
	for (j = 0; j < 4; j++) {
		if (gridding[block[j].x + 1][block[j].y] == 1) {
			for (m = 0; m < 4; m++) {
				gridding[block[m].x][block[m].y] = 1;
			}
			return 0;
		}
	}
	for (n = 0; n < 4; n++) {
		gridding[block[n].x][block[n].y] = 0;
	}
	for (p = 0; p < 4; p++) {
		block[p].x++;
	}
	for (q = 0; q < 4; q++) {
		gridding[block[q].x][block[q].y] = 2;
	}
	return 1;
}

void MoveBlockLeft() {//控制方块向左移动
	for (i = 0; i < 4; i++) {
		if (block[i].y <= 0) {
			return;
		}
	}
	for (j = 0; j < 4; j++) {
		if (gridding[block[j].x][block[j].y - 1] == 1) {
			return;
		}
	}
	for (k = 0; k < 4; k++) {
		gridding[block[k].x][block[k].y] = 0;
	}
	for (m = 0; m < 4; m++) {
		block[m].y--;
	}
	for (n = 0; n < 4; n++) {
		gridding[block[n].x][block[n].y] = 2;
	}
}

void MoveBlockRight() {//控制方块向右移动
	for (i = 0; i < 4; i++) {
		if (block[i].y >= 11) {
			return;
		}
	}
	for (j = 0; j < 4; j++) {
		if (gridding[block[j].x][block[j].y + 1] == 1) {
			return;
		}
	}
	for (k = 0; k < 4; k++) {
		gridding[block[k].x][block[k].y] = 0;
	}
	for (m = 0; m < 4; m++) {
		block[m].y++;
	}
	for (n = 0; n < 4; n++) {
		gridding[block[n].x][block[n].y] = 2;
	}
}

void ChangeBlockShape() {//控制方块变换形状
	if (chart_num == 0) {
		if (block[3].y < 11) {
			if (gridding[block[2].x][block[2].y + 1] != 1 && gridding[block[2].x][block[2].y + 2] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;//原位置置0
				}
				block[0].x++;
				block[1].y++;
				block[2].x--;
				block[2].y += 2;
				block[3].y--;
				for (m = 0; m < 4; m++) {//重新赋值更新位置信息
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num++;
			}
		}
	}
	else if (chart_num == 1) {
		if (gridding[block[1].x - 1][block[1].y] != 1 && gridding[block[1].x + 1][block[1].y] != 1) {
			for (k = 0; k < 4; k++) {
				gridding[block[k].x][block[k].y] = 0;
			}
			block[0].x--;
			block[1].x--;
			block[2].y--;
			block[3].y++;
			for (m = 0; m < 4; m++) {
				gridding[block[m].x][block[m].y] = 2;
			}
			chart_num++;
		}
	}
	else if (chart_num == 2) {
		if (block[0].y > 0 && block[1].y > 0 && block[2].y > 0 && block[3].y > 0) {
			if (gridding[block[3].x][block[3].y - 1] != 1 && gridding[block[3].x][block[3].y - 2] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[0].x++;
				block[0].y++;
				block[1].x += 2;
				block[1].y -= 2;
				block[2].x++;
				block[2].y--;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num++;
			}
		}
	}
	else if (chart_num == 3) {
		if (gridding[block[2].x - 1][block[2].y] != 1 && gridding[block[2].x - 2][block[2].y] != 1) {
			for (k = 0; k < 4; k++) {
				gridding[block[k].x][block[k].y] = 0;
			}
			block[0].x--;
			block[0].y--;
			block[1].x--;
			block[1].y++;
			for (m = 0; m < 4; m++) {
				gridding[block[m].x][block[m].y] = 2;
			}
			chart_num = 0;
		}
	}
	else if (chart_num == 4) {
		if (block[2].y > 0) {
			if (gridding[block[1].x][block[1].y - 2] != 1 && gridding[block[2].x][block[2].y - 1] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[0].x++;
				block[0].y -= 2;
				block[1].x++;
				block[1].y -= 2;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num++;
			}
		}
	}
	else if (chart_num == 5) {
		if (gridding[block[0].x - 1][block[0].y] != 1 && gridding[block[2].x - 2][block[2].y] != 1) {
			for (k = 0; k < 4; k++) {
				gridding[block[k].x][block[k].y] = 0;
			}
			block[0].x--;
			block[1].x -= 2;
			block[1].y++;
			block[2].x--;
			block[2].y--;
			block[3].y -= 2;
			for (m = 0; m < 4; m++) {
				gridding[block[m].x][block[m].y] = 2;
			}
			chart_num++;
		}
	}
	else if (chart_num == 6) {
		if (block[1].y < 11) {
			if (gridding[block[1].x + 1][block[1].y] != 1 && gridding[block[2].x][block[2].y + 2] != 1 && gridding[block[3].x][block[3].y + 2] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[0].x++;
				block[1].x++;
				block[2].y += 2;
				block[3].y += 2;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num++;
			}
		}
	}
	else if (chart_num == 7) {
		if (gridding[block[2].x + 1][block[2].y - 1] != 1) {
			for (k = 0; k < 4; k++) {
				gridding[block[k].x][block[k].y] = 0;
			}
			block[0].x--;
			block[0].y += 2;
			block[1].y++;
			block[2].x++;
			block[2].y--;
			for (m = 0; m < 4; m++) {
				gridding[block[m].x][block[m].y] = 2;
			}
			chart_num = 4;
		}
	}
	else if (chart_num == 8) {
		if (block[0].x < 23) {
			if (gridding[block[3].x + 1][block[3].y - 1] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[0].x -= 2;
				block[0].y += 2;
				block[1].x--;
				block[1].y++;
				block[3].x++;
				block[3].y--;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num++;
			}
		}
	}
	else if (chart_num == 9) {
		if (block[0].y < 11) {
			if (gridding[block[2].x][block[2].y - 2] != 1 && gridding[block[2].x][block[2].y - 1] != 1 && gridding[block[2].x][block[2].y + 1] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[0].x += 2;
				block[0].y -= 2;
				block[1].x++;
				block[1].y--;
				block[3].x--;
				block[3].y++;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num = 8;
			}
		}
	}
	else if (chart_num == 10) {
		if (block[2].x < 23) {
			if (gridding[block[0].x][block[0].y - 1] != 1 && gridding[block[3].x + 1][block[3].y] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[0].y--;
				block[1].x++;
				block[1].y -= 2;
				block[2].y++;
				block[3].x++;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num++;
			}
		}
	}
	else if (chart_num == 11) {
		if (block[2].y < 11) {
			if (gridding[block[0].x][block[0].y + 1] != 1 && gridding[block[0].x][block[0].y + 2] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[0].y++;
				block[1].x--;
				block[1].y += 2;
				block[2].y--;
				block[3].x--;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num = 10;
			}
		}
	}
	else if (chart_num == 12) {
		if (block[2].x < 23) {
			if (gridding[block[0].x + 1][block[0].y] != 1 && gridding[block[0].x + 2][block[0].y] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[0].y++;
				block[1].x++;
				block[1].y--;
				block[3].x++;
				block[3].y -= 2;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num++;
			}
		}
	}
	else if (chart_num == 13) {
		if (block[0].y < 11) {
			if (gridding[block[0].x][block[0].y - 1] != 1 && gridding[block[2].x][block[2].y + 1] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[0].y--;
				block[1].x--;
				block[1].y++;
				block[3].x--;
				block[3].y += 2;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num = 12;
			}
		}
	}
	else if (chart_num == 14) {
		if (block[1].x < 23) {
			if (gridding[block[2].x + 1][block[2].y] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[1].y++;
				block[2].y++;
				block[3].x++;
				block[3].y--;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num++;
			}
		}
	}
	else if (chart_num == 15) {
		if (gridding[block[1].x][block[1].y - 1] != 1) {
			for (k = 0; k < 4; k++) {
				gridding[block[k].x][block[k].y] = 0;
			}
			block[0].x++;
			block[0].y--;
			for (m = 0; m < 4; m++) {
				gridding[block[m].x][block[m].y] = 2;
			}
			chart_num++;
		}
	}
	else if (chart_num == 16) {
		if (gridding[block[1].x - 1][block[1].y] != 1) {
			for (k = 0; k < 4; k++) {
				gridding[block[k].x][block[k].y] = 0;
			}
			block[0].x--;
			block[0].y++;
			block[1].y--;
			block[2].y--;
			for (m = 0; m < 4; m++) {
				gridding[block[m].x][block[m].y] = 2;
			}
			chart_num++;
		}
	}
	else if (chart_num == 17) {
		if (block[0].y < 11) {
			if (gridding[block[2].x][block[2].y + 1] != 1) {
				for (k = 0; k < 4; k++) {
					gridding[block[k].x][block[k].y] = 0;
				}
				block[3].x--;
				block[3].y++;
				for (m = 0; m < 4; m++) {
					gridding[block[m].x][block[m].y] = 2;
				}
				chart_num = 14;
			}
		}
	}
	else {
		return;
	}
	return;
}

void DestroyOneLineSqare() {//消除一行
	int sum = 0, mpi = 0;
	for (i = 27; i >= 4; i--) {
		for (j = 0; j < 12; j++) {
			if (gridding[i][j] > 0) {
				sum++;
			}
		}
		if (sum == 12) {//消除一行
			for (mpi = i - 1; mpi >= 4; mpi--) {
				for (j = 0; j < 12; j++) {
					gridding[mpi + 1][j] = gridding[mpi][j];
				}
			}
			i = 28;
			grade += 10;
		}
		sum = 0;
	}
	sprintf(s, "%d", grade);
	outtextxy(240 + 55, 200, s);
}

void drawSide()//侧边区域栏的绘制及操作说明
{
	setbkcolor(RGB(190, 190, 190));
	clearrectangle(245, 5, 355, 475);
	settextcolor(RGB(65, 105, 225));
	settextstyle(30, 0, _T("华文楷体"));
	outtextxy(245, 270, _T("操作说明"));
	outtextxy(240 + 5, 300, _T("左移：←"));
	outtextxy(240 + 5, 330, _T("右移：→"));
	outtextxy(240 + 5, 360, _T("变形：↑"));
	outtextxy(240 + 5, 390, _T("下落：↓"));
	sprintf(s, "%d", grade);
	outtextxy(240 + 55, 200, s);
}

int GameOverCheck() {//检查游戏是否结束
	for (i = 0; i < 12; i++) {
		if (gridding[3][i]) {
			MessageBox(NULL, "GameOver", "提示", MB_OK);
			return 0;
		}
	}
	return 1;
}

int main() {//主函数
	initgraph(360, 480);//网格初始化
	drawSide();//右侧区域调用
	init_Gridding();//初始化网格
	Read_Chart();//读取所有方块
	initRandomNum();//产生随机数
	chart_num = x;
	GetBlockX_Y();//获得方块坐标
	draw_GriddingAndBlocks();//画出方块在网格的位置
	draw_GriddingAndBlocks1();
	BeginBatchDraw();
	int move_down_count = 0;
	while (1) {
		GetBlock1X_Y();
		draw_GriddingAndBlocks1();
		if (flag) {
			initRandomNum(); flag = 0;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			ChangeBlockShape();
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			MoveBlockLeft();
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			MoveBlockRight();
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (MoveBlockDown() == 0) {
				DestroyOneLineSqare();
				if (GameOverCheck() == 1) {
					chart_num = x;
					GetBlockX_Y();
					flag = 1;
				}
				else return 0;
			}
		}
		if (move_down_count == 3) {
			if (MoveBlockDown() == 0) {
				DestroyOneLineSqare();
				if (GameOverCheck() == 1) {
					chart_num = x;
					GetBlockX_Y();
					flag = 1;
				}
				else return 0;
			}
			move_down_count = 0;
		}
		else {
			move_down_count++;
		}
		Sleep(100);//下降速度控制
		draw_GriddingAndBlocks();
		FlushBatchDraw();
	}
	EndBatchDraw();
	return 0;
}