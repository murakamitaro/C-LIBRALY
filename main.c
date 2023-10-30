#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include"func.h"
#include <math.h>

#define ONE 1

void UT_StdStr_Strstr()
{
    char    s1[] = "abcdefghijklmn";        /* 検索対象文字列 */
    char    s2[] = "defgh";                 /* 一致する場合 */
    char    s3[] = "xyz";                   /* 一致しない場合 */
    char    s4[] = "abcdefghijklmnopqr";    /* 検索対象文字列より長い場合 */
    char    s5[] = "";                      /* \0 */
    char* sp;


    printf("標準関数\n");
    sp = strstr(s1, s2);
    printf("一致する場合 : %s\n", sp);
    sp = strstr(s1, s3);
    printf("一致しない場合 : %s\n", sp);
    sp = strstr(s1, s4);
    printf("検索対象文字列より長い場合 : %s\n", sp);
    sp = strstr(s1, s5);
    printf("\\0 : %s\n\n", sp);

    printf("自作関数\n");
    sp = StdStr_Strstr(s1, s2);
    printf("一致する場合 : %s\n", sp);
    sp = StdStr_Strstr(s1, s3);
    printf("一致しない場合 : %s\n", sp);
    sp = StdStr_Strstr(s1, s4);
    printf("検索対象文字列より長い場合 : %s\n", sp);
    sp = StdStr_Strstr(s1, s5);
    printf("\\0 : %s\n", sp);
}


void UT_StdStr_Strtok()
{
    char str1[] = ",ABCD ef..1234./.,,G,";
    char* tp1;
    char str2[] = ",ABCD ef..1234./.,,G,";
    char* tp2;

    /* スペース.を区切りに文字列を抽出 */
    printf("標準関数\n");
    tp1 = strtok(str1, " .,../");
    puts(tp1);
    while (tp1 != 0) {
        tp1 = strtok(0, " .,../");
        if (tp1 != 0) puts(tp1);
    }

    /* スペース.を区切りに文字列を抽出 */
    printf("\n");
    printf("自作関数\n");
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
    double jisaku = 0; ;/*　0～PI/4の範囲ならかなりの精度*/
    double hyojun = 0; ;
    jisaku = StdArc_Sin(314);/*　0～PI/4の範囲ならかなりの精度*/;
    hyojun = sin(314);
    printf("自作%f\n", jisaku);
    printf("標準%f\n", hyojun);
    printf("誤差%f%%\n",100.0*(hyojun - jisaku) / hyojun);

    printf("自作%f\n", StdArc_Floor(-1.9999999999999999999999999999));
    printf("標準%f\n", floor(-1.9999999999999999999999999999));
    printf("誤差%f%%\n", 100.0 * (hyojun - jisaku) / hyojun);
#endif

#if 0
    printf("自作%f\n", StdArc_Ceil(-0.00000000000000000000000001));
    printf("標準%f\n", ceil(-0.00000000000000000000000001));
    printf("誤差%f%%\n", 100.0 * (hyojun - jisaku) / hyojun);
#endif

#if 0
    printf("自作%f\n", StdArc_Fabs(-11.00000000000000000000000001));
    printf("標準%f\n", fabs(-11.00000000000000000000000001));
#endif
#if 0
    for (double rad = 3.14159265358979/2; rad < 3.1415926535898/2; rad += 0.000000000000001)
    {
        printf("自作%f  / 標準%f\n", StdArc_Tan(rad), tan(rad));
    }
#endif
#if 0
    double x;
    for ( x = -10; x < 10; x+= 0.1)
    {
        printf("自作%f  / 標準%f\n", StdArc_Exp(x), exp(x));
        //printf("%lf,%f%%\n",x, (StdArc_Exp(x)-exp(x))*100/ exp(x));
    }
#endif
#if 1
    double64t x,y;
    for (x = -1; x <= 1; x += 0.3)
    {
        for (y = -1; y <= 1; y += 0.3)
        {
            printf("入力%f ,%f　/　自作%f  / 標準%f\n", x,y, StdArc_Atan2(x,y), atan2(x,y));
            //printf("%lf,%f%%\n",x, (StdArc_Exp(x)-exp(x))*100/ exp(x));
        }
    }
#endif
    

}

