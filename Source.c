#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<windows.h>


//global
int field[8][8] = { 0 };//0:�Ȃ��@1,��:���@-1,�Z:���
int turn = 1;
int i_in, j_in;

int show_field(void) {
	int i = 0, j = 0;

	printf("  0 1 2 3 4 5 6 7 \n");
	for (j = 0; j < 8; j++) {
		printf(" %d", j);

		for (i = 0; i < 8; i++) {
			if (field[j][i] == 1) {
				printf("��");
			}
			else if (field[j][i] == -1) {
				printf("�Z");
			}
			else {
				printf("��");
			}
		}
		printf("\n");
	}
	printf("\n");

	return 1;
}

int scan_pos(void) {

	printf("�s�ԍ��C��ԍ��@�̂悤�ɓ���\n");
	scanf("%d %d", &j_in, &i_in);

	while (1) {
		if (j_in<0 || j_in>7 || i_in<0 || j_in>7 || field[j_in][i_in] != 0) {
			printf("�����ɂ͂����܂���\n");
			printf("�s�ԍ��C��ԍ��@�̂悤�ɓ���\n");
			scanf("%d %d", &j_in, &i_in);
		}
		else
			break;
	}

	return 1;
}

int turn2sign(int turn) {

	return (int)pow(-1, turn + 1);
}

int reverse(int i_start, int i_end, int j_start, int j_end) {//�Ђ�����Ԃ��́@�J�n�n�_�ƏI���n�_������
	int tmp,i,j;

	if (i_start > i_end) {
		tmp = i_start;
		i_start = i_end;
		i_end = tmp;
	}
	if (j_start > j_end) {
		tmp = j_start;
		j_start = j_end;
		j_end = tmp;
	}

	for (i = i_start;i <= i_end;i++) {
		field[j_in][i] = -field[j_in][i];
	}

}




int field_update(void) {
	int i, j;//���[�v����
	int j_chk = 0;//�`�F�b�N������W
	int i_chk = 0;//�`�F�b�N������W
	int me;
	int enemy;

	me = turn2sign(turn);	//��������̕����@1or-1
	enemy = -me;			//�G����̕����@1or-1

	//���u�����Ƃ����field�X�V
	field[j_in][i_in] = turn2sign(turn);//�����ɍX�V����悤�ɒ������ق�������

	//8�����ɒT��

	//i+�����Aj�{�����ւ̏���
	if (field[j_in+1][i_in + 1] == -field[j_in][i_in]) {//�u�����R�}�ׂ̗��Ⴄ�F�Ȃ烋�[�v�����J�n
		
			i_chk = i_in + 1;
			j_chk = j_in + 1;

			while (i_chk < 6 && j_chk < 6) {

				if (field[j_chk][i_chk] == enemy && field[j_chk+1][i_chk + 1] == enemy) {//�G�A�G�ƂȂ�Ƃ�
					
					//��������Ȃ��Ȃ��H�H
					/*if (i_chk < 6 && j_chk < 6 ) {
						//��{�͉������Ȃ��ŃX�L�b�v
					}
					else {//�G�A�G�A�g�O�ƂȂ鎞
						printf("�Ђ�����Ԃ�Ȃ�\n");
						break;
					}*/
				}
				else if (field[j_chk][i_chk] == enemy && field[j_chk+1][i_chk + 1] == me) {
					printf("�Ђ�����Ԃ�\n");
					//field[j_in][i_in+1]����field[j_in][i_chk]�܂Ŕ��]�@�����͕ʂ̊֐��ɕ�������
					i = i_in + 1;
					j = j_in + 1;

					while (i<=i_chk && j<=j_chk) {
						field[j][i] = -field[j][i];
						i++;
						j++;
					}

					break;
				}
				else {//�G�A��@�ƂȂ鎞
					printf("�Ђ�����Ԃ�Ȃ�\n");
					break;
				}

				i_chk++;
				j_chk++;
			}
	}


	//i��+�����݂̂̏���
	if (field[j_in][i_in + 1] == -field[j_in][i_in]) {//�u�����R�}�ׂ̗��Ⴄ�F�Ȃ烋�[�v�����J�n
		for (i_chk = i_in + 1;i_chk < 6;i_chk++) {//if���Œu�����Ƃ��̈��͊m�F���Ă���̂�i_in+1���画��
			if (field[j_in][i_chk] == enemy && field[j_in][i_chk + 1] == enemy) {//�G�A�G�ƂȂ�Ƃ�		
				if (i_chk < 6) {
					//��{�͉������Ȃ��ŃX�L�b�v
				}
				else {//�G�A�G�A�g�O�ƂȂ鎞
					printf("�Ђ�����Ԃ�Ȃ�\n");
					break;
				}
			}
			else if (field[j_in][i_chk] == enemy && field[j_in][i_chk + 1] == me) {
				printf("�Ђ�����Ԃ�\n");
				//field[j_in][i_in+1]����field[j_in][i_chk]�܂Ŕ��]�@�����͕ʂ̊֐��ɕ�������
				for (i = i_in + 1;i <= i_chk;i++) {
					field[j_in][i] = -field[j_in][i];
				}
				break;
			}
			else {//�G�A��@�ƂȂ鎞
				printf("�Ђ�����Ԃ�Ȃ�\n");
				break;
			}
		}
	}

		//i��-�����݂̂̏���
	if (field[j_in][i_in - 1] == -field[j_in][i_in]) {//�u�����R�}�ׂ̗��Ⴄ�F�Ȃ烋�[�v�����J�n
		for (i_chk = i_in - 1;i_chk > 1;i_chk--) {//if���Œu�����Ƃ��̈��͊m�F���Ă���̂�i_in+1���画��
			
			if (field[j_in][i_chk] == enemy && field[j_in][i_chk - 1] == enemy) {//�G�A�G�ƂȂ�Ƃ�		
				if (i_chk > 1) {
					//��{�͉������Ȃ��ŃX�L�b�v
				}
				else {//�G�A�G�A�g�O�ƂȂ鎞
					printf("�Ђ�����Ԃ�Ȃ�\n");
					break;
				}
			}

			else if (field[j_in][i_chk] == enemy && field[j_in][i_chk - 1] == me) {
				printf("�Ђ�����Ԃ�\n");
				//field[j_in][i_in+1]����field[j_in][i_chk]�܂Ŕ��]
				for (i = i_in-1;i >= i_chk;i--) {
					field[j_in][i] = -field[j_in][i];
				}
				break;
			}
			else {//�G�A��@�ƂȂ鎞
				printf("�Ђ�����Ԃ�Ȃ�\n");
				break;
			}
		}
	}

	//j��+�����݂̂̏���
	if (field[j_in+1][i_in] == -field[j_in][i_in]) {//�u�����R�}�ׂ̗��Ⴄ�F�Ȃ烋�[�v�����J�n

		for (j_chk = j_in + 1;j_chk < 6;j_chk++) {//if���Œu�����Ƃ��̈��͊m�F���Ă���̂�i_in+1���画��

												  //field[j_in][i_chk] �Ɓ@field[j_in][i_chk+1]���r������
			if (field[j_chk][i_in] == enemy && field[j_chk+1][i_in] == enemy) {//�G�A�G�ƂȂ�Ƃ�		
				if (j_chk < 6) {
					//��{�͉������Ȃ��ŃX�L�b�v
				}
				else {//�G�A�G�A�g�O�ƂȂ鎞
					printf("�Ђ�����Ԃ�Ȃ�\n");
					break;
				}
			}

			else if (field[j_chk][i_in] == enemy && field[j_chk+1][i_in] == me) {
				printf("�Ђ�����Ԃ�\n");
				//field[j_in][i_in+1]����field[j_in][i_chk]�܂Ŕ��]
				for (j = j_in + 1;j <= j_chk;j++) {
					field[j][i_in] = -field[j][i_in];
				}
				break;
			}
			else {//�G�A��@�ƂȂ鎞
				printf("�Ђ�����Ԃ�Ȃ�\n");
				break;
			}
		}
	}

	//j��-�����݂̂̏���
	if (field[j_in-1][i_in] == -field[j_in][i_in]) {//�u�����R�}�ׂ̗��Ⴄ�F�Ȃ烋�[�v�����J�n

		for (j_chk = j_in - 1;j_chk > 1;j_chk--) {//if���Œu�����Ƃ��̈��͊m�F���Ă���̂�i_in+1���画��

												  //field[j_in][i_chk] �Ɓ@field[j_in][i_chk+1]���r������
			if (field[j_chk][i_in] == enemy && field[j_chk-1][i_in] == enemy) {//�G�A�G�ƂȂ�Ƃ�		
				if (j_chk > 1) {
					//��{�͉������Ȃ��ŃX�L�b�v
				}
				else {//�G�A�G�A�g�O�ƂȂ鎞
					printf("�Ђ�����Ԃ�Ȃ�\n");
					break;
				}
			}

			else if (field[j_chk][i_in] == enemy && field[j_chk-1][i_in] == me) {
				printf("�Ђ�����Ԃ�\n");
				//field[j_in][i_in+1]����field[j_in][i_chk]�܂Ŕ��]
				for (j = j_in - 1;j >= j_chk;j--) {
					field[j][i_in] = -field[j][i_in];
				}
				break;
			}
			else {//�G�A��@�ƂȂ鎞
				printf("�Ђ�����Ԃ�Ȃ�\n");
				break;
			}
		}
	}


	printf("�`�F�b�N�I��\n");

	return 1;
}


int main(void) {
	int i, j, k, n, m;


	show_field();

	//�����z�u
	field[3][3] = 1;
	field[4][4] = 1;
	field[3][4] = -1;
	field[4][3] = -1;

	//Sleep(1000);

	while (1) {
		system("cls");
		show_field();

		printf("%d�^�[����\n", turn);
		if (turn % 2 == 1) {	//��^�[���ː��̃^�[���C  1�ˎ����̋�@�@�^�[���ˋ�l�ϊ��́@1*(-1)^(turn+1)
			printf("���̃^�[���ł�\n");
		}
		else {					//-1�ˎ����̋�
			printf("�Z�̃^�[���ł�\n");
		}
		scan_pos();
		field_update();
		turn++;
	}

}