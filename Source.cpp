#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<windows.h>
#define SIZE 8
//�J�[�\���ړ�����̌���Ŕj��

int main(void) {
	int field[SIZE][SIZE] = { 0 };	//-1:�n���@	0�`:���͂̔��e�̐� ������16�i���ł��I�I
	int field_status[SIZE][SIZE] = {};		//1;�x�����Ƃ��@0:�@���ĂȂ��Ƃ�
	int i, j;
	int n, m;
	int mine_cnt = 0;
	

	srand((unsigned)time(NULL));

	//�n�����Z�b�g
	for (i = 0;i < 10;i++) {
		field[rand() % 8][rand() % 8] = -1;
	}

	//�n���̂Ȃ��ӏ��Ɂ@����3*3�͈̔͂̒n���̌����Z�b�g
	for (i = 0;i < SIZE;i++) {
		for (j = 0;j < SIZE;j++) {
			if (field[i][j] != -1) {//�n���}�X�ȊO�Ȃ�

				mine_cnt =0;//�n����������
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