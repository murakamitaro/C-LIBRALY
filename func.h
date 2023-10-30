#ifndef _FUNC_H_//_CHAR_FUNC_H_����`����Ă��Ȃ����endif�܂ł��C���N���[�h
#define _FUNC_H_//_CHAR_FUNC_H_�Ƃ����v���v���Z�b�T�}�N��(�ʏ̃K�[�h�}�N��)���`



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

//�ނ�����́@�Ƃ肠���������Ɍ��肵�đΉ��H�H
/*��{*/
double64t StdArc_Floor(double64t );				//��OK
double64t StdArc_Ceil(double64t);				//��OK
double64t StdArc_Fabs(double64t );				//��OK�@�@
double64t StdArc_Fmod(double64t, double64t);	//��OK

/*�}�N���[�����W�J*/
double64t StdArc_Sin(double64t);				//��OK
double64t StdArc_Cos(double64t);				//��OK
double64t StdArc_Tan(double64t);				//��OK
double64t StdArc_Asin(double64t);				//���Ƃ肠����OK�@ �������Ԉ���Ă��@���[�v100000�ʂ���Ȃ���-1,1�t�߂̌덷�ł���
double64t StdArc_Acos(double64t);				//���Ƃ肠����OK�@Asin�̐��x�Ɉˑ�
double64t StdArc_Atan(double64t);				//���A�L���͈͂��Ⴄ�@���[�v��100�񂭂炢�ɂ���Ƃ܂��܂��̐��x�����C�C�C
double64t StdArc_Atan2(double64t,double64t);	//���Batan�Ɉˑ��H
double64t StdArc_Cosh(double64t);				//��OK exp�g���Ă��v�Z�ł���
double64t StdArc_Exp(double64t);				//��OK

double64t StdArc_Pow(double64t, double64t);		//��OK�H�@�ۂ��̂͂ł��� sqrt�֐��ƕ����񐔂Ɉˑ�

/*�j���[�g���@*/
double64t StdArc_Sqrt(double64t );				//��OK
double64t StdArc_Log(double64t);				//��OK�@exp�̃o�O�������Œl���������Ȃ��Ă�
double64t StdArc_Log10(double64t);				//��OK�@Log�̐��x����




#endif//