#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<windows.h>
#define SIZE 10

//地雷の個所の旗立て動作がない

//★グローバル変数 field
//下位8bitしか使ってない
//0000 XXXX :未採掘,地雷なし　
//0001 XXXX未採掘　地雷あり　
//0010 XXXX:採掘済み　地雷なし　 
//0100 XXXX:旗あり
// ※　XXXXは周囲の地雷の数

int field[SIZE][SIZE] = { 0 };
int mine_num = 10;	//地雷の数
int done_cnt = 0;	//採掘した数

//連鎖的に隣接マス開ける処理で使用 ループ処理するときの　加算値と探索方向の対応を表す配列
//　{jの加算値,iの加算値}
const int add[12][2] =		{	{0,1} ,{1,1},{1,0},		//方向　0   0,1,2
								{-1,0},{-1,-1},{0,-1},	//方向　1    3,4,5
								{-1,0},{-1,1},{0,1},	//方向　2    6,7,8
								{0,-1},{1,-1},{1,0}		//方向　3    9,10,11
							};
//fieldの初期設定
void init_field(void) {
	int i, j,n,m;

	srand((unsigned)time(NULL));

	//地雷をセット
	for (i = 0; i < mine_num; i++) {
		field[rand() % SIZE][rand() % SIZE] |= 1 << 4;//0001 0000との論理和にする(XXX1 XXXX　となるようにする) ;
	}

	//地雷のない箇所に　周囲3*3の範囲の地雷の個数をセット
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (((field[i][j] >> 4) & 1) == 0) {//5bit目が0(=地雷でない)なら
												//セット箇所の周囲1マスの地雷を探索
				for (n = -1; n <= 1; n++) {
					for (m = -1; m <= 1; m++) {
						if (0 <= i + n && i + n <= 7 && 0 <= j + m && j + m <= 7) {//周囲1マスが有効範囲の時のみ処理
							if (((field[i + n][j + m] >> 4) & 1) == 1) {//5bit目が1(=地雷)なら
								field[i][j]++;//field の値に1加算　(下位4bitが地雷数，0～15)
							}
						}
					}
				}
			}
		}
	}
}

//fieldを右に90度回転させる
void field_rot(void) {
	int field_pre[SIZE][SIZE] = {0};
	int i, j;
	
	//処理前の状態をいったんfield_preに保存
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

//入力用関数 作成中!!!!! いらないかも
char * input(void) {
	char input_char[2] = {0};//入力結果(i,j)を格納する
	int i;


	do {
		//掘る位置を入力
		printf("採掘したい場所の行番号(a～h)を入力\n");
		printf("旗を立てる場合は行番号を大文字入力\n");

		input_char[0] = getchar();


		printf("採掘したい場所の行番号(a～h)を入力\n");
		printf("旗を立てる場合は行番号を大文字入力\n");

		input_char[0] = getchar();

		if (1) {// a-z,a-zの組み合わせ以外　またはA-Z,A-Zの組み合わせ以外の時
			printf("入力エラー　もう一度入力してください\n");//
		}

	} while (input_char[0]);

	return input_char;
}
//受け取った整数を2進数として解釈しなおす ※8bitまで
int dec2bin(int dec) {
	int mask = 1 << (8 - 1);//int型の8番目のbitを1にする
	int bin = 0;
	int bit = 8;//何bit目か
	int gain = 1;//倍率　1,10,100

	dec = dec % (int)pow(2, 8 - 1);//大きすぎる値を受けとったら下位8bitだけにする

	while (mask != 0) {
		if (mask & dec) {
			bin += 1 * (int)pow(10, bit - 1);//intが扱えるサイズを超えている
			//printf("1");
		}
		else {
			//printf("0");
		}
		bit--;
		mask >>= 1;//右に1ビットシフト
	}
	//printf("\n");

	return bin;
}

//受け取った0/1のみの整数を10進数として解釈しなおす　※8bitまで
int bin2dec(int bin) {
	int n, dec = 0;
	int bin_keta = 0;
	int dec_keta = 0;
	int bit = 0;

	for (n = 0;n < 8;n++) {
		bin_keta = (int)pow(2, 7 - n);
		dec_keta = (int)pow(10, 7 - n);
		bit = (bin / dec_keta);				//注目している桁が0の場合は小数点以下になるので切り捨てられて0になる
		if (bit > 1) { bit = 1; }
		dec += bit * bin_keta ;//1以上の桁は1として解釈される
		bin %= dec_keta;
		//printf("%d\n",dec);
	}

	return dec;
}

//field表示
void field_print(void) {
	int i, j;

	done_cnt = 0;
	
	//横方向のラベル
	printf("\n   ");
	for (i = 0;i < SIZE;i++) {
		printf("%c ", 'a' + i);
	}
	printf("\n");

	for (i = 0; i < SIZE; i++) {
		printf("%c ", (char)('a' + i));//縦方向のラベル
		for (j = 0; j < SIZE; j++) {
			if ((field[i][j] >> 5 & 1) == 0) {	//6bit目が0(=未採掘)なら?と表示
				printf(" ?");
			}
			else {
				if ((field[i][j] >> 4 & 1) == 1) {//5bit目が1(=地雷)ならBと表示
					printf(" B");
				}
				else {
					printf(" %d", field[i][j] & 0x0000000F);//地雷でない場合は下位4bitを10進数で表示
				}
				done_cnt++;
			}

		}
		printf("\n");
	}

	printf("採掘済み%d個　爆弾%d個\n", done_cnt, mine_num);
	printf("\n\n");
}

//field全表示
void field_print_all(void) {
	int i, j;
	//初期状態表示部
	printf("～答え～\n");

	printf("\n   ");
	for (i = 0;i < SIZE;i++) {
		printf("%c ", 'a' + i);
	}
	printf("\n");

	for (i = 0; i < SIZE; i++) {
		printf("%c ", (char)('a' + i));
		for (j = 0; j < SIZE; j++) {
			if ((field[i][j] >> 4 & 1) == 1) {//5bit目が1(=地雷)ならBと表示
				printf(" B");
			}
			else {
				printf(" %d", field[i][j] & 0x0000000F);//地雷でない場合は下位4bitを10進数で表示
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

//(i,j)を起点としてdir方向に周囲を掘る　バグありそう...
void search(int i, int j,int dir) {

	//printf("(%c,%c)\n",i+'a',j+'a');

	if (0 <= i && i < SIZE && 0 <= j && j < SIZE ) {//i,jが配列の範囲内の値の場合の処理する
		//採掘済みの時も処理しないようにしたい　if( (field[i][j] >> 5) & 1 == 1)
		if ((field[i][j] >> 4 & 0x00000001) == 0x00000001 || ( (field[i][j] >> 5) & 1 == 1  &&  done_cnt>0 ) ) {//マスが地雷あるいは　再帰2回目以降かつ採掘済みの時
										  //何もせず終了
		}
		else if ((field[i][j] & 0x0000000F) == 0 ) {//マスが地雷数0のとき
			field[i][j] |= (1 << 5); //採掘bitを立てる
			done_cnt++;
			//Sleep(10);		//アニメーション風表示
			system("cls");	//
			field_print();	//
			search(i +add[dir][1]   ,j +add[dir][0]   ,dir);
			search(i +add[dir+1][1] ,j +add[dir+1][0] ,dir);
			search(i +add[dir+2][1] ,j +add[dir+2][0] ,dir);

		}
		else {//マスが地雷数１以上の時
			field[i][j] |= (1 << 5); //採掘bitを立てる
			//done_cnt++;//探索が重複するとカウントバグる
		}
	}

}


int main(void) {
	int loop_flag = 1;
	int i, j;
	int n, m;
	int input_i, input_j;
	int dir;

	//field初期化
	init_field();

	//初期状態表示
	field_print();

	while (loop_flag==1) {

		do {
			//掘る位置を入力
			printf("採掘したい場所の行番号(a～h)を入力\n");
			input_i = (int)(getchar());
			getchar();//改行読み込み
			printf("採掘した場所の列番号(a～h)を入力\n");
			input_j = (int)(getchar());
			getchar();//改行読み込み

			//採掘するとき
			if ('a' <= input_i && input_i <= 'a' + SIZE &&'a' <= input_j && input_j <= 'a' + SIZE) {
				input_i -= 'a';//0～SIZE-1の値に変換
				input_j -= 'a';//0～SIZE-1の値に変換

				//採掘bitを立てる 初回のみ必要
				field[input_i][input_j] |= (1 << 5);

				//掘る位置の周囲を探索しステータス更新
				search(input_i, input_j, 0 * 3);
				search(input_i-1, input_j-1, 1 * 3);
				search(input_i, input_j-1, 2 * 3);
				search(input_i-1, input_j, 3 * 3);
				break;
			}
			//旗立て/撤去
			else if ('A' <= input_i && input_i <= 'A' + SIZE && 'A' <= input_j && input_j <= 'A' + SIZE) {
				input_i -= 'A';//0～SIZE-1の値に変換
				input_j -= 'A';//0～SIZE-1の値に変換

				//旗bitを反転させる
				field[input_i][input_j] |= (1 << 6);//　bit値と1の排他的論理和　bit=0⇒1　bit=1⇒0
				break;
			}
			else {
				printf("入力エラー\n");
				//while (getchar()!='\n');//バッファをリセット？
			}
		} while (1);


		//field表示
		Sleep(100);
		//system("cls");
		field_print();

		//クリア、ゲームオーバーの判定
		if ((field[input_i][input_j] >> 4 & 0x00000001) == 0x00000001) {//新しく採掘した場所が地雷ならゲームオーバー　(5bit目が1ならアウト)
			printf("GAME OVER！\n\n");
			field_print_all();
			loop_flag = -1;
		}
		else if (done_cnt >= (SIZE*SIZE -mine_num) ) {//地雷以外のマスすべて採掘できたらクリア
			printf("GAME CLEAR！\n\n");
			field_print_all();
			loop_flag = 0;
		}
	}
	system("pause");
}