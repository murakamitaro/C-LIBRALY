#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<windows.h>


//global
int field[8][8] = { 0 };//0:なし　1,●:先手　-1,〇:後手
int turn = 1;
int i_in, j_in;

int show_field(void) {
	int i = 0, j = 0;

	printf("  0 1 2 3 4 5 6 7 \n");
	for (j = 0; j < 8; j++) {
		printf(" %d", j);

		for (i = 0; i < 8; i++) {
			if (field[j][i] == 1) {
				printf("●");
			}
			else if (field[j][i] == -1) {
				printf("〇");
			}
			else {
				printf("□");
			}
		}
		printf("\n");
	}
	printf("\n");

	return 1;
}

int scan_pos(void) {

	printf("行番号，列番号　のように入力\n");
	scanf("%d %d", &j_in, &i_in);

	while (1) {
		if (j_in<0 || j_in>7 || i_in<0 || j_in>7 || field[j_in][i_in] != 0) {
			printf("そこにはおけません\n");
			printf("行番号，列番号　のように入力\n");
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

int reverse(int i_start, int i_end, int j_start, int j_end) {//ひっくり返しの　開始地点と終了地点が引数
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
	int i, j;//ループ制御
	int j_chk = 0;//チェックする座標
	int i_chk = 0;//チェックする座標
	int me;
	int enemy;

	me = turn2sign(turn);	//自分側駒の符号　1or-1
	enemy = -me;			//敵側駒の符号　1or-1

	//駒を置いたところのfield更新
	field[j_in][i_in] = turn2sign(turn);//判定後に更新するように直したほうがいい

	//8方向に探索

	//i+方向、j＋方向への処理
	if (field[j_in+1][i_in + 1] == -field[j_in][i_in]) {//置いたコマの隣が違う色ならループ処理開始
		
			i_chk = i_in + 1;
			j_chk = j_in + 1;

			while (i_chk < 6 && j_chk < 6) {

				if (field[j_chk][i_chk] == enemy && field[j_chk+1][i_chk + 1] == enemy) {//敵、敵となるとき
					
					//ここいらなくない？？
					/*if (i_chk < 6 && j_chk < 6 ) {
						//基本は何もしないでスキップ
					}
					else {//敵、敵、枠外となる時
						printf("ひっくり返らない\n");
						break;
					}*/
				}
				else if (field[j_chk][i_chk] == enemy && field[j_chk+1][i_chk + 1] == me) {
					printf("ひっくり返る\n");
					//field[j_in][i_in+1]からfield[j_in][i_chk]まで反転　ここは別の関数に分離する
					i = i_in + 1;
					j = j_in + 1;

					while (i<=i_chk && j<=j_chk) {
						field[j][i] = -field[j][i];
						i++;
						j++;
					}

					break;
				}
				else {//敵、空　となる時
					printf("ひっくり返らない\n");
					break;
				}

				i_chk++;
				j_chk++;
			}
	}


	//iの+方向のみの処理
	if (field[j_in][i_in + 1] == -field[j_in][i_in]) {//置いたコマの隣が違う色ならループ処理開始
		for (i_chk = i_in + 1;i_chk < 6;i_chk++) {//if文で置いたとこの一つ先は確認しているのでi_in+1から判定
			if (field[j_in][i_chk] == enemy && field[j_in][i_chk + 1] == enemy) {//敵、敵となるとき		
				if (i_chk < 6) {
					//基本は何もしないでスキップ
				}
				else {//敵、敵、枠外となる時
					printf("ひっくり返らない\n");
					break;
				}
			}
			else if (field[j_in][i_chk] == enemy && field[j_in][i_chk + 1] == me) {
				printf("ひっくり返る\n");
				//field[j_in][i_in+1]からfield[j_in][i_chk]まで反転　ここは別の関数に分離する
				for (i = i_in + 1;i <= i_chk;i++) {
					field[j_in][i] = -field[j_in][i];
				}
				break;
			}
			else {//敵、空　となる時
				printf("ひっくり返らない\n");
				break;
			}
		}
	}

		//iの-方向のみの処理
	if (field[j_in][i_in - 1] == -field[j_in][i_in]) {//置いたコマの隣が違う色ならループ処理開始
		for (i_chk = i_in - 1;i_chk > 1;i_chk--) {//if文で置いたとこの一つ先は確認しているのでi_in+1から判定
			
			if (field[j_in][i_chk] == enemy && field[j_in][i_chk - 1] == enemy) {//敵、敵となるとき		
				if (i_chk > 1) {
					//基本は何もしないでスキップ
				}
				else {//敵、敵、枠外となる時
					printf("ひっくり返らない\n");
					break;
				}
			}

			else if (field[j_in][i_chk] == enemy && field[j_in][i_chk - 1] == me) {
				printf("ひっくり返る\n");
				//field[j_in][i_in+1]からfield[j_in][i_chk]まで反転
				for (i = i_in-1;i >= i_chk;i--) {
					field[j_in][i] = -field[j_in][i];
				}
				break;
			}
			else {//敵、空　となる時
				printf("ひっくり返らない\n");
				break;
			}
		}
	}

	//jの+方向のみの処理
	if (field[j_in+1][i_in] == -field[j_in][i_in]) {//置いたコマの隣が違う色ならループ処理開始

		for (j_chk = j_in + 1;j_chk < 6;j_chk++) {//if文で置いたとこの一つ先は確認しているのでi_in+1から判定

												  //field[j_in][i_chk] と　field[j_in][i_chk+1]を比較し分岐
			if (field[j_chk][i_in] == enemy && field[j_chk+1][i_in] == enemy) {//敵、敵となるとき		
				if (j_chk < 6) {
					//基本は何もしないでスキップ
				}
				else {//敵、敵、枠外となる時
					printf("ひっくり返らない\n");
					break;
				}
			}

			else if (field[j_chk][i_in] == enemy && field[j_chk+1][i_in] == me) {
				printf("ひっくり返る\n");
				//field[j_in][i_in+1]からfield[j_in][i_chk]まで反転
				for (j = j_in + 1;j <= j_chk;j++) {
					field[j][i_in] = -field[j][i_in];
				}
				break;
			}
			else {//敵、空　となる時
				printf("ひっくり返らない\n");
				break;
			}
		}
	}

	//jの-方向のみの処理
	if (field[j_in-1][i_in] == -field[j_in][i_in]) {//置いたコマの隣が違う色ならループ処理開始

		for (j_chk = j_in - 1;j_chk > 1;j_chk--) {//if文で置いたとこの一つ先は確認しているのでi_in+1から判定

												  //field[j_in][i_chk] と　field[j_in][i_chk+1]を比較し分岐
			if (field[j_chk][i_in] == enemy && field[j_chk-1][i_in] == enemy) {//敵、敵となるとき		
				if (j_chk > 1) {
					//基本は何もしないでスキップ
				}
				else {//敵、敵、枠外となる時
					printf("ひっくり返らない\n");
					break;
				}
			}

			else if (field[j_chk][i_in] == enemy && field[j_chk-1][i_in] == me) {
				printf("ひっくり返る\n");
				//field[j_in][i_in+1]からfield[j_in][i_chk]まで反転
				for (j = j_in - 1;j >= j_chk;j--) {
					field[j][i_in] = -field[j][i_in];
				}
				break;
			}
			else {//敵、空　となる時
				printf("ひっくり返らない\n");
				break;
			}
		}
	}


	printf("チェック終了\n");

	return 1;
}


int main(void) {
	int i, j, k, n, m;


	show_field();

	//初期配置
	field[3][3] = 1;
	field[4][4] = 1;
	field[3][4] = -1;
	field[4][3] = -1;

	//Sleep(1000);

	while (1) {
		system("cls");
		show_field();

		printf("%dターン目\n", turn);
		if (turn % 2 == 1) {	//奇数ターン⇒先手のターン，  1⇒自分の駒　　ターン⇒駒値変換は　1*(-1)^(turn+1)
			printf("●のターンです\n");
		}
		else {					//-1⇒自分の駒
			printf("〇のターンです\n");
		}
		scan_pos();
		field_update();
		turn++;
	}

}