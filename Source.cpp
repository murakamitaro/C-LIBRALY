#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<windows.h>
#define SIZE 8
//カーソル移動からの決定で破壊

int main(void) {
	int field[SIZE][SIZE] = { 0 };	//-1:地雷　	0～:周囲の爆弾の数 ★ここ16進数でやる！！
	int field_status[SIZE][SIZE] = {};		//1;堀ったとこ　0:掘ってないとこ
	int i, j;
	int n, m;
	int mine_cnt = 0;
	

	srand((unsigned)time(NULL));

	//地雷をセット
	for (i = 0;i < 10;i++) {
		field[rand() % 8][rand() % 8] = -1;
	}

	//地雷のない箇所に　周囲3*3の範囲の地雷の個数をセット
	for (i = 0;i < SIZE;i++) {
		for (j = 0;j < SIZE;j++) {
			if (field[i][j] != -1) {//地雷マス以外なら

				mine_cnt =0;//地雷数初期化
				for (n = -1;n <=1 ;n++) {
					for (m = -1;m <=1;m++) {
						if (0 <= i + n && i + n <= 7 && 0 <= j + m && j + m <= 7) {
							if (field[i+n][j+m] == -1) {
								mine_cnt++;
							}
						}
					}
				}
				field[i][j] = mine_cnt;
			}
		}
	}

	for (i = 0;i < SIZE;i++) {
		for (j = 0;j < SIZE;j++) {
			if (field[i][j] == -1) {
				printf(" B ");
			}
			else {
				printf("%2d ", field[i][j]);
			}
		}
		printf("\n");
	}printf("\n\n");

	system("pause");
}