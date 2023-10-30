#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 
#pragma warning(disable:4996)

float matmulti(float*, float*);
float sgn(float);
float sigmoid(float,float);
float theta_traj(float,float,float);

void main(void) {
////////共通パラメータ//////////////////////////
	double theta_d = 3.14 / 2;		//目標角速度
	double theta = 0;				//目標角度
	double theta_last = 0;          //一個前の目標角度
	double theta_dot_last = 0;      //
	double theta_dot = 0;			//目標角度の微分
	double theta_2dot = 0;          //目標角度の2回微分
	int i, j,k;
	float time=0;                   //現在の時間[s]
	float time_f;					//終了時間
	float theta_peak;               //cos軌道の最大値[rad]
	float peak_time;                //開始からcos軌道が最大値になるまでの時間
	float T;                        //サンプリングタイム[s]
	int mode = 2;					//1:PID /2:SMC(new) 3:SMC&PD ハイブリッド

/////////////////////////////////////////////////
//    制御対象のパラメータ        ////////////// 
////////////////////////////////////////////////     //無駄にサーボ系になってる　1行目は不要
float Asys[3][3] = { { 1, -0.01, -0.0000487 },       // 制御対象(モータのモデル式)  同定値をもとにサンプリングタイム０．０１ｓで離散化 状態変数の更新用
				 	 { 0,     1,  0.0096105 },       // 制御対象(モータのモデル式)  同定値をもとにサンプリングタイム０．０１ｓで離散化 状態変数の更新用
				 	 { 0,     0,  0.9231163 } };     // 制御対象(モータのモデル式)  同定値をもとにサンプリングタイム０．０１ｓで離散化 状態変数の更新用
float Bsys[3] = { -4.744e-8, 0.0000141, 0.0027904 }; // 制御対象(モータのモデル式)  同定値をもとにサンプリングタイム０．０１ｓで離散化 状態変数の更新用	
float ita, D, J, Gain,alpha;

//////////////////////////////////////////////////
///　　　　　　変数
/////////////////////////////////////////////////
float  x[2][3] = { { 0.0, 3.14/20, 0.0 }, //left
					{ 0.0, 3.14/20, 0.0 }};//right
float u1[2]			= { 0 };
float u2[2]			= { 0 };
float u[2]		    = { 0 };
float sigma[2]		= { 0 };
float ABSsigma[2]	= { 0 };
float anti_u = 0;//外乱

////////////////////////////////////////////////////
//        P(I)D制御用パラメータ         ///////////////
///////////////////////////////////////////////////
	//変数
float e[2]			= { 0 };
float last_e[2]		= { 0 };
float delta_e[2]	= { 0 };
float Se[2]			= { 0 };

	//定数
float kp = 500;            
float ki = 0;
float kd = 0.0;
//////////////////////////////////////////////////




////////////////////////////////////////////////////
 //ファイル出力

	FILE *fp;
	fopen_s(&fp, "output.csv", "w");
	fprintf(fp, "time,e[0],delta_e[0],x[0][1],x[0][2],u[0],u1[0],u2[0],sigma[0],e[1],delta_e[1],x[1][1],x[1][2],u[1],u1[1],u2[1],sigma[1],theta,ita,alpha,Gain \n");

	{
		T = 0.01;  //サンプリングタイム[s]
		time_f = 16;//終了時間[s]

		//初期値の調整
		theta_last = theta;
		theta_dot_last = theta_dot;
		theta = theta_traj(time, 45 * 3.14 / 180, 4);
		theta_dot = (theta - theta_last) / T;
		theta_2dot = (theta_dot - theta_dot_last) / T;
		for (j = 0; j < 2; j++) {
			e[j] =- theta + x[j][1];								//制御量(角度)の偏差
		}
	}

	//シミュレータ
	for (time = 0; time < time_f; time+=T) {
		theta_last = theta;
		theta_dot_last = theta_dot;
		theta=theta_traj(time,45 *3.14/180,4);						//目標軌道を逐次計算
		theta_dot = (theta - theta_last) / T;
		theta_2dot = (theta_dot - theta_dot_last) / T;

		//実際のsystem
		float newX[2][3];

		for (j = 0; j < 2;j++) {
				newX[j][0] = matmulti(Asys[0], x[j]) + Bsys[0] * u[j];
				newX[j][1] = matmulti(Asys[1], x[j]) + Bsys[1] * u[j];
				newX[j][2] = matmulti(Asys[2], x[j]) + Bsys[2] * u[j];

				for (int i = 0; i < 3; i++) {
					x[j][i] = newX[j][i];
				}
				if (mode == 1) {//位置型PID
					last_e[j] = e[j];
					e[j] = -theta +x[j][1];							//制御量(角度)の偏差
					delta_e[j] = (e[j] - last_e[j]) / T; 			//偏差の微分
					Se[j] += (e[j] + last_e[j]) / 2 * T;			//偏差の積分値
					u[j] =- (kp*e[j] + ki * Se[j] + kd * delta_e[j]);//入力 操作量
				}

				else if (mode == 2) {
					//パラメータ設定
					D = 1.38;	//新32.432 / 旧1.38
					J = 0.1725;	//新0.246  / 旧0.1725
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
					e[j] = -theta+x[j][1];							//制御量(角度)の偏差
					delta_e[j] = (e[j] - last_e[j]) / T; 			//偏差の微分
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


//////(3×1行列)かける(1×3行列)の計算///////////////
float matmulti(float *a, float *b) {
	float c;
	c = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return c;
}
////////////////////////////////////////////////////


////////////////sgn関数//////////////////////////////
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


//////////////////平滑関数(sgn関数の代用)/////////////
float sigmoid(float v, float ita) {
	return  v / (fabsf(v) + ita);
}
//////////////////////////////////////////////////////


///////cosの目標軌道////////////////////////////////
float theta_traj(float time, float theta_peak, float peak_time) {
	float theta_r;
	theta_r = (-theta_peak/2.0 * cos(time / peak_time * 3.14) + theta_peak/2.0);
	return theta_r;
}
/////////////////////////////////////////////////////



