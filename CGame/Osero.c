#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

#pragma comment(lib, "user32.lib")

#define MAP_SIZE 8

#define NO_ITEM 0
#define PLAYER1 1
#define PLAYER2 2
#define CAN_PLACE 5

int map[MAP_SIZE + 2][MAP_SIZE + 2] = { 0 };
int cursorX = 1, cursorY = 1;
int turn = 2, turn2 = 1;

typedef struct
{
	int Player1, Player2, NoItem, CanPlace;

}Item_Count;

void show();
void put(int y, int x);
void check();
Item_Count count();

int main() {
	map[4][4] = map[5][5] = PLAYER1;
	map[4][5] = map[5][4] = PLAYER2;
	int noPut = 0;
	Item_Count item;
	while (1) {
		turn = turn % 2 + 1;
		turn2 = 3 - turn;

		check();
		item = count();
		if (noPut == 2) {
			break;
		}
		if (item.CanPlace == 0) {
			noPut++;
			continue;
		}
		while (1) {
			system("cls");
			show();
			if (turn == PLAYER1) {
				printf("���̃^�[��\n");
			}
			else if (turn == PLAYER2) {
				printf("���̃^�[��\n");
			}
			printf("1p %d\t2p %d\n", item.Player1, item.Player2);
			int back_y = cursorY, back_x = cursorX;
			int doNotPut = 0;
			int y = 0, x = 0;
			switch (_getch()) {
			case 0x48: //��
				cursorY--;
				break;
			case 0x4b: //��
				cursorX--;
				break;
			case 0x50: //��
				cursorY++;
				break;
			case 0x4d: //�E
				cursorX++;
				break;
			case 0x0d: //�I��
				y = cursorY, x = cursorX;
				if (1 <= x && x <= MAP_SIZE && 1 <= y && y <= MAP_SIZE) {
					if (map[y][x] == CAN_PLACE) {
						put(y, x);
						if (map[y][x] == turn)doNotPut = 1, noPut = 0;
					}
				}
				break;
			}
			if (cursorX < 1 || cursorX>MAP_SIZE || cursorY < 1 || cursorY>MAP_SIZE) {
				cursorX = back_x, cursorY = back_y;
			}
			if (doNotPut == 1)break;
		}

	}
	if (item.Player1 > item.Player2) {
		MessageBox(NULL, TEXT("1p�̏���!!"), TEXT("���s"), MB_OK | MB_ICONINFORMATION);
	}
	else if (item.Player1 < item.Player2) {
		MessageBox(NULL, TEXT("2p�̏���!!"), TEXT("���s"), MB_OK | MB_ICONINFORMATION);
	}
	else {
		MessageBox(NULL, TEXT("��������!!"), TEXT("���s"), MB_OK | MB_ICONINFORMATION);
	}
	return 0;
}

void show() {
	for (int i = 1; i <= MAP_SIZE; i++) {
		for (int j = 1; j <= MAP_SIZE; j++) {
			if (cursorY == i && cursorX == j) {
				printf("��");
			}
			else {
				switch (map[i][j]) {
				case NO_ITEM:
					printf("��");
					break;
				case CAN_PLACE:
					printf("��");
					break;
				case PLAYER1:
					printf("��");
					break;
				case PLAYER2:
					printf("��");
					break;
				}
			}
		}
		printf("\n");
	}
}

void put(int y, int x) {
	if (map[y][x] != CAN_PLACE) {
		return;
	}
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			int b = 0;
			for (int k = 1; k <= MAP_SIZE; k++) {
				if (map[y + i * k][x + j * k] == turn) {
					if (b == 1) {
						for (int l = k; l >= 0; l--) {
							map[y + i * l][x + j * l] = turn;
						}
					}
					break;
				}
				else if (map[y + i * k][x + j * k] == turn2) {
					b = 1;
				}
				else {
					break;
				}
			}
		}
	}
}

void check() {
	for (int y = 1; y <= MAP_SIZE; y++) {
		for (int x = 1; x <= MAP_SIZE; x++) {
			if (map[y][x] == CAN_PLACE)map[y][x] = NO_ITEM;
			if (map[y][x] == NO_ITEM) {
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						int b = 0;
						for (int k = 1; k <= MAP_SIZE; k++) {
							if (map[y + i * k][x + j * k] == turn) {
								if (b == 1) {
									map[y][x] = CAN_PLACE;
									i = 2, j = 2;
								}
								break;
							}
							else if (map[y + i * k][x + j * k] == turn2) {
								b = 1;
							}
							else {
								break;
							}
						}
					}
				}
			}
		}
	}
}

Item_Count count() {
	Item_Count item = { 0,0,0,0 };
	for (int i = 1; i <= MAP_SIZE; i++) {
		for (int j = 1; j <= MAP_SIZE; j++) {
			switch (map[i][j]) {
			case NO_ITEM:
				item.NoItem++;
				break;
			case PLAYER1:
				item.Player1++;
				break;
			case PLAYER2:
				item.Player2++;
				break;
			case CAN_PLACE:
				item.CanPlace++;
				break;
			}
		}
	}
	return item;
}