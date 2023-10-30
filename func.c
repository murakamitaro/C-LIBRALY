#include "func.h"


char8t* StdStr_Strstr(const char8t* aS1, const char8t* aS2)
{
	char8t* tRet=0;
	uint32t tLpCt1=0;
	uint32t tLpCt2=0;
	char8t* Srch=0;

	for (tLpCt1 = 0; aS1[tLpCt1] != '\0'; tLpCt1++)
	{
		/*����������\0�݂̂̏ꍇ*/
		if (aS2[0] == '\0')
		{
			tRet = aS1;
			break;
		}
		/*����������̐擪�����ƈ�v�����ꍇ*/
		else if (aS2[0] == aS1[tLpCt1] )
		{
			Srch = aS1 + tLpCt1;//��r�J�n�ʒu���

			/*��r�J�n�@���������񖖔��̂�\0�𔭌��@or �s��v�Ń��[�v�I��*/
			for (tLpCt2 = 0; aS2[tLpCt2]!='\0' && Srch[tLpCt2] == aS2[tLpCt2]; tLpCt2++)
			{
					/*DO NOTHING*/
			}

			/*���������񖖔���\0���������ꍇ*/
			if (aS2[tLpCt2] == '\0' && tLpCt2 > 0)
			{
				tRet = Srch;
				break;
			}
			/*�s��v�̏ꍇ\0*/
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
	static char8t* tTp   = 0;/*NULL�@�g�[�N�������ʒu*/
	static char8t* tSrch = 0;/*NULL �T���ʒu*/
	char8t* tRet = 0;		/*NULL*/
	uint32t tFndFlg = 0;	/*��؂蕶�������t���O�@�������邽��1�ɂ���*/
	uint32t tUpdtFlg = 0;	/*�X�V�t���O�@Tp���X�V������1�ɂ���*/
	uint32t tLpCt1 = 0;
	uint32t tLpCt2 = 0;
	
	/*aS1��NULL�ȊO�̏ꍇ�̏���*/
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
			/*��؂蕶������*/
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

		/*��؂蕶���𔭌��ł��Ȃ������ꍇ*/
		if (tFndFlg == 0)
		{
			/*tTp�����X�V�̏ꍇ*/
			if ( tUpdtFlg == 0) {
				tUpdtFlg = 1;
				tTp = tSrch + tLpCt1;;
			}
			/*���̑��̋�؂蕶���𔭌��ł��Ȃ������ꍇ*/
			else
			{
				/*DO NOTHING*/
			}
		}
		/*��؂蕶���𔭌��ł����ꍇ*/
		else
		{
			/*�g�[�N���𔭌����Ă���ꍇ*/
			if (tUpdtFlg == 1)
			{
				tSrch[tLpCt1] = '\0';
				tSrch += (tLpCt1 + 1); /*�����J�n�ʒu�𔭌��ʒu�̈��ɍX�V*/
				break;
			}
			/*�g�[�N���������̏ꍇ*/
			else
			{
				tSrch[tLpCt1] = '\0';
			}
		}
	}

	/*aS1�̏I�[�܂ŒT���I�����ꍇ*/
	if (tSrch[tLpCt1] == '\0')
	{
		tRet = 0;
	}
	else {
		tRet=tTp;
	}
	
	return tRet;
}

/*�؂�̂�*/
double64t StdArc_Floor(double64t aX)
{
	int32t		tX=0;
	double64t	tRet=0;

	/*aX�����̏ꍇ*/
	if (aX < 0)
	{
		tX = (int)aX ;
		
		/*�����_�ȉ�������ꍇ�˃L���X�g��̒l�̕����傫���ꍇ*/
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

	/*aX��0�ȏ�̏ꍇ*/
	else
	{
		tX = (int)aX;
		tRet = (double)tX;
	}

	return tRet;
}

/*�؂�グ*/
double64t StdArc_Ceil(double64t aX)
{
	int32t		tX=0;
	double64t	tRet=0;

	/*aX�����̐��̏ꍇ*/
	if (aX >= 0)
	{
		tX = (int)aX;

		/*�����_�ȉ�������ꍇ�˃L���X�g��̒l�̕����傫���ꍇ*/
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

	/*aX��0�ȉ��̐��̏ꍇ*/
	else
	{
		tX = (int)aX;

		/*tX��0�̏ꍇ�@-0�Ƃ���ׂ̏���*/
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

/*��Βl�v�Z*/
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
	double64t	tSin=0;	/*sin�̋ߎ��l���i�[*/
	double64t	tAdd=0;	/*���̍�*/
	double64t	tN = 0;
	uint32t		tLpCt=0;
	double64t   PI = 3.141592653589793238;/*define�ɕύX����*/

	/*�͈͂�-2PI�`2PI�ɕϊ�����*/
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
	double64t	tCos = 0;	/*sin�̋ߎ��l���i�[*/
	double64t	tAdd = 0;	/*���̍�*/
	double64t	tFlr = 1;
	double64t	tN = 0;
	uint32t		tLpCt = 0;
	double64t   PI = 3.141592653589793238;/*define�ɕύX����*/

	/*�͈͂�-2PI�`2PI�ɕϊ�����*/
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
	double64t	tAsin = 0;	/*Asin�̋ߎ��l���i�[*/
	double64t	tSin = 0;	/*Sin�֐��̖߂�l���i�[*/
	double64t	tDlt = 0; /*aX��tSin�̌덷*/
	double64t	tAdd = 0;	/*���̍�*/
	double64t	tFlr = 1;
	double64t	tN = 0;
	uint32t		tLpCt = 0;
	double64t   PI = 3.141592653589793238;/*define�ɕύX����*/

	/*�͈͂�-1�`1�ȊO�̎���0��Ԃ�*/
	if (aX > 1 || aX < -1)
	{
		tRet = 0;
	}
	else
	{
#if 0
		/*����sin�֐���-PI/2�`PI/2�̒l��^���Ă���݂Ԃ��ɒT��*/
		/*������x�����Â����獏�ݕ����ׂ�������ƌ����������H*/
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
			/*���ݕ��ƌ덷�͈͂̑g�ݍ��킹�ɂ���Ắ@�덷�͈̔͂Ɏ��܂��Ă��Ȃ������[�v�𔲂���\��������*/
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
		/*�}�N���[�����W�J���ƃ��[�v�񐔑��₵�Ă��덷���傫�߁@50000�ł�������*/
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
	double64t  PI = 3.141592653589793238;/*define�ɕύX����*/

	/*�͈͂�-1�`1�ȊO�̎���0��Ԃ�*/
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
	double64t	tTan = 0;	/*tan�̋ߎ��l���i�[*/
	double64t   tBuf = 0.0;


	/* atan(aX)=asin(aX/srqt(1+aX*aX)) */

	/*-1�t�߁@1�t�߂𒴂���Ƃ̌덷�����܂����@10�������Ă��_��*/ 
	/*�߂�l��-�� / 2 �` + �� / 2*/
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
	double64t	tTan2 = 0;	/*tan�̋ߎ��l���i�[*/
	double64t   tBuf = 0.0;
	double64t	tYX = 0.0;

	
	tYX = aY / aX;

	/*aY,aX�̕���?�̑g�ݍ��킹�ŕ���*/
	/*�߂�l��-��  �` + �� */

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
	double64t	tCosh= 0;	/*Cosh�̋ߎ��l���i�[*/
	double64t	tAdd = 0;	/*���̍�*/
	double64t	tN = 0;
	uint32t		tLpCt = 0;
	double64t   PI = 3.141592653589793238;/*define�ɕύX����*/

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
	double64t tX	= 1;	/*�Ƃ肠�����̏����l*/
	double64t tLpCt = 0;
	double64t tExp = 0;

	/*aX��0�ȉ��̎��ɒ�`��G���[�o���K�v������̂��H*/
	if (aX <= 0)
	{
		tX = 0;
	}
	else
	{
		/*�j���[�g���@�@f(tX)=e^tX-aX=0�@�ƂȂ�tX�����߂�*/
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
	int32t		tXInt=0;		/*aX�̐��������i�[*/
	double64t	tXDec=0.0;		/*aX�̏��������i�[*/
	double64t	tExpInt=0.0;	/*e��tXInt����i�[*/
	double64t	tExpDec=0.0;	/*e��tXDec��̒l���i�[*/
	double64t	tAdd = 0.0;
	double64t	tN = 0;
	uint32t		tLpCt = 0;
	double64t	tRet = 0.0;

	
	/*���̐��̎�*/
	if (aX > 0)
	{
		tXInt = (int32t)StdArc_Floor(aX);
		tXDec = aX - (double64t)tXInt;

		for (tExpInt = 1,tLpCt = 1; tLpCt <= tXInt; tLpCt++)
		{
			tExpInt *= 2.718;
		}
	}
	/*���̐��̎�*/
	else if(aX < 0)
	{
		tXInt = (int32t)StdArc_Floor(aX);	/*e^-3.2�̏ꍇ�@e^-4 *�@e^0.8�@�̂悤�ɕ������Čv�Z*/
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
		/*���������}�N���[�����W�J�𗘗p���Čv�Z*/
		tAdd = 1;
		/*2���ڈȍ~��for�����Ōv�Z*/
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
	double64t tX=aX/2;	/*�Ƃ肠�����̏����l*/
	double64t tLpCt = 0;

	/*aX�����̎��ɒ�`��G���[�o���K�v������̂��H*/
	if (aX < 0)
	{
		tX = 0;
	}
	else
	{
		/*�j���[�g���@�@f(tX)=tX^2-aX=0�@�ƂȂ�tX�����߂�*/
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
	double64t	tBuf;			//2^(-n)�̒l���ꎞ�I�ɋL�����Ă���
	double64t	tSqrtN;			//sqrt�̖߂�l��sqrt�̈����ɂ���n��J��Ԃ����l;
	

	/*�܂�aY�̐����������o��aX��tYInt��|�����킹��or����*/
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
		/*sqrt�����x���g���ď��������ߎ��I�ɋ��߂�@*/
		/*tYDec���@2^(-n)�̘a�ŋߎ�*/
		
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