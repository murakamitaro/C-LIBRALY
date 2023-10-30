#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<windows.h>
#define SIZE 10

//�n���̌��̊����ē��삪�Ȃ�

//���O���[�o���ϐ� field
//����8bit�����g���ĂȂ�
//0000 XXXX :���̌@,�n���Ȃ��@
//0001 XXXX���̌@�@�n������@
//0010 XXXX:�̌@�ς݁@�n���Ȃ��@ 
//0100 XXXX:������
// ���@XXXX�͎��͂̒n���̐�

int field[SIZE][SIZE] = { 0 };
int mine_num = 10;	//�n���̐�
int done_cnt = 0;	//�̌@������

//�A���I�ɗאڃ}�X�J���鏈���Ŏg�p ���[�v��������Ƃ��́@���Z�l�ƒT�������̑Ή���\���z��
//�@{j�̉��Z�l,i�̉��Z�l}
const int add[12][2] =		{	{0,1} ,{1,1},{1,0},		//�����@0   0,1,2
								{-1,0},{-1,-1},{0,-1},	//�����@1    3,4,5
								{-1,0},{-1,1},{0,1},	//�����@2    6,7,8
								{0,-1},{1,-1},{1,0}		//�����@3    9,10,11
							};
//field�̏����ݒ�
void init_field(void) {
	int i, j,n,m;

	srand((unsigned)time(NULL));

	//�n�����Z�b�g
	for (i = 0; i < mine_num; i++) {
		field[rand() % SIZE][rand() % SIZE] |= 1 << 4;//0001 0000�Ƃ̘_���a�ɂ���(XXX1 XXXX�@�ƂȂ�悤�ɂ���) ;
	}

	//�n���̂Ȃ��ӏ��Ɂ@����3*3�͈̔͂̒n���̌����Z�b�g
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (((field[i][j] >> 4) & 1) == 0) {//5bit�ڂ�0(=�n���łȂ�)�Ȃ�
												//�Z�b�g�ӏ��̎���1�}�X�̒n����T��
				for (n = -1; n <= 1; n++) {
					for (m = -1; m <= 1; m++) {
						if (0 <= i + n && i + n <= 7 && 0 <= j + m && j + m <= 7) {//����1�}�X���L���͈͂̎��̂ݏ���
							if (((field[i + n][j + m] >> 4) & 1) == 1) {//5bit�ڂ�1(=�n��)�Ȃ�
								field[i][j]++;//field �̒l��1���Z�@(����4bit���n�����C0�`15)
							}
						}
					}
				}
			}
		}
	}
}

//field���E��90�x��]������
void field_rot(void) {
	int field_pre[SIZE][SIZE] = {0};
	int i, j;
	
	//�����O�̏�Ԃ���������field_pre�ɕۑ�
	for (i = 0;i < SIZE;i++) {
		for (j = 0;j < SIZE;j++) {
			field_pre[i][j] = field[i][j];
		}
	}


	for (j = 0;j < SIZE;j++) {
		for (i = 0;i < SIZE;i++) {
			field[i][j] = field_pre[SIZE-1 - j][i];
		}
	}
}

//���͗p�֐� �쐬��!!!!! ����Ȃ�����
char * input(void) {
	char input_char[2] = {0};//���͌���(i,j)���i�[����
	int i;


	do {
		//�@��ʒu�����
		printf("�̌@�������ꏊ�̍s�ԍ�(a�`h)�����\n");
		printf("���𗧂Ă�ꍇ�͍s�ԍ���啶������\n");

		input_char[0] = getchar();


		printf("�̌@�������ꏊ�̍s�ԍ�(a�`h)�����\n");
		printf("���𗧂Ă�ꍇ�͍s�ԍ���啶������\n");

		input_char[0] = getchar();

		if (1) {// a-z,a-z�̑g�ݍ��킹�ȊO�@�܂���A-Z,A-Z�̑g�ݍ��킹�ȊO�̎�
			printf("���̓G���[�@������x���͂��Ă�������\n");//
		}

	} while (input_char[0]);

	return input_char;
}
//�󂯎����������2�i���Ƃ��ĉ��߂��Ȃ��� ��8bit�܂�
int dec2bin(int dec) {
	int mask = 1 << (8 - 1);//int�^��8�Ԗڂ�bit��1�ɂ���
	int bin = 0;
	int bit = 8;//��bit�ڂ�
	int gain = 1;//�{���@1,10,100

	dec = dec % (int)pow(2, 8 - 1);//�傫������l���󂯂Ƃ����牺��8bit�����ɂ���

	while (mask != 0) {
		if (mask & dec) {
			bin += 1 * (int)pow(10, bit - 1);//int��������T�C�Y�𒴂��Ă���
			//printf("1");
		}
		else {
			//printf("0");
		}
		bit--;
		mask >>= 1;//�E��1�r�b�g�V�t�g
	}
	//printf("\n");

	return bin;
}

//�󂯎����0/1�݂̂̐�����10�i���Ƃ��ĉ��߂��Ȃ����@��8bit�܂�
int bin2dec(int bin) {
	int n, dec = 0;
	int bin_keta = 0;
	int dec_keta = 0;
	int bit = 0;

	for (n = 0;n < 8;n++) {
		bin_keta = (int)pow(2, 7 - n);
		dec_keta = (int)pow(10, 7 - n);
		bit = (bin / dec_keta);				//���ڂ��Ă��錅��0�̏ꍇ�͏����_�ȉ��ɂȂ�̂Ő؂�̂Ă���0�ɂȂ�
		if (bit > 1) { bit = 1; }
		dec += bit * bin_keta ;//1�ȏ�̌���1�Ƃ��ĉ��߂����
		bin %= dec_keta;
		//printf("%d\n",dec);
	}

	return dec;
}

//field�\��
void field_print(void) {
	int i, j;

	done_cnt = 0;
	
	//�������̃��x��
	printf("\n   ");
	for (i = 0;i < SIZE;i++) {
		printf("%c ", 'a' + i);
	}
	printf("\n");

	for (i = 0; i < SIZE; i++) {
		printf("%c ", (char)('a' + i));//�c�����̃��x��
		for (j = 0; j < SIZE; j++) {
			if ((field[i][j] >> 5 & 1) == 0) {	//6bit�ڂ�0(=���̌@)�Ȃ�?�ƕ\��
				printf(" ?");
			}
			else {
				if ((field[i][j] >> 4 & 1) == 1) {//5bit�ڂ�1(=�n��)�Ȃ�B�ƕ\��
					printf(" B");
				}
				else {
					printf(" %d", field[i][j] & 0x0000000F);//�n���łȂ��ꍇ�͉���4bit��10�i���ŕ\��
				}
				done_cnt++;
			}

		}
		printf("\n");
	}

	printf("�̌@�ς�%d�@���e%d��\n", done_cnt, mine_num);
	printf("\n\n");
}

//field�S�\��
void field_print_all(void) {
	int i, j;
	//������ԕ\����
	printf("�`�����`\n");

	printf("\n   ");
	for (i = 0;i < SIZE;i++) {
		printf("%c ", 'a' + i);
	}
	printf("\n");

	for (i = 0; i < SIZE; i++) {
		printf("%c ", (char)('a' + i));
		for (j = 0; j < SIZE; j++) {
			if ((field[i][j] >> 4 & 1) == 1) {//5bit�ڂ�1(=�n��)�Ȃ�B�ƕ\��
				printf(" B");
			}
			else {
				printf(" %d", field[i][j] & 0x0000000F);//�n���łȂ��ꍇ�͉���4bit��10�i���ŕ\��
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

//(i,j)���N�_�Ƃ���dir�����Ɏ��͂��@��@�o�O���肻��...
void search(int i, int j,int dir) {

	//printf("(%c,%c)\n",i+'a',j+'a');

	if (0 <= i && i < SIZE && 0 <= j && j < SIZE ) {//i,j���z��͈͓̔��̒l�̏ꍇ�̏�������
		//�̌@�ς݂̎����������Ȃ��悤�ɂ������@if( (field[i][j] >> 5) & 1 == 1)
		if ((field[i][j] >> 4 & 0x00000001) == 0x00000001 || ( (field[i][j] >> 5) & 1 == 1  &&  done_cnt>0 ) ) {//�}�X���n�����邢�́@�ċA2��ڈȍ~���̌@�ς݂̎�
										  //���������I��
		}
		else if ((field[i][j] & 0x0000000F) == 0 ) {//�}�X���n����0�̂Ƃ�
			field[i][j] |= (1 << 5); //�̌@bit�𗧂Ă�
			done_cnt++;
			//Sleep(10);		//�A�j���[�V�������\��
			system("cls");	//
			field_print();	//
			search(i +add[dir][1]   ,j +add[dir][0]   ,dir);
			search(i +add[dir+1][1] ,j +add[dir+1][0] ,dir);
			search(i +add[dir+2][1] ,j +add[dir+2][0] ,dir);

		}
		else {//�}�X���n�����P�ȏ�̎�
			field[i][j] |= (1 << 5); //�̌@bit�𗧂Ă�
			//done_cnt++;//�T�����d������ƃJ�E���g�o�O��
		}
	}

}


int main(void) {
	int loop_flag = 1;
	int i, j;
	int n, m;
	int input_i, input_j;
	int dir;

	//field������
	init_field();

	//������ԕ\��
	field_print();

	while (loop_flag==1) {

		do {
			//�@��ʒu�����
			printf("�̌@�������ꏊ�̍s�ԍ�(a�`h)�����\n");
			input_i = (int)(getchar());
			getchar();//���s�ǂݍ���
			printf("�̌@�����ꏊ�̗�ԍ�(a�`h)�����\n");
			input_j = (int)(getchar());
			getchar();//���s�ǂݍ���

			//�̌@����Ƃ�
			if ('a' <= input_i && input_i <= 'a' + SIZE &&'a' <= input_j && input_j <= 'a' + SIZE) {
				input_i -= 'a';//0�`SIZE-1�̒l�ɕϊ�
				input_j -= 'a';//0�`SIZE-1�̒l�ɕϊ�

				//�̌@bit�𗧂Ă� ����̂ݕK�v
				field[input_i][input_j] |= (1 << 5);

				//�@��ʒu�̎��͂�T�����X�e�[�^�X�X�V
				search(input_i, input_j, 0 * 3);
				search(input_i-1, input_j-1, 1 * 3);
				search(input_i, input_j-1, 2 * 3);
				search(input_i-1, input_j, 3 * 3);
				break;
			}
			//������/�P��
			else if ('A' <= input_i && input_i <= 'A' + SIZE && 'A' <= input_j && input_j <= 'A' + SIZE) {
				input_i -= 'A';//0�`SIZE-1�̒l�ɕϊ�
				input_j -= 'A';//0�`SIZE-1�̒l�ɕϊ�

				//��bit�𔽓]������
				field[input_i][input_j] |= (1 << 6);//�@bit�l��1�̔r���I�_���a�@bit=0��1�@bit=1��0
				break;
			}
			else {
				printf("���̓G���[\n");
				//while (getchar()!='\n');//�o�b�t�@�����Z�b�g�H
			}
		} while (1);


		//field�\��
		Sleep(100);
		//system("cls");
		field_print();

		//�N���A�A�Q�[���I�[�o�[�̔���
		if ((field[input_i][input_j] >> 4 & 0x00000001) == 0x00000001) {//�V�����̌@�����ꏊ���n���Ȃ�Q�[���I�[�o�[�@(5bit�ڂ�1�Ȃ�A�E�g)
			printf("GAME OVER�I\n\n");
			field_print_all();
			loop_flag = -1;
		}
		else if (done_cnt >= (SIZE*SIZE -mine_num) ) {//�n���ȊO�̃}�X���ׂč̌@�ł�����N���A
			printf("GAME CLEAR�I\n\n");
			field_print_all();
			loop_flag = 0;
		}
	}
	system("pause");
}