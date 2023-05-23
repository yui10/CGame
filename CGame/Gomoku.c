#include<stdio.h>
#include<string.h>

#define NO_ITEM -1
#define PLAYER1 0
#define PLAYER2 1
#define MAX_SIZE 13	//mapのサイズ
#define PUT_MAX 5	//揃えるべき数

int Puts(int, int, int map[][MAX_SIZE + 2]);
int show(int map[][MAX_SIZE + 2]);

int main(void) {
	int map[MAX_SIZE + 2][MAX_SIZE + 2];
	memset(map, NO_ITEM, sizeof(map));
	int* p = map;
	int now_player = 0;
	int game_flag = 1;
	int turn = 1;

	/*for (int i = 0; i < (MAX_SIZE + 2) * (MAX_SIZE + 2); i++) {
		*(p + i) = NO_ITEM;
	}*/

	while (game_flag) {
		if (show(p) <= 0) {
			printf("置くところが無くなったのでプログラムを終了します。\n");
			return 0;
		}

		printf("%d手目\n", turn);
		if (!now_player)printf("●のターン\n");
		else printf("×のターン\n");

		int flag = 1;
		while (flag) {
			char str[3] = { "" };
			int x = 0;

			scanf_s("%s", str, 3);
			sscanf_s(str, "%d", &x);

			switch (Puts(x, now_player, p)) {
			case -2:
				printf("そこには置くことが出来ません\n");
				break;
			case -1:
				printf("1～%dまでの数字を入力してください\n", MAX_SIZE);
				break;
			case 0:
				flag = 0;
				break;
			case 10:
			case 11:
				game_flag = 0, flag = 0;
				break;
			default:
				break;
			}
		}
		now_player = !now_player;
		turn++;
	}

	printf("\n\n");
	show(p);
	printf("Player%dの勝利\n\n", (!now_player) + 1);
	return 0;
}

int Puts(int x, int putdata, int map[][MAX_SIZE + 2]) {
	if (x < 1 || MAX_SIZE < x)return -1;

	int i = 0, j = 0, k = 0;
	int y = 0;

	for (i = MAX_SIZE; i >= 1; i--) {
		if (map[i][x] == NO_ITEM) {
			map[i][x] = putdata;
			y = i;
			break;
		}
	}

	if (y < 1)return -2;

	int value[10] = { 0 };
	int value_count = 1;

	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			int count = 0;
			if (i == 0 && j == 0) {
				count = 1;
			}
			else if (map[y + i][x + j] == putdata) {
				for (k = 1; k < MAX_SIZE; k++) {
					if (map[y + i * k][x + j * k] == putdata) {
						count++;
					}
					else {
						break;
					}
				}
			}
			value[value_count] = count;
			value_count++;
		}
	}

	for (i = 1; i <= 4; i++) {
		if (value[i] + value[5] + value[10 - i] >= PUT_MAX) {
			return putdata + 10;
		}
	}

	return 0;
}

int show(int map[][MAX_SIZE + 2]) {
	int count = 0;
	for (int i = 1; i <= MAX_SIZE; i++) {
		printf("%2d", i);
	}
	printf("\n");
	for (int i = 1; i <= MAX_SIZE; i++) {
		for (int j = 1; j <= MAX_SIZE; j++) {
			switch (map[i][j]) {
			case PLAYER1:
				printf("●");
				break;
			case PLAYER2:
				printf("×");
				break;
			case NO_ITEM:
				printf("□");
				count++;
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
	return count;
}
