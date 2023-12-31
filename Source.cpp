#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h> 

#pragma warning(disable:4996)
float matmulti(float*, float*);

float sgn(float v) {
	if (v > 0) {
		return 1;
	}
	else if (v == 0) {
		return 0;

	}
	else return -1;
}


void main(void) {
////////共通パラメータ//////////////////////////
	double T = 0.01;				//サンプリング周期
	double theta_d = 3.14 / 2;		//目標角速度
	double theta = 0;				//目標角度
	double theta_last = 0;          //一個前の目標角度
	double theta_dot_last = 0;      //
	double theta_dot = 0;			//目標角度の微分
	double theta_2dot = 0;          //目標角度の2回微分
	int i, j,k;
	int n;
	int N = 1600;					//繰り返し回数
	int mode = 2;					//1:PID /2:SMC(new) 3:SMC&PD ハイブリッド

/////////////////////////////////////////////////
//    制御対象のパラメータ        ////////////// 
////////////////////////////////////////////////
float Asys[3][3] = { { 1, -0.01, -0.0000487 },       // 制御対象(モータのモデル式)  同定値をもとにサンプリングタイム０．０１ｓで離散化 状態変数の更新用
				 	 { 0,     1,  0.0096105 },       // 制御対象(モータのモデル式)  同定値をもとにサンプリングタイム０．０１ｓで離散化 状態変数の更新用
				 	 { 0,     0,  0.9231163 } };     // 制御対象(モータのモデル式)  同定値をもとにサンプリングタイム０．０１ｓで離散化 状態変数の更新用
float Bsys[3] = { -4.744e-8, 0.0000141, 0.0027904 }; // 制御対象(モータのモデル式)  同定値をもとにサンプリングタイム０．０１ｓで離散化 状態変数の更新用	
float ita, D, J, Gain,alpha;

///////////////////////////////////////////////
//　　　　　　荷重による非線形外乱
///////////////////////////////////////////////
float Kt = 29.2*0.001;  //トルク定数
float R  = 0.582;       //電気指定校
float M  = 10;		   //荷重10kg

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
float kp = 0;            
float ki = 0;
float kd = 0.0;
//////////////////////////////////////////////////



////////////////////////////////////////////////////
 //ファイル出力

	FILE *fp;
	fopen_s(&fp, "output.csv", "w");
	fprintf(fp, "time,e[0],delta_e[0],x[0][1],x[0][2],u[0],u1[0],u2[0],sigma[0],e[1],delta_e[1],x[1][1],x[1][2],u[1],u1[1],u2[1],sigma[1],theta,ita,alpha,Gain,mode \n");

	{
		int n = 0;
		//目標軌道
		theta_last = theta;
		theta_dot_last = theta_dot;
		theta = (-3.14 / 8 * cos(n / 400.0 * 3.14) + 3.14 / 8);
		//theta = 3.14 / 2;
		theta_dot = (theta - theta_last) / T;
		theta_2dot = (theta_dot - theta_dot_last) / T;

		//theta = 3.14 / 2;
		//実際のsystem
		float newX[2][3];

		for (j = 0; j < 2; j++) {
			e[j] = theta - x[j][1];							//制御量(角度)の偏差
			last_e[j] = e[j];
		}
	}

	//シミュレータ
	for (n = 0; n < N; n++) {
		//目標軌道
		theta_last = theta;
		theta_dot_last = theta_dot;
		theta = (-3.14 / 8 * cos(n / 400.0 * 3.14) + 3.14 / 8);
		//theta = 3.14 / 2;
		theta_dot = (theta - theta_last) / T;
		theta_2dot = (theta_dot - theta_dot_last) / T;

		//theta = 3.14 / 2;
		//実際のsystem
		float newX[2][3];

		for (j = 0; j < 2;j++) {
				//newX[j][0] = matmulti(Asys[0], x[j]) + Bsys[0] * u[j];
				newX[j][1] = matmulti(Asys[1], x[j]) + Bsys[1] * u[j];
				newX[j][2] = matmulti(Asys[2], x[j]) + Bsys[2] * u[j];

				for (int i = 0; i < 3; i++) {
					x[j][i] = newX[j][i];
				}
				if (mode == 1) {//位置型PID
					kp = 4000;
					kd = 10;
					last_e[j] = e[j];
					e[j] = theta-x[j][1];							//制御量(角度)の偏差
					delta_e[j] = (e[j] - last_e[j]) / T; 			//偏差の微分
					Se[j] += (e[j] + last_e[j]) / 2 * T;			//偏差の積分値
					u[j] = (kp*e[j] + ki * Se[j] + kd * delta_e[j]);//入力 操作量

					if (u[j] > 24) { u[j] = 24; }
					else if (u[j] < -24) { u[j] = -24; }
				}

				else if (mode == 2) {
					//パラメータ設定
					D = 1.38;
					J = 0.1725;
					Gain = 10;  //44   /22;   //   22 /22
					ita = 0.05; //0.1   /0.3 /0.1
					alpha = 800; // 2  /100 /100
					////////////////

					sigma[j] = delta_e[j] + alpha * e[j];
					//if (sigma[j] < 0) ABSsigma[j] = -sigma[j];
					ABSsigma[j] = fabsf(sigma[j]);

					u1[j] = J * (theta_2dot - alpha * x[j][2] + alpha * theta_dot) - D * x[j][2];
					u2[j] = Gain * sgn(sigma[j]);  // sigma[j] / (ABSsigma[j] + ita);
					u[j] = u1[j] + u2[j];
					
					last_e[j] = e[j];
					e[j] = theta-x[j][1];							//制御量(角度)の偏差
					delta_e[j] = (e[j] - last_e[j]) / T; 			//偏差の微分
				}

				
		}
		fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d \n"  ,  n / 100.0, e[0],delta_e[0],x[0][1] * 180 / 3.14, x[0][2] * 180 / 3.14, u[0], u1[0], u2[0], sigma[0],e[1],delta_e[1],x[1][1] * 180 / 3.14, x[1][2] * 180 / 3.14, u[1], u1[1], u2[1], sigma[1], theta * 180 / 3.14,ita,alpha,Gain,mode);

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



