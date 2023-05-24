#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<queue>
#include<iostream>
#include<Windows.h>

#pragma comment(lib, "user32.lib")

#define MAP_SIZE 23

using namespace std;

typedef struct {
	int qX;
	int qY;
	int qturn;
}queuedata;

queue<queuedata>que;

int map[MAP_SIZE][MAP_SIZE] = { 0 };
int cursorY = 0, cursorX = 0;
int x = 1, y = 1;

void show();
void creatmap();
void check();

int main() {
	int backy = 0, backx = 0;
	creatmap();
	printf("↑キーで上に移動\n");
	printf("↓キーで下に移動\n");
	printf("←キーで左に移動\n");
	printf("→キーで右に移動\n");
	printf("スペースキーでプログラムを終了\n");
	printf("\nキーを入力して開始\n");
	_getch();
	while (1) {
		system("cls");
		show();
		printf("%d %d", cursorY, cursorX);
		if (map[cursorY][cursorX] == 6) {
			break;
		}
		backx = cursorX, backy = cursorY;
		switch (_getch()) {
		case 0x48: //上
			cursorY--;
			break;
		case 0x4b: //左
			cursorX--;
			break;
		case 0x50: //下
			cursorY++;
			break;
		case 0x4d: //右
			cursorX++;
			break;
		case 0x20://space
			return 0;
		}

		if (map[cursorY][cursorX] == 0 || map[cursorY][cursorX] == 3) {
			cursorY = backy, cursorX = backx;
		}

	}
	MessageBox(NULL, TEXT("ゴールおめでとうございます!"), TEXT("ゴール"), MB_OK | MB_ICONINFORMATION);
	return 0;
}

void show() {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (i == cursorY && j == cursorX) {
				printf("◎");
			}
			else {
				switch (map[i][j]) {
				case 0:
					printf("□");//壁
					break;
				case 1:
					printf("  ");//道
					break;
				case 3:
					printf("■");//外壁
					break;
				case 5:
					printf("ｓ");//スタート
					break;
				case 6:
					printf("ｇ");//ゴール
					break;
				}
			}
		}
		printf("\n");
	}
}

void creatmap() {
	int ay[4] = { -1,0,0,1 };
	int ax[4] = { 0,-1,1,0 };
	for (int i = 0; i < MAP_SIZE; i++) {
		map[i][0] = 3;
		map[i][MAP_SIZE - 1] = 3;
		map[0][i] = 3;
		map[MAP_SIZE - 1][i] = 3;
	}
	map[y][x] = 1;
	for (x = 1; x < MAP_SIZE - 1; x += 2) {
		for (y = 1; y < MAP_SIZE - 1; y += 2) {

			//for(y=2;y<mapsize-2;y+=2){
			//	for (x = 2; x < mapsize-2; x+=2) {
			if (map[y][x] == 1) {
				int x1 = x, y1 = y;
				int check = 0;
				int count = 0;
				while (1) {
					count++;
					int no = 0;
					srand((unsigned)time(NULL));
					int a = rand();
					srand(a + check + x1 + y1 + count + y * x);
					no = rand() % 4;
					if (map[y1 + ay[no]][x1 + ax[no]] == 0 && map[y1 + ay[no] * 2][x1 + ax[no] * 2] == 0) {
						map[y1 + ay[no]][x1 + ax[no]] = 1;//1マスとなり
						map[y1 + ay[no] * 2][x1 + ax[no] * 2] = 1;//2マス先

						y1 = y1 + ay[no] * 2;
						x1 = x1 + ax[no] * 2;
					}
					else {
						if (check == 4) {
							break;
						}
						else {
							check++;
						}
					}

				}
			}
		}
	}
	check();
}

void check() {
	//show();
	int turn = 0;
	int checkmap[23][23] = { 0 };
	//初期位置をランダムに選ぶ
	srand((unsigned)time(NULL));
	y = rand() % (MAP_SIZE - 1) + 1;
	srand(y * y);
	x = rand() % (MAP_SIZE - 1) + 1;
	//printf("y%d x%d\n", y, x);
	int ay[4] = { -1,0,0,1 };
	int ax[4] = { 0,-1,1,0 };

	que.push(queuedata{ x, y, 0 });
	queuedata data;
	data.qturn = -1;
	data.qX = x;
	data.qY = y;
	checkmap[y][x] = 1;
	while (!que.empty()) {
		queuedata xy = que.front();//取り出し
		if (data.qturn <= xy.qturn) {
			data.qturn = xy.qturn;
			data.qX = xy.qX;
			data.qY = xy.qY;
		}
		//printf("%d %d %d\n", xy.qY, xy.qX, xy.qturn);
		que.pop();//削除
		for (int i = 0; i < 4; i++) {
			queuedata datacheck;
			datacheck.qturn = xy.qturn;
			datacheck.qX = xy.qX;
			datacheck.qY = xy.qY;
			if (checkmap[xy.qY + ay[i]][xy.qX + ax[i]] == 0 && map[xy.qY + ay[i]][xy.qX + ax[i]] == 1) {
				que.push(queuedata{ datacheck.qX + ax[i],datacheck.qY + ay[i],datacheck.qturn + 1 });//追加
			}
			checkmap[datacheck.qY + ay[i]][datacheck.qX + ax[i]] = 1;
		}
	}
	map[data.qY][data.qX] = 5;
	//printf("\n");
	cursorY = data.qY, cursorX = data.qX;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			checkmap[i][j] = 0;
		}
	}
	//printf("y%d x%d\n", data.qY, data.qX);
	que.push(queuedata{ cursorX,cursorY, 0 });
	data.qturn = -1;
	data.qX = cursorX;
	data.qY = cursorY;
	checkmap[data.qY][data.qX] = 1;
	while (!que.empty()) {
		queuedata xy = que.front();//取り出し
		if (data.qturn <= xy.qturn) {
			data.qturn = xy.qturn;
			data.qX = xy.qX;
			data.qY = xy.qY;
		}
		//printf("%d %d %d\n", xy.qY, xy.qX, xy.qturn);
		que.pop();//削除
		for (int i = 0; i < 4; i++) {
			queuedata datacheck;
			datacheck.qturn = xy.qturn;
			datacheck.qX = xy.qX;
			datacheck.qY = xy.qY;
			if (checkmap[xy.qY + ay[i]][xy.qX + ax[i]] == 0 && map[xy.qY + ay[i]][xy.qX + ax[i]] == 1) {
				que.push(queuedata{ datacheck.qX + ax[i],datacheck.qY + ay[i],datacheck.qturn + 1 });//追加
			}
			checkmap[datacheck.qY + ay[i]][datacheck.qX + ax[i]] = 1;
		}
	}
	map[data.qY][data.qX] = 6;

}