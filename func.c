#include "func.h"


char8t* StdStr_Strstr(const char8t* aS1, const char8t* aS2)
{
	char8t* tRet=0;
	uint32t tLpCt1=0;
	uint32t tLpCt2=0;
	char8t* Srch=0;

	for (tLpCt1 = 0; aS1[tLpCt1] != '\0'; tLpCt1++)
	{
		/*検索文字列が\0のみの場合*/
		if (aS2[0] == '\0')
		{
			tRet = aS1;
			break;
		}
		/*検索文字列の先頭文字と一致した場合*/
		else if (aS2[0] == aS1[tLpCt1] )
		{
			Srch = aS1 + tLpCt1;//比較開始位置代入

			/*比較開始　検索文字列末尾のの\0を発見　or 不一致でループ終了*/
			for (tLpCt2 = 0; aS2[tLpCt2]!='\0' && Srch[tLpCt2] == aS2[tLpCt2]; tLpCt2++)
			{
					/*DO NOTHING*/
			}

			/*検索文字列末尾の\0を見つけた場合*/
			if (aS2[tLpCt2] == '\0' && tLpCt2 > 0)
			{
				tRet = Srch;
				break;
			}
			/*不一致の場合\0*/
			else 
			{
				tRet = 0;
				break;
			}
		}
		else
		{
			/*DO NOTHING*/
		}
	}
	return tRet;
}

char* custom_strtok(char* str, const char* delim) {
	static char* token;
	if (str)
		token = str;
	else
		str = token;

	if (!str || !*str)
		return 0;

	char* start = str;
	while (*str) {
		if (strchr(delim, *str)) {
			*str = '\0';
			token = str + 1;
			return start;
		}
		str++;
	}

	token = str;
	return start;
}

char8t* StdStr_Strtok(char8t* aS1, const char8t* aS2)
{
	static char8t* tTp   = 0;/*NULL　トークン発見位置*/
	static char8t* tSrch = 0;/*NULL 探索位置*/
	char8t* tRet = 0;		/*NULL*/
	uint32t tFndFlg = 0;	/*区切り文字発見フラグ　発見するたび1にする*/
	uint32t tUpdtFlg = 0;	/*更新フラグ　Tpを更新したら1にする*/
	uint32t tLpCt1 = 0;
	uint32t tLpCt2 = 0;
	
	/*aS1がNULL以外の場合の処理*/
	if (aS1 != 0)
	{
		tSrch = aS1;	
	}
	else
	{
		/*DO NOTHING*/
	}

	for (tLpCt1 = 0; tSrch[tLpCt1] != '\0'; tLpCt1++)
	{
		tFndFlg = 0;
		for (tLpCt2 = 0; aS2[tLpCt2] != '\0'; tLpCt2++)
		{
			/*区切り文字発見*/
			if (tSrch[tLpCt1] == aS2[tLpCt2])
			{
				tFndFlg = 1;
				break;
			}
			else
			{
				/*DO NOTHING*/
			}
		}

		/*区切り文字を発見できなかった場合*/
		if (tFndFlg == 0)
		{
			/*tTpが未更新の場合*/
			if ( tUpdtFlg == 0) {
				tUpdtFlg = 1;
				tTp = tSrch + tLpCt1;;
			}
			/*その他の区切り文字を発見できなかった場合*/
			else
			{
				/*DO NOTHING*/
			}
		}
		/*区切り文字を発見できた場合*/
		else
		{
			/*トークンを発見している場合*/
			if (tUpdtFlg == 1)
			{
				tSrch[tLpCt1] = '\0';
				tSrch += (tLpCt1 + 1); /*検索開始位置を発見位置の一つ先に更新*/
				break;
			}
			/*トークン未発見の場合*/
			else
			{
				tSrch[tLpCt1] = '\0';
			}
		}
	}

	/*aS1の終端まで探索終えた場合*/
	if (tSrch[tLpCt1] == '\0')
	{
		tRet = 0;
	}
	else {
		tRet=tTp;
	}
	
	return tRet;
}

/*切り捨て*/
double64t StdArc_Floor(double64t aX)
{
	int32t		tX=0;
	double64t	tRet=0;

	/*aXが負の場合*/
	if (aX < 0)
	{
		tX = (int)aX ;
		
		/*小数点以下がある場合⇒キャスト後の値の方が大きい場合*/
		if (aX < (double)tX)
		{
			tX -= 1;
		}
		else
		{
			/*DO NOTHING*/
		}
		tRet = (double)tX;
	}

	/*aXが0以上の場合*/
	else
	{
		tX = (int)aX;
		tRet = (double)tX;
	}

	return tRet;
}

/*切り上げ*/
double64t StdArc_Ceil(double64t aX)
{
	int32t		tX=0;
	double64t	tRet=0;

	/*aXが正の数の場合*/
	if (aX >= 0)
	{
		tX = (int)aX;

		/*小数点以下がある場合⇒キャスト後の値の方が大きい場合*/
		if (aX < (double)tX)
		{
			tX += 1;
		}
		else
		{
			/*DO NOTHING*/
		}
		tRet = (double)tX;
	}

	/*aXが0以下の数の場合*/
	else
	{
		tX = (int)aX;

		/*tXが0の場合　-0とする為の処理*/
		if (tX == 0)
		{
			tRet = -(double)tX;
		}
		else
		{
			tRet = (double)tX;
		}
	}

	return tRet;
}

/*絶対値計算*/
double64t StdArc_Fabs(double64t aX)
{
	double64t tRet = 0;
	double64t tX = aX;

	if (tX < 0)
	{
		tRet = -tX;
	}
	else
	{
		tRet = tX;
	}

	return tRet;
}

/*Sin*/
double64t StdArc_Sin(double64t aX)
{
	double64t	tRet=0;
	double64t	tSin=0;	/*sinの近似値を格納*/
	double64t	tAdd=0;	/*次の項*/
	double64t	tN = 0;
	uint32t		tLpCt=0;
	double64t   PI = 3.141592653589793238;/*defineに変更する*/

	/*範囲を-2PI～2PIに変換する*/
	if (aX > 2*PI || aX < -2*PI )
	{
		aX = StdArc_Fmod(aX,2*PI );
	}
	else
	{
		/*DO NOTHING*/
	}

	for (tAdd = aX,tLpCt = 1; tLpCt <=10; tLpCt++)
	{
		tN = (double64t)tLpCt;
		tSin += tAdd;
		tAdd *= -aX * aX / (tN * 2.0)/ (tN * 2.0 + 1.0); 
	}

	tRet = tSin;

	return tRet;
}

/*Tan*/
double64t StdArc_Tan(double64t aX)
{
	double64t	tSin = 0;
	double64t	tCos = 0;
	double64t	tRet = 0;

	tSin = StdArc_Sin(aX);
	tCos = StdArc_Cos(aX);
	
	if (tCos == 0)
	{
		tRet = 0;
	}
	else
	{
		tRet = tSin / tCos;
	}

	return tRet;
}

/*Cos*/
double64t StdArc_Cos(double64t aX)
{
	double64t	tRet = 0;
	double64t	tCos = 0;	/*sinの近似値を格納*/
	double64t	tAdd = 0;	/*次の項*/
	double64t	tFlr = 1;
	double64t	tN = 0;
	uint32t		tLpCt = 0;
	double64t   PI = 3.141592653589793238;/*defineに変更する*/

	/*範囲を-2PI～2PIに変換する*/
	if (aX > 2 * PI || aX < -2 * PI)
	{
		aX = StdArc_Fmod(aX, 2 * PI);
	}
	else
	{
		/*DO NOTHING*/
	}

	for (tAdd = 1, tLpCt = 1; tLpCt <= 10; tLpCt++)
	{
		tN = (double64t)tLpCt;
		tCos += tAdd;
		tAdd *= -aX * aX / (tN * 2.0) / (tN * 2.0 - 1.0);
	}

	tRet = tCos;

	return tRet;
}

/*Asin*/
double64t StdArc_Asin(double64t aX)
{
	double64t	tRet = 0;
	double64t	tAsin = 0;	/*Asinの近似値を格納*/
	double64t	tSin = 0;	/*Sin関数の戻り値を格納*/
	double64t	tDlt = 0; /*aXとtSinの誤差*/
	double64t	tAdd = 0;	/*次の項*/
	double64t	tFlr = 1;
	double64t	tN = 0;
	uint32t		tLpCt = 0;
	double64t   PI = 3.141592653589793238;/*defineに変更する*/

	/*範囲が-1～1以外の時は0を返す*/
	if (aX > 1 || aX < -1)
	{
		tRet = 0;
	}
	else
	{
#if 0
		/*自作sin関数に-PI/2～PI/2の値を与えてしらみつぶしに探す*/
		/*ある程度ちかづいたら刻み幅を細かくすると効率がいい？*/
		for (tAsin = -PI/2; tAsin <= PI/2 * PI; tAsin += 0.00001)
		{
			tSin = StdArc_Sin(tAsin);
			tDlt = tSin - aX;
			if (tDlt < 0)
			{
				tDlt = -tDlt;
			}
			else
			{
				/*DO NOTHING*/
			}
			/*刻み方と誤差範囲の組み合わせによっては　誤差の範囲に収まっていないがループを抜ける可能性がある*/
			if (tDlt<0.0001)
			{

				break;
			}
			else
			{
				/*DO NOTHING*/
			}
		}
#endif
		
#if 1
		/*マクローリン展開だとループ回数増やしても誤差が大きめ　50000でそこそこ*/
		for (tAdd = aX, tLpCt = 1; tLpCt <= 100000; tLpCt++)
		{
			tN = (double64t)tLpCt;
			tAsin += tAdd;
			tAdd *= (2.0 * tN - 1.0)* (2.0 * tN - 1.0) / (2.0 * tN * (2.0 * tN + 1.0))* aX * aX;
		}
#endif
		tRet = tAsin;
	}

	return tRet;
}

/*Acos*/
double64t StdArc_Acos(double64t aX)
{
	double64t tRet = 0;
	double64t  PI = 3.141592653589793238;/*defineに変更する*/

	/*範囲が-1～1以外の時は0を返す*/
	if (aX > 1 || aX < -1)
	{
		tRet = 0;
	}
	else
	{
		tRet = PI / 2.0 - StdArc_Asin(aX); /* asin = PI/2 - asin*/
	}

	return tRet;
}

/*Atan*/
double64t StdArc_Atan(double64t aX)
{
	double64t	tRet = 0;
	double64t	tTan = 0;	/*tanの近似値を格納*/
	double64t   tBuf = 0.0;


	/* atan(aX)=asin(aX/srqt(1+aX*aX)) */

	/*-1付近　1付近を超えるとの誤差すさまじい　10万回やってもダメ*/ 
	/*戻り値は-π / 2 ～ + π / 2*/
	tBuf = aX / StdArc_Sqrt(1.0 + aX * aX);
	tTan = StdArc_Asin(tBuf);


#if 0 
	if (aX >1.0 || aX < -1.0)
	{
		aX = StdArc_Fmod(aX, 1.0 );
	}
	else
	{
		/*DO NOTHING*/
	}

	for (tAdd = aX,tTan = aX, tLpCt = 1; tLpCt <= 100000; tLpCt++)
	{
		tN = (double64t)tLpCt;
		tAdd *= -aX * aX;
		tTan += tAdd / (2.0 * tN + 1.0);
	}
#endif

	tRet = tTan;
	
	

	return tRet;
}

/*Atan2*/
double64t StdArc_Atan2(double64t aY, double64t aX)
{
	double64t	tRet = 0;
	double64t	tTan2 = 0;	/*tanの近似値を格納*/
	double64t   tBuf = 0.0;
	double64t	tYX = 0.0;

	
	tYX = aY / aX;

	/*aY,aXの符号?の組み合わせで分岐*/
	/*戻り値は-π  ～ + π */

	tBuf = tYX / StdArc_Sqrt(1.0 + tYX * tYX);
	tTan2 = StdArc_Asin(tBuf);

	if (aX < 0.0)
	{
		if ( aY > 0.0)
		{
			tTan2 += 3.141592 ;
		}
		else if (aY <= 0.0)
		{
			tTan2 -=  3.141592;
		}

	}
	else
	{
		/*DO NOTHING*/
	}

	tRet = tTan2;

	return tRet;
}

/*Cosh*/
double64t StdArc_Cosh(double64t aX)
{
	double64t	tRet = 0;
	double64t	tCosh= 0;	/*Coshの近似値を格納*/
	double64t	tAdd = 0;	/*次の項*/
	double64t	tN = 0;
	uint32t		tLpCt = 0;
	double64t   PI = 3.141592653589793238;/*defineに変更する*/

	for (tAdd = 1, tLpCt = 1; tLpCt <= 10; tLpCt++)
	{
		tN = (double64t)tLpCt;
		tCosh += tAdd;
		tAdd *= aX * aX / (tN * 2.0) / (tN * 2.0 - 1.0);
	}

	tRet = tCosh;

	return tRet;
}

double64t StdArc_Log(double64t aX)
{
	double64t tRet = 0;
	double64t tX	= 1;	/*とりあえずの初期値*/
	double64t tLpCt = 0;
	double64t tExp = 0;

	/*aXが0以下の時に定義域エラー出す必要があるのか？*/
	if (aX <= 0)
	{
		tX = 0;
	}
	else
	{
		/*ニュートン法　f(tX)=e^tX-aX=0　となるtXを求める*/
		for (tLpCt = 0; tLpCt < 50; tLpCt++)
		{
			tExp = StdArc_Exp(tX);
			if (tExp == 0.0) {
				break;
			}
			else
			{
				tX = tX - (tExp - aX) / tExp;
			}
		}
	}

	tRet = tX;

	return tRet;
}

double64t StdArc_Log10(double64t aX)
{
	double64t tRet = 0;
	double64t tLogX = 0;
	double64t tLog10 = 0;

	/* log10(aX)=log(aX)/log(10) */
	tLogX  = StdArc_Log(aX);
	tLog10 = StdArc_Log(10.0);

	return tRet = tLogX / tLog10;
}

double64t StdArc_Fmod(double64t aX, double64t aY)
{
	int32t		tSho   = 0;
	double64t	tAmari = 0;
	double64t	tRet   = 0;
	
	if (aY == 0)
	{
		/*DO NOTHING*/
	}
	else
	{
		tSho = (int)(aX / aY);
		tAmari = aX - ((double64t)tSho * aY);
		tRet = tAmari;
	}

	return tRet;
}

double64t StdArc_Exp(double64t aX)
{
	int32t		tXInt=0;		/*aXの整数部を格納*/
	double64t	tXDec=0.0;		/*aXの小数部を格納*/
	double64t	tExpInt=0.0;	/*eのtXInt乗を格納*/
	double64t	tExpDec=0.0;	/*eのtXDec乗の値を格納*/
	double64t	tAdd = 0.0;
	double64t	tN = 0;
	uint32t		tLpCt = 0;
	double64t	tRet = 0.0;

	
	/*正の数の時*/
	if (aX > 0)
	{
		tXInt = (int32t)StdArc_Floor(aX);
		tXDec = aX - (double64t)tXInt;

		for (tExpInt = 1,tLpCt = 1; tLpCt <= tXInt; tLpCt++)
		{
			tExpInt *= 2.718;
		}
	}
	/*負の数の時*/
	else if(aX < 0)
	{
		tXInt = (int32t)StdArc_Floor(aX);	/*e^-3.2の場合　e^-4 *　e^0.8　のように分解して計算*/
		tXDec = aX - (double64t)tXInt;

		for (tExpInt = 1,tLpCt = 1; tLpCt <= (-tXInt); tLpCt++)
		{
			tExpInt /= 2.718;
		}
	}
	else
	{
		tXInt = 0.0;
		tXDec = 0.0;
		tExpInt = 1.0;
	}

	if (tXDec !=0.0)
	{
		/*小数部をマクローリン展開を利用して計算*/
		tAdd = 1;
		/*2項目以降をfor文内で計算*/
		for (tLpCt = 1; tLpCt <= 10; tLpCt++)
		{
			tN = (double64t)tLpCt;
			tExpDec += tAdd;
			tAdd *= tXDec / tN;
		}
	}
	else
	{
		tExpDec = 1.0;
	}

	tRet = tExpInt * tExpDec;

	return tRet;
}

double64t StdArc_Sqrt(double64t aX)
{
	double64t tRet=0;
	double64t tX=aX/2;	/*とりあえずの初期値*/
	double64t tLpCt = 0;

	/*aXが負の時に定義域エラー出す必要があるのか？*/
	if (aX < 0)
	{
		tX = 0;
	}
	else
	{
		/*ニュートン法　f(tX)=tX^2-aX=0　となるtXを求める*/
		for (tLpCt = 0; tLpCt < 10; tLpCt++)
		{
			tX = tX - (tX * tX - aX) / (2.0 * tX);
		}
	}

	tRet = tX;

	return tRet;
}

/*Pow*/
double64t StdArc_Pow(double64t aX, double64t aY)
{
	double64t	tRet = 0;
	double64t	tPowInt = 0;
	double64t	tPowDec = 1;
	double64t	tYInt = 0;
	double64t	tYDec = 0;
	uint32t		tLpCt=0;
	double64t	tBuf;			//2^(-n)の値を一時的に記憶しておく
	double64t	tSqrtN;			//sqrtの戻り値をsqrtの引数にしてn回繰り返した値;
	

	/*まずaYの整数部を取り出しaXをtYInt回掛け合わせるor割る*/
	tYInt = StdArc_Floor(aY);
	tYDec = aY - tYInt;
	tPowInt = 1;

	if (tYInt < 0)
	{
		for (tLpCt = 0; tLpCt < (-tYInt);tLpCt++)
		{
			tPowInt /= aX;
		}
	}
	else 
	{
		for (tLpCt = 0; tLpCt < tYInt;tLpCt++)
		{
			tPowInt *= aX;
		}
	}

#if 1
	tPowDec = 1.0;
	if (tYDec != 0.0)
	{
		/*sqrtを何度か使って小数部を近似的に求める　*/
		/*tYDecを　2^(-n)の和で近似*/
		
		tSqrtN = StdArc_Sqrt(aX);
		for (tBuf = 1, tLpCt = 0; tLpCt < 10; tLpCt++)
		{
			tBuf /= 2.0;

			if (tYDec - tBuf < 0)
			{
				/*DO NOTHING*/
			}
			else
			{
				tPowDec *= tSqrtN;
				tYDec -= tBuf;
			}
			tSqrtN = StdArc_Sqrt(tSqrtN);
		}
	}
	else
	{
		/*DO NOTHING*/
	}
#endif
	
	tRet = tPowInt * tPowDec;

	return tRet;
}