#ifndef _FUNC_H_//_CHAR_FUNC_H_が定義されていなければendifまでをインクルード
#define _FUNC_H_//_CHAR_FUNC_H_というプリプロセッサマクロ(通称ガードマクロ)を定義



typedef unsigned int	uint32t;
typedef int				int32t;
typedef unsigned char	uchar8t;
typedef char			char8t;
typedef	double			double64t;

#define ONE 1;


/*Str*/
char8t* StdStr_Strstr(const char8t* aS1, const char8t* aS2);
char8t* StdStr_Strtok(char8t* aS1, const char8t* aS2);

/*Math*/

//むずいやつは　とりあえず整数に限定して対応？？
/*基本*/
double64t StdArc_Floor(double64t );				//★OK
double64t StdArc_Ceil(double64t);				//★OK
double64t StdArc_Fabs(double64t );				//★OK　　
double64t StdArc_Fmod(double64t, double64t);	//★OK

/*マクローリン展開*/
double64t StdArc_Sin(double64t);				//★OK
double64t StdArc_Cos(double64t);				//★OK
double64t StdArc_Tan(double64t);				//★OK
double64t StdArc_Asin(double64t);				//★とりあえずOK① 公式が間違ってた　ループ100000位じゃないと-1,1付近の誤差でかい
double64t StdArc_Acos(double64t);				//★とりあえずOK　Asinの精度に依存
double64t StdArc_Atan(double64t);				//△②有効範囲が違う　ループ回数100回くらいにするとまあまあの精度だが，，，
double64t StdArc_Atan2(double64t,double64t);	//△③atanに依存？
double64t StdArc_Cosh(double64t);				//★OK exp使っても計算できる
double64t StdArc_Exp(double64t);				//★OK

double64t StdArc_Pow(double64t, double64t);		//★OK？　ぽいのはできた sqrt関数と分解回数に依存

/*ニュートン法*/
double64t StdArc_Sqrt(double64t );				//★OK
double64t StdArc_Log(double64t);				//★OK　expのバグが原因で値おかしくなってた
double64t StdArc_Log10(double64t);				//★OK　Logの精度次第




#endif//