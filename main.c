#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include"func.h"
#include <math.h>

#define ONE 1

void UT_StdStr_Strstr()
{
    char    s1[] = "abcdefghijklmn";        /* �����Ώە����� */
    char    s2[] = "defgh";                 /* ��v����ꍇ */
    char    s3[] = "xyz";                   /* ��v���Ȃ��ꍇ */
    char    s4[] = "abcdefghijklmnopqr";    /* �����Ώە������蒷���ꍇ */
    char    s5[] = "";                      /* \0 */
    char* sp;


    printf("�W���֐�\n");
    sp = strstr(s1, s2);
    printf("��v����ꍇ : %s\n", sp);
    sp = strstr(s1, s3);
    printf("��v���Ȃ��ꍇ : %s\n", sp);
    sp = strstr(s1, s4);
    printf("�����Ώە������蒷���ꍇ : %s\n", sp);
    sp = strstr(s1, s5);
    printf("\\0 : %s\n\n", sp);

    printf("����֐�\n");
    sp = StdStr_Strstr(s1, s2);
    printf("��v����ꍇ : %s\n", sp);
    sp = StdStr_Strstr(s1, s3);
    printf("��v���Ȃ��ꍇ : %s\n", sp);
    sp = StdStr_Strstr(s1, s4);
    printf("�����Ώە������蒷���ꍇ : %s\n", sp);
    sp = StdStr_Strstr(s1, s5);
    printf("\\0 : %s\n", sp);
}


void UT_StdStr_Strtok()
{
    char str1[] = ",ABCD ef..1234./.,,G,";
    char* tp1;
    char str2[] = ",ABCD ef..1234./.,,G,";
    char* tp2;

    /* �X�y�[�X.����؂�ɕ�����𒊏o */
    printf("�W���֐�\n");
    tp1 = strtok(str1, " .,../");
    puts(tp1);
    while (tp1 != 0) {
        tp1 = strtok(0, " .,../");
        if (tp1 != 0) puts(tp1);
    }

    /* �X�y�[�X.����؂�ɕ�����𒊏o */
    printf("\n");
    printf("����֐�\n");
    tp2 = StdStr_Strtok(str2, " .,../");
    puts(tp2);
    while (tp2 != 0) {
        tp2 = StdStr_Strtok(0, " .,../");
       if (tp2 != 0) puts(tp2);
    }
}

void one()
{
    int a;
    if (a > ONE)
    {
    }
    else
    {
    }
}



int main(void)
{
    //UT_StdStr_Strstr();
    UT_StdStr_Strtok();


#if 0
    double jisaku = 0; ;/*�@0�`PI/4�͈̔͂Ȃ炩�Ȃ�̐��x*/
    double hyojun = 0; ;
    jisaku = StdArc_Sin(314);/*�@0�`PI/4�͈̔͂Ȃ炩�Ȃ�̐��x*/;
    hyojun = sin(314);
    printf("����%f\n", jisaku);
    printf("�W��%f\n", hyojun);
    printf("�덷%f%%\n",100.0*(hyojun - jisaku) / hyojun);

    printf("����%f\n", StdArc_Floor(-1.9999999999999999999999999999));
    printf("�W��%f\n", floor(-1.9999999999999999999999999999));
    printf("�덷%f%%\n", 100.0 * (hyojun - jisaku) / hyojun);
#endif

#if 0
    printf("����%f\n", StdArc_Ceil(-0.00000000000000000000000001));
    printf("�W��%f\n", ceil(-0.00000000000000000000000001));
    printf("�덷%f%%\n", 100.0 * (hyojun - jisaku) / hyojun);
#endif

#if 0
    printf("����%f\n", StdArc_Fabs(-11.00000000000000000000000001));
    printf("�W��%f\n", fabs(-11.00000000000000000000000001));
#endif
#if 0
    for (double rad = 3.14159265358979/2; rad < 3.1415926535898/2; rad += 0.000000000000001)
    {
        printf("����%f  / �W��%f\n", StdArc_Tan(rad), tan(rad));
    }
#endif
#if 0
    double x;
    for ( x = -10; x < 10; x+= 0.1)
    {
        printf("����%f  / �W��%f\n", StdArc_Exp(x), exp(x));
        //printf("%lf,%f%%\n",x, (StdArc_Exp(x)-exp(x))*100/ exp(x));
    }
#endif
#if 1
    double64t x,y;
    for (x = -1; x <= 1; x += 0.3)
    {
        for (y = -1; y <= 1; y += 0.3)
        {
            printf("����%f ,%f�@/�@����%f  / �W��%f\n", x,y, StdArc_Atan2(x,y), atan2(x,y));
            //printf("%lf,%f%%\n",x, (StdArc_Exp(x)-exp(x))*100/ exp(x));
        }
    }
#endif
    

}

