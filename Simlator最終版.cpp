#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#pragma warning(disable:4996)

float matmulti(float*, float*);
float sgn(float);
float sigmoid(float,float);
float theta_traj(float,float,float);

void main(void) {
////////���ʃp�����[�^//////////////////////////
	double theta_d = 3.14 / 2;		//�ڕW�p���x
	double theta = 0;				//�ڕW�p�x
	double theta_last = 0;          //��O�̖ڕW�p�x
	double theta_dot_last = 0;      //
	double theta_dot = 0;			//�ڕW�p�x�̔���
	double theta_2dot = 0;          //�ڕW�p�x��2�����
	int i, j,k;
	float time=0;                   //���݂̎���[s]
	float time_f;					//�I������
	float theta_peak;               //cos�O���̍ő�l[rad]
	float peak_time;                //�J�n����cos�O�����ő�l�ɂȂ�܂ł̎���
	float T;                        //�T���v�����O�^�C��[s]
	int mode = 2;					//1:PID /2:SMC(new) 3:SMC&PD �n�C�u���b�h

/////////////////////////////////////////////////
//    ����Ώۂ̃p�����[�^        ////////////// 
////////////////////////////////////////////////     //���ʂɃT�[�{�n�ɂȂ��Ă�@1�s�ڂ͕s�v
float Asys[3][3] = { { 1, -0.01, -0.0000487 },       // ����Ώ�(���[�^�̃��f����)  ����l�����ƂɃT���v�����O�^�C���O�D�O�P���ŗ��U�� ��ԕϐ��̍X�V�p
				 	 { 0,     1,  0.0096105 },       // ����Ώ�(���[�^�̃��f����)  ����l�����ƂɃT���v�����O�^�C���O�D�O�P���ŗ��U�� ��ԕϐ��̍X�V�p
				 	 { 0,     0,  0.9231163 } };     // ����Ώ�(���[�^�̃��f����)  ����l�����ƂɃT���v�����O�^�C���O�D�O�P���ŗ��U�� ��ԕϐ��̍X�V�p
float Bsys[3] = { -4.744e-8, 0.0000141, 0.0027904 }; // ����Ώ�(���[�^�̃��f����)  ����l�����ƂɃT���v�����O�^�C���O�D�O�P���ŗ��U�� ��ԕϐ��̍X�V�p	
float ita, D, J, Gain,alpha;

//////////////////////////////////////////////////
///�@�@�@�@�@�@�ϐ�
/////////////////////////////////////////////////
float  x[2][3] = { { 0.0, 3.14/20, 0.0 }, //left
					{ 0.0, 3.14/20, 0.0 }};//right
float u1[2]			= { 0 };
float u2[2]			= { 0 };
float u[2]		    = { 0 };
float sigma[2]		= { 0 };
float ABSsigma[2]	= { 0 };
float anti_u = 0;//�O��

////////////////////////////////////////////////////
//        P(I)D����p�p�����[�^         ///////////////
///////////////////////////////////////////////////
	//�ϐ�
float e[2]			= { 0 };
float last_e[2]		= { 0 };
float delta_e[2]	= { 0 };
float Se[2]			= { 0 };

	//�萔
float kp = 500;            
float ki = 0;
float kd = 0.0;
//////////////////////////////////////////////////




////////////////////////////////////////////////////
 //�t�@�C���o��

	FILE *fp;
	fopen_s(&fp, "output.csv", "w");
	fprintf(fp, "time,e[0],delta_e[0],x[0][1],x[0][2],u[0],u1[0],u2[0],sigma[0],e[1],delta_e[1],x[1][1],x[1][2],u[1],u1[1],u2[1],sigma[1],theta,ita,alpha,Gain \n");

	{
		T = 0.01;  //�T���v�����O�^�C��[s]
		time_f = 16;//�I������[s]

		//�����l�̒���
		theta_last = theta;
		theta_dot_last = theta_dot;
		theta = theta_traj(time, 45 * 3.14 / 180, 4);
		theta_dot = (theta - theta_last) / T;
		theta_2dot = (theta_dot - theta_dot_last) / T;
		for (j = 0; j < 2; j++) {
			e[j] =- theta + x[j][1];								//�����(�p�x)�̕΍�
		}
	}

	//�V�~�����[�^
	for (time = 0; time < time_f; time+=T) {
		theta_last = theta;
		theta_dot_last = theta_dot;
		theta=theta_traj(time,45 *3.14/180,4);						//�ڕW�O���𒀎��v�Z
		theta_dot = (theta - theta_last) / T;
		theta_2dot = (theta_dot - theta_dot_last) / T;

		//���ۂ�system
		float newX[2][3];

		for (j = 0; j < 2;j++) {
				newX[j][0] = matmulti(Asys[0], x[j]) + Bsys[0] * u[j];
				newX[j][1] = matmulti(Asys[1], x[j]) + Bsys[1] * u[j];
				newX[j][2] = matmulti(Asys[2], x[j]) + Bsys[2] * u[j];

				for (int i = 0; i < 3; i++) {
					x[j][i] = newX[j][i];
				}
				if (mode == 1) {//�ʒu�^PID
					last_e[j] = e[j];
					e[j] = -theta +x[j][1];							//�����(�p�x)�̕΍�
					delta_e[j] = (e[j] - last_e[j]) / T; 			//�΍��̔���
					Se[j] += (e[j] + last_e[j]) / 2 * T;			//�΍��̐ϕ��l
					u[j] =- (kp*e[j] + ki * Se[j] + kd * delta_e[j]);//���� �����
				}

				else if (mode == 2) {
					//�p�����[�^�ݒ�
					D = 1.38;	//�V32.432 / ��1.38
					J = 0.1725;	//�V0.246  / ��0.1725
					Gain = 150;	//15
					ita = 0.05;	//0.01
					alpha = 4;	//4
					////////////////

					sigma[j] = delta_e[j] + alpha * e[j];
					u1[j] = J * (theta_2dot - alpha * x[j][2] + alpha * theta_dot) - D * x[j][2];
					//u2[j] = -Gain * sigmoid(sigma[j], ita);
					u2[j] = -Gain * sgn(sigma[j]);
					u[j] = u1[j] + u2[j];
					
					last_e[j] = e[j];
					e[j] = -theta+x[j][1];							//�����(�p�x)�̕΍�
					delta_e[j] = (e[j] - last_e[j]) / T; 			//�΍��̔���
				}

				//if (u[j] > 24) { u[j] = 24; }
				//else if (u[j] < -24) { u[j] = -24; }
		}
		fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf \n"  ,  time, e[0],delta_e[0],x[0][1] * 180 / 3.14, x[0][2] * 180 / 3.14, u[0], u1[0], u2[0], sigma[0],e[1],delta_e[1],x[1][1] * 180 / 3.14, x[1][2] * 180 / 3.14, u[1], u1[1], u2[1], sigma[1], theta * 180 / 3.14,ita,alpha,Gain);

		printf("%lf \n", sigma[0]);
	}
	fclose(fp);
	getchar();
}


//////(3�~1�s��)������(1�~3�s��)�̌v�Z///////////////
float matmulti(float *a, float *b) {
	float c;
	c = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return c;
}
////////////////////////////////////////////////////


////////////////sgn�֐�//////////////////////////////
float sgn(float v) {
	if (v > 0) {
		return 1;
	}
	else if (v == 0) {
		return 0;

	}
	else return -1;
}
//////////////////////////////////////////////////////


//////////////////�����֐�(sgn�֐��̑�p)/////////////
float sigmoid(float v, float ita) {
	return  v / (fabsf(v) + ita);
}
//////////////////////////////////////////////////////


///////cos�̖ڕW�O��////////////////////////////////
float theta_traj(float time, float theta_peak, float peak_time) {
	float theta_r;
	theta_r = (-theta_peak/2.0 * cos(time / peak_time * 3.14) + theta_peak/2.0);
	return theta_r;
}
/////////////////////////////////////////////////////



