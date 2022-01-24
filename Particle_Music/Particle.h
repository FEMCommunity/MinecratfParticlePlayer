#pragma warning(disable : 4996)
#ifndef Particle_MC
#define Particle_MC


#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;
constexpr long double pi = 3.1415926535897932384626433832795;
FILE* file1 = nullptr;
int Mode = 1;
int init;


#define Particle_type minecraft:end_rod



long double s_qrt(long double a) {
	return a * a;
}
//构造连续相切圆的向量
struct Particle_Vector {
	long double Vx;
	long double Vz;
};
	//直线
	struct Line
	{
		long double k;
		long double b;
		bool Test;
	};
	//点
	struct Point
	{
		long double z;
		long double x;
	};
	//求直线方程
	void GetLine(long double z0, long double z1, long double x0, long double x1, Line& out_Line)
	{
		const long double m = z1 - z0;
		if (m >= -0.000001 && m <= 0.000001)
		{
			out_Line.k = 1000000;
			out_Line.b = x0 - (1000000 * z0);
			out_Line.Test = false;
		}
		else
		{
			out_Line.k = (x1 - x0) / (z1 - z0);
			out_Line.b = x0 - (out_Line.k * z0);
			out_Line.Test = true;
		}
	}
	//求中位线
	void GetMidLine(Line& Line_in, Line& Line_out, long double z0, long double z1, long double x0, long double x1)
	{
		if (!Line_in.Test)
		{
			Line_out.k = 0;
			Line_out.b = (x1 + x0) * 0.5;
			Line_out.Test = true;
		}
		else if (Line_in.k <= -0.000001 || Line_in.k >= 0.000001)
		{
			Line_out.k = -1 / Line_in.k;
			Line_out.b = ((x1 + x0) * 0.5) - (Line_out.k * ((z1 + z0) * 0.5));
			Line_out.Test = true;
		}
		else
		{
			Line_out.k = 1000000;
			Line_out.b = ((x1 + x0) * 0.5) - (Line_out.k * ((z1 + z0) * 0.5));
			Line_out.Test = false;
		}
	}
	//求交点
	void GetCross(Line& L1, Line& L2, Point& Cross, long double Z)
	{
		if ((!L1.Test) && L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			Cross.z = Z;
			Cross.x = L2.b;
		}
		else if (!L1.Test)
		{
			Cross.z = Z;
			Cross.x = (L2.k * Z) + L2.b;
		}
		else
		{
			Cross.z = ((L2.b - L1.b) / (L1.k - L2.k));
			Cross.x = (L1.k * Cross.z) + L1.b;
		}
	}











//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\\
//-------------------------------------------------------------------------------终点特效部分-----------------------------------------------------------------------------------------\\
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\\








//螺旋圈阵
void print_round_move(long double ex, long double ey, long double ez) {
	int x_3 = (int)ex;
	long double COR;//RGB颜色通道
	long double COG;//RGB颜色通道
	long double COB;//RGB颜色通道

	COR = 0.3;//随机RGB颜色通道
	COG = 0.7;//随机RGB颜色通道
	COB = 0.4;//随机RGB颜色通道

	fprintf(file1, "execute if score @p Timer matches %d run particleex tickpolarparameter minecraft:end_rod %.10f %.10f %.10f %.10f %.10f %.10f 1 0 0 0 0 2 \"s1,dis=t*10,t*1.5\" 0.01 20 25\n", x_3, ex+0.5, ey+0.5, ez+0.5, COR, COG, COB);

}

//圆圈阵
void print_round(long double ex, long double ey, long double ez) {


	long double Omega1 = 2 * pi / 30;
	long double theta = 0.0;

	for (int A = 0; A <= 30; A++) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex tickpolarparameter minecraft:end_rod %.10f %.10f %.10f 0.75686274 0.8235294 0.9411764 1 0 0 0 0 3 \"s1,dis=%.10f,t\" 0.1 1 1\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5, theta);
		theta+= Omega1;
	}
	//particleex tickpolarparameter minecraft:end_rod 0 8 0 1 1 1 1 0 0 0 0 2 "s1,dis=0,t" 0.1 1 1
}

void summon_firework(long double ex, long double ey, long double ez) {

	fprintf(file1, "execute if score @p Timer matches %d run summon minecraft:firework_rocket %.10f %.10f %.10f {FireworksItem:{tag:{Fireworks:{Flight:0,Explosions:[{Type:0,Colors:[I;50431],FadeColors:[I;10239]},{Type:0,Colors:[I;65526],FadeColors:[I;16777215]},{Type:0,Colors:[I;12976383],FadeColors:[I;16711880]}]}},id:\"minecraft:firework_rocket\",Count:1},Life:0,LifeTime:1}\n",(int)ex, ex, ey, ez);



	///summon minecraft:firework_rocket %.10f %.10f %.10f {FireworksItem:{tag:{Fireworks:{Flight:0,Explosions:[{Type:0,Colors:[I;50431],FadeColors:[I;10239]},{Type:0,Colors:[I;65526],FadeColors:[I;16777215]},{Type:0,Colors:[I;12976383],FadeColors:[I;16711880]}]}},id:"minecraft:firework_rocket",Count:1},Life:0,LifeTime:1}
}

void F_Rose(long double ex, long double ey, long double ez) {
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -0.7853981634 0 \"s1,dis,cr,cg,cb=t,5*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 0.7853981634 \"s1,dis,cr,cg,cb=(0.7853981634-t),5*cos(2*(0.7853981634-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0.7853981634 1.5707963268 \"s1,dis,cr,cg,cb=t,5*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 1.5707963268 2.3561944902 \"s1,dis,cr,cg,cb=(2.3561944902+1.5707963268-t),5*cos(2*(2.3561944902+1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 2.3561944902 3.1415926535 \"s1,dis,cr,cg,cb=t,5*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -3.1415926535 -2.3561944902 \"s1,dis,cr,cg,cb=(-2.3561944902-3.1415926535-t),5*cos(2*(-2.3561944902-3.1415926535-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -2.3561944902 -1.5707963268 \"s1,dis,cr,cg,cb=t,5*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -1.5707963268 -0.7853981634 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t),5*cos(2*(-0.7853981634-1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 -3.1415926535 3.1415926535 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t),5*cos(2*(-0.7853981634-1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.01,,z*2*sin(a))\"\n", (int)ex+15, ex + 0.5, ey + 0.5, ez + 0.5);
}

void F_D_Rose(long double ex, long double ey, long double ez) {
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -0.7853981634 0 \"s1,dis,cr,cg,cb=t,5*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 0.7853981634 \"s1,dis,cr,cg,cb=(0.7853981634-t),5*cos(2*(0.7853981634-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0.7853981634 1.5707963268 \"s1,dis,cr,cg,cb=t,5*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 1.5707963268 2.3561944902 \"s1,dis,cr,cg,cb=(2.3561944902+1.5707963268-t),5*cos(2*(2.3561944902+1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 2.3561944902 3.1415926535 \"s1,dis,cr,cg,cb=t,5*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -3.1415926535 -2.3561944902 \"s1,dis,cr,cg,cb=(-2.3561944902-3.1415926535-t),5*cos(2*(-2.3561944902-3.1415926535-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -2.3561944902 -1.5707963268 \"s1,dis,cr,cg,cb=t,5*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -1.5707963268 -0.7853981634 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t),5*cos(2*(-0.7853981634-1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -0.7853981634 0 \"s1,dis,cr,cg,cb=t,3*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 0.7853981634 \"s1,dis,cr,cg,cb=(0.7853981634-t),3*cos(2*(0.7853981634-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0.7853981634 1.5707963268 \"s1,dis,cr,cg,cb=t,3*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 1.5707963268 2.3561944902 \"s1,dis,cr,cg,cb=(2.3561944902+1.5707963268-t),3*cos(2*(2.3561944902+1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 2.3561944902 3.1415926535 \"s1,dis,cr,cg,cb=t,3*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -3.1415926535 -2.3561944902 \"s1,dis,cr,cg,cb=(-2.3561944902-3.1415926535-t),3*cos(2*(-2.3561944902-3.1415926535-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -2.3561944902 -1.5707963268 \"s1,dis,cr,cg,cb=t,3*cos(2*t),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -1.5707963268 -0.7853981634 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t),3*cos(2*(-0.7853981634-1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 -3.1415926535 3.1415926535 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t),5*cos(2*(-0.7853981634-1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.02,,z*2*sin(a))\"\n", (int)ex+15, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 -3.1415926535 3.1415926535 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t),3*cos(2*(-0.7853981634-1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.06,,z*2*sin(a))\"\n", (int)ex+15, ex + 0.5, ey + 0.5, ez + 0.5);
}

void L_Rose(long double ex, long double ey, long double ez) {
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -0.7853981634 0 \"s1,dis,cr,cg,cb=t+0.7853981634,4*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 0.7853981634 \"s1,dis,cr,cg,cb=(0.7853981634-t+0.7853981634),4*sin(2*(0.7853981634-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0.7853981634 1.5707963268 \"s1,dis,cr,cg,cb=t+0.7853981634,4*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 1.5707963268 2.3561944902 \"s1,dis,cr,cg,cb=(2.3561944902+1.5707963268-t+0.7853981634),4*sin(2*(2.3561944902+1.5707963268-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 2.3561944902 3.1415926535 \"s1,dis,cr,cg,cb=t+0.7853981634,4*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -3.1415926535 -2.3561944902 \"s1,dis,cr,cg,cb=(-2.3561944902-3.1415926535-t+0.7853981634),4*sin(2*(-2.3561944902-3.1415926535-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -2.3561944902 -1.5707963268 \"s1,dis,cr,cg,cb=t+0.7853981634,4*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -1.5707963268 -0.7853981634 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t+0.7853981634),4*sin(2*(-0.7853981634-1.5707963268-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 -3.1415926535 3.1415926535 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t),4*sin(2*(-0.7853981634-1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex+15, ex + 0.5, ey + 0.5, ez + 0.5);
}

void L_D_Rose(long double ex, long double ey, long double ez) {
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -0.7853981634 0 \"s1,dis,cr,cg,cb=t+0.7853981634,4*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 0.7853981634 \"s1,dis,cr,cg,cb=(0.7853981634-t+0.7853981634),4*sin(2*(0.7853981634-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0.7853981634 1.5707963268 \"s1,dis,cr,cg,cb=t+0.7853981634,4*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 1.5707963268 2.3561944902 \"s1,dis,cr,cg,cb=(2.3561944902+1.5707963268-t+0.7853981634),4*sin(2*(2.3561944902+1.5707963268-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 2.3561944902 3.1415926535 \"s1,dis,cr,cg,cb=t+0.7853981634,4*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -3.1415926535 -2.3561944902 \"s1,dis,cr,cg,cb=(-2.3561944902-3.1415926535-t+0.7853981634),4*sin(2*(-2.3561944902-3.1415926535-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -2.3561944902 -1.5707963268 \"s1,dis,cr,cg,cb=t+0.7853981634,4*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -1.5707963268 -0.7853981634 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t+0.7853981634),4*sin(2*(-0.7853981634-1.5707963268-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -0.7853981634 0 \"s1,dis,cr,cg,cb=t+0.7853981634,6*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 0.7853981634 \"s1,dis,cr,cg,cb=(0.7853981634-t+0.7853981634),6*sin(2*(0.7853981634-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0.7853981634 1.5707963268 \"s1,dis,cr,cg,cb=t+0.7853981634,6*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 1.5707963268 2.3561944902 \"s1,dis,cr,cg,cb=(2.3561944902+1.5707963268-t+0.7853981634),6*sin(2*(2.3561944902+1.5707963268-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 2.3561944902 3.1415926535 \"s1,dis,cr,cg,cb=t+0.7853981634,6*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -3.1415926535 -2.3561944902 \"s1,dis,cr,cg,cb=(-2.3561944902-3.1415926535-t+0.7853981634),6*sin(2*(-2.3561944902-3.1415926535-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -2.3561944902 -1.5707963268 \"s1,dis,cr,cg,cb=t+0.7853981634,6*sin(2*(t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 -1.5707963268 -0.7853981634 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t+0.7853981634),6*sin(2*(-0.7853981634-1.5707963268-t+0.7853981634)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 5 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 -3.1415926535 3.1415926535 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t),4*sin(2*(-0.7853981634-1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex+15, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 -3.1415926535 3.1415926535 \"s1,dis,cr,cg,cb=(-0.7853981634-1.5707963268-t),6*sin(2*(-0.7853981634-1.5707963268-t)),sin(t*1.5)/4+0.5,sin(t*2)/4+0.5,sin(t*2.5)/4+0.5\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.08,,z*2*sin(a))\"\n", (int)ex+15, ex + 0.5, ey + 0.5, ez + 0.5);
}

void L_F_Rose(long double ex, long double ey, long double ez) {
	L_Rose(ex, ey, ez);
	F_Rose(ex, ey, ez);
}

void L_F_D_Rose(long double ex, long double ey, long double ez) {
	L_D_Rose(ex, ey, ez);
	F_D_Rose(ex, ey, ez);
}

void Butter_Fly(long double ex, long double ey, long double ez,int Temround,long double Butterflysize) {
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.2*sin(t))\" 0.01 %d 25\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize, Temround * 50);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.2*sin(t))\" 0.01 1\n", (int)ex + 20, ex + 0.5, ey + 0.5, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.25*sin(t))\" 0.01 1\n", (int)ex + 21, ex + 0.5+0.25, ey + 0.5+0.25, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.3*sin(t))\" 0.01 1\n", (int)ex + 22, ex + 0.5+0.5, ey + 0.5+0.25*2, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.35*sin(t))\" 0.01 1\n", (int)ex + 23, ex + 0.5+0.75, ey + 0.5+0.25*3, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.4*sin(t))\" 0.01 1\n", (int)ex + 24, ex + 0.5+1, ey + 0.5+0.25*4, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.45*sin(t))\" 0.01 1\n", (int)ex + 25, ex + 0.5+1.25, ey + 0.5+0.25*5, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.5*sin(t))\" 0.01 1\n", (int)ex + 26, ex + 0.5+1.5, ey + 0.5+0.25*6, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.55*sin(t))\" 0.01 1\n", (int)ex + 27, ex + 0.5+1.75, ey + 0.5+0.25*7, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.6*sin(t))\" 0.01 1\n", (int)ex + 28, ex + 0.5+2, ey + 0.5+0.25*8, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.65*sin(t))\" 0.01 1\n", (int)ex + 29, ex + 0.5+2.25, ey + 0.5+0.25*9, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.7*sin(t))\" 0.01 1\n", (int)ex + 30, ex + 0.5+2.5, ey + 0.5+0.25*10, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.75*sin(t))\" 0.01 1\n", (int)ex + 31, ex + 0.5+2.75, ey + 0.5+0.25*11, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.7*sin(t))\" 0.01 1\n", (int)ex + 32, ex + 0.5+3, ey + 0.5+0.25*12, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.65*sin(t))\" 0.01 1\n", (int)ex + 33, ex + 0.5+3.25, ey + 0.5+0.25*13, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.6*sin(t))\" 0.01 1\n", (int)ex + 34, ex + 0.5+3.5, ey + 0.5+0.25*14, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.55*sin(t))\" 0.01 1\n", (int)ex + 35, ex + 0.5+3.75, ey + 0.5+0.25*15, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.5*sin(t))\" 0.01 1\n", (int)ex + 36, ex + 0.5+4, ey + 0.5+0.25*16, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.45*sin(t))\" 0.01 1\n", (int)ex + 37, ex + 0.5+4.25, ey + 0.5+0.25*17, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.4*sin(t))\" 0.01 1\n", (int)ex + 38, ex + 0.5+4.5, ey + 0.5+0.25*18, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.35*sin(t))\" 0.01 1\n", (int)ex + 39, ex + 0.5+4.75, ey + 0.5+0.25*19, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.3*sin(t))\" 0.01 1\n", (int)ex + 40, ex + 0.5+5, ey + 0.5+0.25*20, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.25*sin(t))\" 0.01 1\n", (int)ex + 41, ex + 0.5+5.25, ey + 0.5+0.25*21, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.2*sin(t))\" 0.01 1\n", (int)ex + 42, ex + 0.5+5.5, ey + 0.5+0.25*22, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.25*sin(t))\" 0.01 1\n", (int)ex + 43, ex + 0.5+5.75, ey + 0.5+0.25*23, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.3*sin(t))\" 0.01 1\n", (int)ex + 44, ex + 0.5+6, ey + 0.5+0.25*24, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.35*sin(t))\" 0.01 1\n", (int)ex + 45, ex + 0.5+6.25, ey + 0.5+0.25*25, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.4*sin(t))\" 0.01 1\n", (int)ex + 46, ex + 0.5+6.5, ey + 0.5+0.25*26, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.45*sin(t))\" 0.01 1\n", (int)ex + 47, ex + 0.5+6.75, ey + 0.5+0.25*27, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.5*sin(t))\" 0.01 1\n", (int)ex + 48, ex + 0.5+7, ey + 0.5+0.25*28, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.55*sin(t))\" 0.01 1\n", (int)ex + 49, ex + 0.5+7.25, ey + 0.5+0.25*29, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.6*sin(t))\" 0.01 1\n", (int)ex + 50, ex + 0.5+7.5, ey + 0.5+0.25*30, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.65*sin(t))\" 0.01 1\n", (int)ex + 51, ex + 0.5+7.75, ey + 0.5+0.25*31, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.7*sin(t))\" 0.01 1\n", (int)ex + 52, ex + 0.5+8, ey + 0.5+0.25*32, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.75*sin(t))\" 0.01 1\n", (int)ex + 53, ex + 0.5+8.25, ey + 0.5+0.25*33, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.7*sin(t))\" 0.01 1\n", (int)ex + 54, ex + 0.5+8.5, ey + 0.5+0.25*34, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.65*sin(t))\" 0.01 1\n", (int)ex + 55, ex + 0.5+8.75, ey + 0.5+0.25*35, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.6*sin(t))\" 0.01 1\n", (int)ex + 56, ex + 0.5+9, ey + 0.5+0.25*36, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.55*sin(t))\" 0.01 1\n", (int)ex + 57, ex + 0.5+9.25, ey + 0.5+0.25*37, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.5*sin(t))\" 0.01 1\n", (int)ex + 58, ex + 0.5+9.5, ey + 0.5+0.25*38, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 1 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.45*sin(t))\" 0.01 1\n", (int)ex + 59, ex + 0.5+9.75, ey + 0.5+0.25*39, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %.10f \"s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*%.10f,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(0.4*sin(t))\" 0.01 30\n", (int)ex + 60, ex + 0.5+10, ey + 0.5+0.25*40, ez + 0.5, pi * 2 * (long double)Temround, Butterflysize);
}

void Flower_3d(long double ex, long double ey, long double ez) {
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 6.28 \"s1,dis,s2,cr,cg,cb=t,5*sin(4*t),0.5,0.75+0.25*sin(t),0.2+0.1*cos(t),0.2+0.2*cos(t)\" 0.01 45 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 6.28 \"s1,dis,s2,cr,cg,cb=t,5*sin(4*t),0.5,0.75+0.25*sin(t),0.2+0.1*cos(t),0.2+0.2*cos(t)\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex+15, ex + 0.5, ey + 0.5, ez + 0.5);
}

void Flower_2d(long double ex, long double ey, long double ez) {
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 6.28 \"s1,dis,s2,cr,cg,cb=t,5*sin(4*t),0,0.75+0.25*sin(t),0.2+0.1*cos(t),0.2+0.2*cos(t)\" 0.01 45 15\n", (int)ex, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbapolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 6.28 \"s1,dis,s2,cr,cg,cb=t,5*sin(4*t),0,0.75+0.25*sin(t),0.2+0.1*cos(t),0.2+0.2*cos(t)\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex + 15, ex + 0.5, ey + 0.5, ez + 0.5);
}

void Flower_3d_And_2d(long double ex, long double ey, long double ez) {
	Flower_3d(ex, ey, ez);
	Flower_2d(ex, ey, ez);
}

void SeaStar(long double ex, long double ey, long double ez) {
	long double R = 2.0;
	for (int i = 0; i <= (int)R * 10; i++) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 1 0.8 0 1 0 0.1 0 0 6.28 \"s1, dis = t, (-2 - 2 ^ (sin(5 * t)))*%.10f\" 0.01 10\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i / 20);
	}
}

void SeaStar_Flash(long double ex, long double ey, long double ez) {
	long double R = 2.0;
	for (int i = 0; i <= (int)R * 10; i++) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 1 0.8 0 1 0 0 0 0 6.28 \"s1, dis = t, (-2 - 2 ^ (sin(5 * t)))*%.10f\" 0.01 1\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i / 20);
	}
	fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 1 0.8 0 1 0 0 0 0 6.28 \"s1, dis = t, (-2 - 2 ^ (sin(5 * t)))\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex + 20, ex + 0.5, ey + 0.5, ez + 0.5);
}

void SmallFlower(long double ex, long double ey, long double ez) {
	long double R = 2.0;
	for (int i = 0; i <= (int)R * 10; i++) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 1 0.8 0 1 0 0.1 0 0 6.28 \"s1, dis = t, (5 - 2 ^ (sin(5 * t)))*%.10f\" 0.01 10\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i / 20);
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 1 0.8 0 1 0 0.1 0 0 6.28 \"s1, dis = t, %.10f\" 0.01 10\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i / 20);
	}
}

void SmallFlower_Flash(long double ex, long double ey, long double ez) {
	long double R = 2.0;
	for (int i = 0; i <= (int)R * 10; i++) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 0 0.75 1 1 0 0 0 0 6.28 \"s1, dis = t, (5 - 2 ^ (sin(5 * t)))*%.10f\" 0.01 1\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i / 20);
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 0 0.75 1 1 0 0 0 0 6.28 \"s1, dis = t, %.10f\" 0.01 1\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i / 20);
	}
	fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 0 0.75 1 1 0 0 0 0 6.28 \"s1, dis = t, (5 - 2 ^ (sin(5 * t)))\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex + 19, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 0 0.75 1 1 0 0 0 0 6.28 \"s1, dis = t, 1\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex + 20, ex + 0.5, ey + 0.5, ez + 0.5);
}

void D_SmallFlower_Flash(long double ex, long double ey, long double ez) {
	long double R = 2.0;
	for (int i = 0; i <= (int)R * 10; i++) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 0 0.75 1 1 0 0 0 0 6.28 \"s1, dis = t, (5 - 2 ^ (sin(5 * t)))*%.10f\" 0.02 1\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i / 40);
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 0 0.75 1 1 0 0 0 0 6.28 \"s1, dis = t+0.3141592, (5 - 2 ^ (sin(5 * t)))*%.10f\" 0.04 1\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i / 120);
	}
	fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 0 0.75 1 1 0 0 0 0 6.28 \"s1, dis = t, (5 - 2 ^ (sin(5 * t)))/2\" 0.02 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex + 19, ex + 0.5, ey + 0.5, ez + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 0 0.75 1 1 0 0 0 0 6.28 \"s1, dis = t+0.3141592, (5 - 2 ^ (sin(5 * t)))/6\" 0.04 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex + 20, ex + 0.5, ey + 0.5, ez + 0.5);
}

void SeaStar_to_F(long double ex, long double ey, long double ez) {
	long double R = 2.0;
	for (int i = 0; i <= (int)R * 10; i++) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 1 0.8 0 1 0 0.1 0 0 6.28 \"s1, dis = t, (-%.10f - 2 ^ (sin(5 * t)))*0.25\" 0.01 10\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i);
	}
}

void SeaStar_to_F_Flash(long double ex, long double ey, long double ez) {
	long double R = 2.0;
	for (int i = 0; i <= (int)R * 10; i++) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 1 0.8 0.2 1 0 0 0 0 6.28 \"s1, dis = t, (-%.10f - 2 ^ (sin(5 * t)))*0.25\" 0.01 1\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i);
	}
	fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 1 0.8 0.2 1 0 0 0 0 6.28 \"s1, dis = t, (-20 - 2 ^ (sin(5 * t)))*0.25\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex + 20, ex + 0.5, ey + 0.5, ez + 0.5);
}

void Eight_Flower__Flash(long double ex, long double ey, long double ez) {
	long double R = 2.0;
	for (int i = 0; i <= (int)R * 10; i++) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 1 0.6 0 1 0 0 0 0 6.28 \"s1,dis=t,(2*abs(sin(2*t))+abs(sin(4*t)))*%.10f\" 0.01 1\n", (int)ex + i, ex + 0.5, ey + 0.5, ez + 0.5, (long double)i/10);
	}
	fprintf(file1, "execute if score @p Timer matches %d run particleex polarparameter minecraft:end_rod %.10f %.10f %.10f 1 0.6 0 1 0 0 0 0 6.28 \"s1,dis=t,(2*abs(sin(2*t))+abs(sin(4*t)))*2\" 0.01 0 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.04,,z*2*sin(a))\"\n", (int)ex + 20, ex + 0.5, ey + 0.5, ez + 0.5);
}

void Eight_flower_small_flower_star(long double ex, long double ey, long double ez) {
	Eight_Flower__Flash(ex, ey, ez);
	SeaStar_to_F_Flash(ex, ey, ez);
	SmallFlower_Flash(ex, ey, ez);
	SeaStar_Flash(ex, ey, ez);
}

///"s1,dis=t,2*abs(sin(2*t))+abs(sin(4*t))"
///particleex polarparameter minecraft:end_rod 0 10 0 1 0.8 0 1 0 0 0 0 6.28 "s1,dis=t,2-2^(sin(5*t))" 0.01 10
///particleex rgbatickpolarparameter minecraft:end_rod 0 10 0 0 0 0 0 6.28 "s1,dis,s2,cr,cg,cb=t,5*sin(4*t),0.5,0.75+0.25*sin(t),0.2+0.1*cos(t),0.2+0.2*cos(t)" 0.01 20 25
///particleex rgbatickpolarparameter minecraft:end_rod 0 10 0 0 0 0 0 6.28 "s1,dis,cr,cg,cb,s2=t,(E^cos(t)-2*cos(4*t)+(sin(t/12))^5)*3,0.25+0.25*sin(t),0.3+0.3*cos(t),0.6+0.1*sin(t),abs(sin(t))" 0.01 10
///71:1:2*sqrt(2)
///particleex tickpolarparameter minecraft:end_rod 0 4.5 14.5 1 1 1 1 0 0 0 -0.7285 2.2995 "s1,s2,dis=t+PI/4,(3*2*sqrt(2)*sin(t)*cos(t))/(sin(t)*sin(t)*sin(t)+cos(t)*cos(t)*cos(t))" 0.0001 1000
///particleex rgbaparameter end_rod ~ ~6 ~ 0 0 0 -3082 3082 "cr=0.9;cg=0.7;cb=0.05;a=2;u=floor(t/78.5)/25;v=t%157/25;x=a*(cos(u)*cos(v))^3;y=a*(sin(u)*cos(v))^3;z=a*sin(v)^3" 5 100 \"a=0.05;(vx,,vy,,vz)=(-sin(a),0,-cos(a),,0,1,0,,cos(a),0,-sin(a))*(x*2*sin(a),,0.1,,z*2*sin(a))\"
///particleex tickpolarparameter minecraft:end_rod 0 10 0 1 1 1 1 0 0 0 -3.1415926535 3.1415926535 "dis,s1=5*sin(2*t),t" 0.01 10 0
/// particleex tickpolarparameter minecraft : end_rod - 8 3.5 - 25 1 0.8 0 1 0 0 0 0 3.14 "s1,dis=t,(-2-2^(sin(5*t)))/3" 0.01 10


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\\
//-------------------------------------------------------------------------------绘制线条部分-----------------------------------------------------------------------------------------\\
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\\





int Startype = 0;

void Star_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	long double S = sqrt(s_qrt((x2 - x1)) + s_qrt((z2 - z1)));//求位移
	long double theta = atan((z2 - z1) / deltaT);
	long double H = (S/6) ;
	long double A = S * 2.0 * sqrt(2.0) / 71.0;
	int N = 628 / (int)deltaT;
	N++;
	if (Startype == 0) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 3.14 \"s1,dis,cr,cg,cb=%.10f+t,(-2-2^(sin(5*t)))*%.10f,sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.005 %d 20\n", int(x1), (x1 + x2) / 2.0, y1 + 0.5, (z2 + z1) / 2.0, theta, H, N);
		Startype++;
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 3.14 \"s1,dis,cr,cg,cb=%.10f-t,(-2-2^(sin(5*t)))*%.10f,sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.005 %d 20\n", int(x1), (x1 + x2) / 2.0, y1 + 0.5, (z2 + z1) / 2.0, theta, H, N);
		Startype--;
	}
}


//绘制直线
void straight_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double S = sqrt(s_qrt((x2 - x1)) + s_qrt((z2 - z1)));//求位移
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double vy = ((y2 - y1) / deltaT);//参数方程（Y轴）
	int x = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(S / deltaT))*10.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量
	


	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = t+0.5, %.10f*t+0.5, %.10f*t+0.5, sin(t/7)/4+0.75, cos(t/5)/4+0.75, sin(t/3)/4+0.75\" %.10f %d 25\n", x, x1, y1, z1, deltaT2, vy, vz, NumBC_, (int)NumBC);
}


//笛卡儿叶形线
void Folium_of_Descartes(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	long double S = sqrt(s_qrt((x2 - x1)) + s_qrt((z2 - z1)));//求位移
	long double theta = atan((z2 - z1) / deltaT);
	long double H = S / 71.0;
	long double A = S * 2.0 * sqrt(2.0) / 71.0;
	int N = 30280 / (16*(int)deltaT);
	N++;
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 -0.7287 2.2997 \"s1,s2,dis,cr,cg,cb=%.10f,t+PI/4,(3*%.10f*sin(t)*cos(t))/(sin(t)*sin(t)*sin(t)+cos(t)*cos(t)*cos(t)),sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.0016 %d 20\n", int(x1), (x1 + x2) / 2.0 + 0.5, y1 + H + 0.5, (z2 + z1) / 2.0 + 0.5, theta, A, N);
}

void Folium_of_Descartes_W(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	long double S = sqrt(s_qrt((x2 - x1)) + s_qrt((z2 - z1)));//求位移
	long double theta = atan((z2 - z1) / deltaT);
	long double H = S / 71.0;
	long double A = S * 2.0 * sqrt(2.0) / 71.0;
	int N = 30280 / (16*(int)deltaT);
	N++;
	D_SmallFlower_Flash(x2,y2,z2);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickpolarparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 -0.7287 2.2997 \"s1,s2,dis,cr,cg,cb=%.10f,t+PI/4,(3*%.10f*sin(t)*cos(t))/(sin(t)*sin(t)*sin(t)+cos(t)*cos(t)*cos(t)),sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.0016 %d 20\n", int(x1), (x1 + x2) / 2.0 + 0.5, y1 + H + 0.5, (z2 + z1) / 2.0 + 0.5, theta, A, N);
}

//正弦曲线
void sin_straight_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double S = sqrt(s_qrt((x2 - x1)) + s_qrt((z2 - z1)));//求位移
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double vy = ((y2 - y1) / deltaT);//参数方程（Y轴）
	int x = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(S / deltaT)) * 15.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量
	long double Sin_A_;//正弦曲线的振幅
	Sin_A_ = S / 10;//计算振幅
	


	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = t+0.5,%.10f*sin(t/%.10f)+%.10f*t+0.5, %.10f*t+0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x, x1, y1, z1, deltaT2, Sin_A_, deltaT/(6*pi), vy, vz, NumBC_, (int)NumBC);
}

//绘制抛物线
void parabola_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {

	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double s = sqrt(s_qrt((x2 - x1)) + s_qrt((z2 - z1)));//求位移
	int x = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(s / deltaT))*20.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量
	

	if (abs(z2 - z1) >= deltaT) {
		Lamta = (long double)((int)(5 * (abs(z2 - z1) / deltaT)));
	}
	double H;//抛物线最高点
	double deltaY = y2 - y1;//Y轴相对坐标
	double deltaX = x2 - x1;//X轴相对坐标

	if (y2 > y1) {
		H = 0.2 * s + deltaY;//高度的定义
	}
	else {
		H = 0.2 * s;//高度的定义
	}

	double a;//y=bx(x-a)
	double b;//y=bx(x-a)
	if (deltaY != 0) {
		a = ((4 * H * deltaX) + sqrt((16 * H * H * deltaX * deltaX) - 16 * H * deltaY * deltaX * deltaX)) / (2 * deltaY);
		if (a / 2 < 0 || a / 2 > x2) {
			a = ((4 * H * deltaX) - sqrt((16 * H * H * deltaX * deltaX) - 16 * H * deltaY * deltaX * deltaX)) / (2 * deltaY);
		}
		b = (-4 * H) / (a * a);
	}
	else if (deltaY == 0) {
		a = deltaX;
		b = (-4 * H) / (a * a);
	}//求y轴参数方程
	
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = t+0.5, (%.10f*t*(t-%.10f))+0.5, %.10f*t+0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x, x1, y1, z1, deltaT2, b, a, vz, NumBC_, (int)NumBC);
}

//螺线
void spiral_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	//求平均速度（直线移动速度）
	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double vy = ((y2 - y1) / deltaT);//参数方程（Y轴）
	long double s = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));//路程
	long double h = y2 - y1;//高度
	long double theta = atan((x2 - x1) / (z2 - z1));//水平偏转角
	long double phi = atan(h / s);//竖直偏转角
	long double omega = 2 * deltaT * pi / (Lamta * deltaT);//转速
	long double AAA = s / 6;
	long double omega2 = pi / (Lamta * deltaT);//转速
	int x_1 = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(s / deltaT)) * 20.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量
	long double r_r = 3;
	if (s > 40) {
		r_r = s / 8.0;
	}



	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = 0+(%.10f * t - (%.10f*sin(t*%.10f)^2 * ((cos(%.10f) * cos(%.10f * t)) + (sin(%.10f) * sin(%.10f) * sin(%.10f * t)))) + 0.5), %.10f * t + (%.10f*sin(t*%.10f)^2 * (cos(%.10f) * sin(%.10f * t))) + 0.5, %.10f * t + (%.10f*sin(t*%.10f)^2 * ((sin(%.10f) * cos(%.10f * t)) - (cos(%.10f) * sin(%.10f) * sin(%.10f * t)))) + 0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x_1, x1, y1, z1, deltaT2, vx, r_r, pi / deltaT, theta, omega, theta, phi, omega, vy, r_r, pi / deltaT, phi, omega, vz, r_r, pi / deltaT, theta, omega, theta, phi, omega, NumBC_, (int)NumBC);
		
}

//螺线(带直线）
void spiral_line_straight(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	//求平均速度（直线移动速度）
	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double vy = ((y2 - y1) / deltaT);//参数方程（Y轴）
	long double s = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));//路程
	long double h = y2 - y1;//高度
	long double theta = atan((x2 - x1) / (z2 - z1));//水平偏转角
	long double phi = atan(h / s);//竖直偏转角
	long double omega = 2 * deltaT * pi / (Lamta * deltaT);//转速
	long double AAA = s / 6;
	long double omega2 = pi / (Lamta * deltaT);//转速
	int x_1 = (int)x1;//起始时间
	int x = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(s / deltaT)) * 20.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量
	long double r_r = 3;
	if (s > 40) {
		r_r = s / 8.0;
	}
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = 0+(%.10f * t - (%.10f*sin(t*%.10f)^2 * ((cos(%.10f) * cos(%.10f * t)) + (sin(%.10f) * sin(%.10f) * sin(%.10f * t)))) + 0.5), %.10f * t + (%.10f*sin(t*%.10f)^2 * (cos(%.10f) * sin(%.10f * t))) + 0.5, %.10f * t + (%.10f*sin(t*%.10f)^2 * ((sin(%.10f) * cos(%.10f * t)) - (cos(%.10f) * sin(%.10f) * sin(%.10f * t)))) + 0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x_1, x1, y1, z1, deltaT2, vx, r_r, pi / deltaT, theta, omega, theta, phi, omega, vy, r_r, pi / deltaT, phi, omega, vz, r_r, pi / deltaT, theta, omega, theta, phi, omega, NumBC_, (int)NumBC);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = t+0.5, %.10f*t+0.5, %.10f*t+0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x, x1, y1, z1, deltaT2, vy, vz, NumBC_, (int)NumBC);
}

//螺线组
void spiral_lines(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	//求平均速度（直线移动速度）
	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double vy = ((y2 - y1) / deltaT);//参数方程（Y轴）
	long double s = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));//路程
	long double h = y2 - y1;//高度
	long double theta = atan((x2 - x1) / (z2 - z1));//水平偏转角
	long double phi = atan(h / s);//竖直偏转角
	long double omega = 4*deltaT * pi / (Lamta * s);//转速
	long double AAA = s / 6;
	long double omega2 = pi / (Lamta * s);//转速
	int x_1 = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(s / deltaT)) * 20.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量
	long double r_r = 4;
	//螺线最大半径

	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = 0+(%.10f * t - (%.10f*sin(t*%.10f)^2 * ((cos(%.10f) * cos(%.10f * t)) + (sin(%.10f) * sin(%.10f) * sin(%.10f * t)))) + 0.5), %.10f * t + (%.10f*sin(t*%.10f) * (cos(%.10f) * sin(%.10f * t))) + 0.5, %.10f * t + (%.10f*sin(t*%.10f)^2 * ((sin(%.10f) * cos(%.10f * t)) - (cos(%.10f) * sin(%.10f) * sin(%.10f * t)))) + 0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x_1, x1, y1, z1, deltaT2, vx, r_r, pi / deltaT, theta, omega, theta, phi, omega, vy, r_r, pi / deltaT, phi, omega, vz, r_r, pi / deltaT, theta, omega, theta, phi, omega, NumBC_, (int)NumBC);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = 0+(%.10f * t - (%.10f*sin(t*%.10f)^2 * ((cos(%.10f) * cos(%.10f * t + (3.1415926535))) + (sin(%.10f) * sin(%.10f) * sin(%.10f * t+ (3.1415926535))))) + 0.5), %.10f * t + (%.10f*sin(t*%.10f)^2 * (cos(%.10f) * sin(%.10f * t+ (3.1415926535)))) + 0.5, %.10f * t + (%.10f*sin(t*%.10f)^2 * ((sin(%.10f) * cos(%.10f * t+ (3.1415926535))) - (cos(%.10f) * sin(%.10f) * sin(%.10f * t+ (3.1415926535))))) + 0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x_1, x1, y1, z1, deltaT2, vx, r_r, pi / deltaT, theta, omega, theta, phi, omega, vy, r_r, pi / deltaT, phi, omega, vz, r_r, pi / deltaT, theta, omega, theta, phi, omega, NumBC_, (int)NumBC);

}

//螺线组(带中心直线）
void spiral_lines_straight_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	//求平均速度（直线移动速度）
	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double vy = ((y2 - y1) / deltaT);//参数方程（Y轴）
	long double s = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));//路程
	long double h = y2 - y1;//高度
	long double theta = atan((x2 - x1) / (z2 - z1));//水平偏转角
	long double phi = atan(h / s);//竖直偏转角
	long double omega = 4 * deltaT * pi / (Lamta * deltaT);//转速
	long double AAA = s / 6;
	long double omega2 = pi / (Lamta * deltaT);//转速
	int x_1 = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(s / deltaT)) * 20.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量
	long double r_r = 3;
	if (s > 40) {
		r_r = s / 8.0;
	}//螺线最大半径
	if (r_r > 5) {
		r_r = 5;
	}
	int x = (int)x1;//起始时间

	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = 0+(%.10f * t - (%.10f*sin(t*%.10f)^2 * ((cos(%.10f) * cos(%.10f * t)) + (sin(%.10f) * sin(%.10f) * sin(%.10f * t)))) + 0.5), %.10f * t + (%.10f*sin(t*%.10f) * (cos(%.10f) * sin(%.10f * t))) + 0.5, %.10f * t + (%.10f*sin(t*%.10f)^2 * ((sin(%.10f) * cos(%.10f * t)) - (cos(%.10f) * sin(%.10f) * sin(%.10f * t)))) + 0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x_1, x1, y1, z1, deltaT2, vx, r_r, pi / deltaT, theta, omega, theta, phi, omega, vy, r_r, pi / deltaT, phi, omega, vz, r_r, pi / deltaT, theta, omega, theta, phi, omega, NumBC_, (int)NumBC);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = 0+(%.10f * t - (%.10f*sin(t*%.10f)^2 * ((cos(%.10f) * cos(%.10f * t + (3.1415926535))) + (sin(%.10f) * sin(%.10f) * sin(%.10f * t+ (3.1415926535))))) + 0.5), %.10f * t + (%.10f*sin(t*%.10f)^2 * (cos(%.10f) * sin(%.10f * t+ (3.1415926535)))) + 0.5, %.10f * t + (%.10f*sin(t*%.10f)^2 * ((sin(%.10f) * cos(%.10f * t+ (3.1415926535))) - (cos(%.10f) * sin(%.10f) * sin(%.10f * t+ (3.1415926535))))) + 0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x_1, x1, y1, z1, deltaT2, vx, r_r, pi / deltaT, theta, omega, theta, phi, omega, vy, r_r, pi / deltaT, phi, omega, vz, r_r, pi / deltaT, theta, omega, theta, phi, omega, NumBC_, (int)NumBC);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = t+0.5, %.10f*t+0.5, %.10f*t+0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x, x1, y1, z1, deltaT2, vy, vz, NumBC_, (int)NumBC);
}

//抛物线（下方向）
void parabola_line_r(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {

	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double s = sqrt(s_qrt((x2 - x1)) + s_qrt((z2 - z1)));//求位移
	int x = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(s / deltaT)) * 20.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量


	if (abs(z2 - z1) >= deltaT) {
		Lamta = (long double)((int)(5 * (abs(z2 - z1) / deltaT)));
	}
	double H;//抛物线最高点
	double deltaY = y2 - y1;//Y轴相对坐标
	double deltaX = x2 - x1;//X轴相对坐标

	if (y2 < y1) {
		H = -0.2 * s + deltaY;
	}
	else {
		H = -0.2 * s;
	}

	double a;//y=bx(x-a)
	double b;//y=bx(x-a)
	if (deltaY != 0) {
		a = ((4 * H * deltaX) + sqrt((16 * H * H * deltaX * deltaX) - 16 * H * deltaY * deltaX * deltaX)) / (2 * deltaY);
		if (a / 2 < 0 || a / 2 > x2) {
			a = ((4 * H * deltaX) - sqrt((16 * H * H * deltaX * deltaX) - 16 * H * deltaY * deltaX * deltaX)) / (2 * deltaY);
		}
		b = (-4 * H) / (a * a);
	}
	else if (deltaY == 0) {
		a = deltaX;
		b = (-4 * H) / (a * a);
	}//求y轴参数方程

	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = t+0.5, (%.10f*t*(t-%.10f))+0.5, %.10f*t+0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x, x1, y1, z1, deltaT2, b, a, vz, NumBC_, (int)NumBC);

}

//（有螺旋圈阵）的抛物线
void spiral_round_parabola_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {

	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double s = sqrt(s_qrt((x2 - x1)) + s_qrt((z2 - z1)));//求位移
	int x = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(s / deltaT)) * 20.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量


	if (abs(z2 - z1) >= deltaT) {
		Lamta = (long double)((int)(5 * (abs(z2 - z1) / deltaT)));
	}
	double H;//抛物线最高点
	double deltaY = y2 - y1;//Y轴相对坐标
	double deltaX = x2 - x1;//X轴相对坐标

	if (y2 > y1) {
		H = 0.2 * s + deltaY;//高度的定义
	}
	else {
		H = 0.2 * s;//高度的定义
	}

	double a;//y=bx(x-a)
	double b;//y=bx(x-a)
	if (deltaY != 0) {
		a = ((4 * H * deltaX) + sqrt((16 * H * H * deltaX * deltaX) - 16 * H * deltaY * deltaX * deltaX)) / (2 * deltaY);
		if (a / 2 < 0 || a / 2 > x2) {
			a = ((4 * H * deltaX) - sqrt((16 * H * H * deltaX * deltaX) - 16 * H * deltaY * deltaX * deltaX)) / (2 * deltaY);
		}
		b = (-4 * H) / (a * a);
	}
	else if (deltaY == 0) {
		a = deltaX;
		b = (-4 * H) / (a * a);
	}//求y轴参数方程

	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = t+0.5, (%.10f*t*(t-%.10f))+0.5, %.10f*t+0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x, x1, y1, z1, deltaT2, b, a, vz, NumBC_, (int)NumBC);
	print_round_move(x2, y2, z2);
}

//（有螺旋圈阵）的抛物线（反向）
void spiral_round_parabola_line_r(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {

	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double s = sqrt(s_qrt((x2 - x1)) + s_qrt((z2 - z1)));//求位移
	int x = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(s / deltaT)) * 20.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量


	if (abs(z2 - z1) >= deltaT) {
		Lamta = (long double)((int)(5 * (abs(z2 - z1) / deltaT)));
	}
	double H;//抛物线最高点
	double deltaY = y2 - y1;//Y轴相对坐标
	double deltaX = x2 - x1;//X轴相对坐标

	if (y2 < y1) {
		H = -0.2 * s + deltaY;
	}
	else {
		H = -0.2 * s;
	}

	double a;//y=bx(x-a)
	double b;//y=bx(x-a)
	if (deltaY != 0) {
		a = ((4 * H * deltaX) + sqrt((16 * H * H * deltaX * deltaX) - 16 * H * deltaY * deltaX * deltaX)) / (2 * deltaY);
		if (a / 2 < 0 || a / 2 > x2) {
			a = ((4 * H * deltaX) - sqrt((16 * H * H * deltaX * deltaX) - 16 * H * deltaY * deltaX * deltaX)) / (2 * deltaY);
		}
		b = (-4 * H) / (a * a);
	}
	else if (deltaY == 0) {
		a = deltaX;
		b = (-4 * H) / (a * a);
	}//求y轴参数方程

	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = t+0.5, (%.10f*t*(t-%.10f))+0.5, %.10f*t+0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25\n", x, x1, y1, z1, deltaT2, b, a, vz, NumBC_, (int)NumBC);
	print_round_move(x2, y2, z2);
}

void round_parabola_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD);

//连续相切圆曲线

Point Later_Center;
void Round_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{
	x1 += 0.5;
	x2 += 0.5;
	z1 += 0.5;
	z2 += 0.5;

	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (init == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center.z);
			Later_Center = Center;
			init = 1;
			if (z2 > z1)
			{
				Mode = 1;
			}
			else
			{
				Mode = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center.z, z1, Later_Center.x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			init = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center.z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center.z)
			{
				if (z1 <= Center.z && z1 >= Later_Center.z)
				{
					Mode = -1 * Mode;
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center.z)
				{
					Mode = -1 * Mode;
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center.z, Later_Center.x,
				Center.z, Center.x,
				R, Mode
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode << endl;
			*/
			Later_Center = Center;
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C*5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}
	

	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (init != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}

	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	long double vy = (((y2 - y1) / (Lamta*abs(x2-x1))));

	if (Mode == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t), %.10f * t, %.10f * cos(%.10f + %.10f * t), sin(PI*t/(7*%.10f)) / 2 + 0.5, cos(PI*t/(5*%.10f)) / 2 + 0.5, sin(PI*t/(3*%.10f)) / 2 + 0.5\" 1 %d 25\n", deltaT2, Center.x, y1, Center.z, deltaT* Lamta, R, Omega_0, Omega, vy, R, Omega_0, Omega, Lamta, Lamta, Lamta, (int)Lamta);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t), %.10f * t, %.10f * cos(%.10f - %.10f * t), sin(PI*t/(7*%.10f)) / 2 + 0.5, cos(PI*t/(5*%.10f)) / 2 + 0.5, sin(PI*t/(3*%.10f)) / 2 + 0.5\" 1 %d 25\n", deltaT2, Center.x, y1, Center.z, deltaT* Lamta, R, Omega_0, Omega, vy, R, Omega_0, Omega, Lamta, Lamta, Lamta, (int)Lamta);
	}
	init = 1;
}



Point Later_Center_Truck[6];
int Init_T[6] = { 0,1,1,1,1,1 };
int Mode_Tr[6] = { 1,1,1,1,1,1 };
int Initsizer = 0;
long double CurretTheta_T[6] = { pi * 0.5 };
int Mode_of_Y[6] = { 1,1,1,1,1,1 };
void Round_line_1(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{

	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[0] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[0].z);
			Later_Center_Truck[0] = Center;
			Init_T[0] = 1;
			if (z2 > z1)
			{
				Mode_Tr[0] = 1;
			}
			else
			{
				Mode_Tr[0] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
		if (R > 200) {
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[0].z, z1, Later_Center_Truck[0].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[0] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[0].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[0].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[0].z)
				{
					Mode_Tr[0] = -1 * Mode_Tr[0];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[0].z)
				{
					Mode_Tr[0] = -1 * Mode_Tr[0];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[0].z, Later_Center_Truck[0].x,
				Center.z, Center.x,
				R, Mode_Tr[0]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[0] << endl;
			*/
			Later_Center_Truck[0] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[0] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[0] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[0] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2-x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / deltaT * Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[0] == -1) {
		omega_of_y = 0.0-omega_of_y;
	}

	if (Mode_Tr[0] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta);
	}
	Init_T[0] = 1;
	Mode_of_Y[0] *= -1;
}

void Round_line_2(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{

	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[1] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[1].z);
			Later_Center_Truck[1] = Center;
			Init_T[1] = 1;
			if (z2 > z1)
			{
				Mode_Tr[1] = 1;
			}
			else
			{
				Mode_Tr[1] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[1].z, z1, Later_Center_Truck[1].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[1] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[1].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[1].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[1].z)
				{
					Mode_Tr[1] = -1 * Mode_Tr[1];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[1].z)
				{
					Mode_Tr[1] = -1 * Mode_Tr[1];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[1].z, Later_Center_Truck[1].x,
				Center.z, Center.x,
				R, Mode_Tr[1]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[1] << endl;
			*/
			Later_Center_Truck[1] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[1] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[1] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[1] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2-x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[1] == -1) {
		omega_of_y = 0.0-omega_of_y;
	}
	if (Mode_Tr[1] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT* Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta);
	}
	Init_T[1] = 1;
	Mode_of_Y[1] *= -1;
}

void Round_line_3(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{
	

	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[2] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[2].z);
			Later_Center_Truck[2] = Center;
			Init_T[2] = 1;
			if (z2 > z1)
			{
				Mode_Tr[2] = 1;
			}
			else
			{
				Mode_Tr[2] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[2].z, z1, Later_Center_Truck[2].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[2] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[2].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[2].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[2].z)
				{
					Mode_Tr[2] = -1 * Mode_Tr[2];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[2].z)
				{
					Mode_Tr[2] = -1 * Mode_Tr[2];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[2].z, Later_Center_Truck[2].x,
				Center.z, Center.x,
				R, Mode_Tr[2]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[2] << endl;
			*/
			Later_Center_Truck[2] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[2] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[2] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[2] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2-x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[2] == -1) {
		omega_of_y = 0.0-omega_of_y;
	}
	if (Mode_Tr[2] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT* Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta);
	}
	Init_T[2] = 1;
	Mode_of_Y[2] *= -1;
}

void Round_line_4(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{
	

	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[3] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[3].z);
			Later_Center_Truck[3] = Center;
			Init_T[3] = 1;
			if (z2 > z1)
			{
				Mode_Tr[3] = 1;
			}
			else
			{
				Mode_Tr[3] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[3].z, z1, Later_Center_Truck[3].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[3] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[3].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[3].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[3].z)
				{
					Mode_Tr[3] = -1 * Mode_Tr[3];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[3].z)
				{
					Mode_Tr[3] = -1 * Mode_Tr[3];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[3].z, Later_Center_Truck[3].x,
				Center.z, Center.x,
				R, Mode_Tr[3]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[3] << endl;
			*/
			Later_Center_Truck[3] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[3] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[3] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[3] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2-x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[3] == -1) {
		omega_of_y = 0.0-omega_of_y;
	}
	if (Mode_Tr[3] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT* Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta);
	}
	Init_T[3] = 1;
	Mode_of_Y[3] *= -1;
}

void Round_line_5(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{
	

	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[4] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[4].z);
			Later_Center_Truck[4] = Center;
			Init_T[4] = 1;
			if (z2 > z1)
			{
				Mode_Tr[4] = 1;
			}
			else
			{
				Mode_Tr[4] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[4].z, z1, Later_Center_Truck[4].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[4] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[4].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[4].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[4].z)
				{
					Mode_Tr[4] = -1 * Mode_Tr[4];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[4].z)
				{
					Mode_Tr[4] = -1 * Mode_Tr[4];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[4].z, Later_Center_Truck[4].x,
				Center.z, Center.x,
				R, Mode_Tr[4]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[4] << endl;
			*/
			Later_Center_Truck[4] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[4] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[4] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[4] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2-x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[4] == -1) {
		omega_of_y = 0.0-omega_of_y;
	}
	if (Mode_Tr[4] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT* Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta);
	}
	Init_T[4] = 1;
	Mode_of_Y[4] *= -1;
}

void Round_line_6(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{
	

	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[5] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[5].z);
			Later_Center_Truck[5] = Center;
			Init_T[5] = 1;
			if (z2 > z1)
			{
				Mode_Tr[5] = 1;
			}
			else
			{
				Mode_Tr[5] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[5].z, z1, Later_Center_Truck[5].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[5] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[5].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[5].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[5].z)
				{
					Mode_Tr[5] = -1 * Mode_Tr[5];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[5].z)
				{
					Mode_Tr[5] = -1 * Mode_Tr[5];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[5].z, Later_Center_Truck[5].x,
				Center.z, Center.x,
				R, Mode_Tr[5]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[5] << endl;
			*/
			Later_Center_Truck[5] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[5] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[5] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[5] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2-x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[5] == -1) {
		omega_of_y = 0.0-omega_of_y;
	}
	if (Mode_Tr[5] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT* Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta);
	}
	Init_T[5] = 1;
	Mode_of_Y[5] *= -1;
}

void Init_Reset(int Truck_Amount) {
	for (int i = Truck_Amount-1; i <6; i++) {
		Later_Center_Truck[i] = Later_Center_Truck[i-1];
		CurretTheta_T[i] = CurretTheta_T[i - 1];
		Mode_Tr[i] = Mode_Tr[i - 1];
		Mode_of_Y[i] = Mode_of_Y[i - 1];
	}
}

void Round_Truck(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, short int Truck) {
	long double Lamta = 20;
	switch (Truck)
	{
	case 1:
		Round_line_1(x1, x2, y1, y2, z1, z2, Lamta,"test");
		break;
	case 2:
		Round_line_2(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	case 3:
		Round_line_3(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	case 4:
		Round_line_4(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	case 5:
		Round_line_5(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	case 6:
		Round_line_6(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	default:
		break;
	}
}

//离散连续相切圆
void Round_line_1_lisan(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{

	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[0] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[0].z);
			Later_Center_Truck[0] = Center;
			Init_T[0] = 1;
			if (z2 > z1)
			{
				Mode_Tr[0] = 1;
			}
			else
			{
				Mode_Tr[0] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
		if (R > 200) {
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[0].z, z1, Later_Center_Truck[0].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[0] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[0].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[0].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[0].z)
				{
					Mode_Tr[0] = -1 * Mode_Tr[0];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[0].z)
				{
					Mode_Tr[0] = -1 * Mode_Tr[0];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[0].z, Later_Center_Truck[0].x,
				Center.z, Center.x,
				R, Mode_Tr[0]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[0] << endl;
			*/
			Later_Center_Truck[0] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[0] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[0] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[0] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2 - x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / deltaT * Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[0] == -1) {
		omega_of_y = 0.0 - omega_of_y;
	}

	if (Mode_Tr[0] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT* Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta, 0.5);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta, 0.5);
	}
	Init_T[0] = 1;
	Mode_of_Y[0] *= -1;
}

void Round_line_2_lisan(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{

	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[1] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[1].z);
			Later_Center_Truck[1] = Center;
			Init_T[1] = 1;
			if (z2 > z1)
			{
				Mode_Tr[1] = 1;
			}
			else
			{
				Mode_Tr[1] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[1].z, z1, Later_Center_Truck[1].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[1] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[1].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[1].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[1].z)
				{
					Mode_Tr[1] = -1 * Mode_Tr[1];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[1].z)
				{
					Mode_Tr[1] = -1 * Mode_Tr[1];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[1].z, Later_Center_Truck[1].x,
				Center.z, Center.x,
				R, Mode_Tr[1]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[1] << endl;
			*/
			Later_Center_Truck[1] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[1] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[1] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[1] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2 - x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[1] == -1) {
		omega_of_y = 0.0 - omega_of_y;
	}
	if (Mode_Tr[1] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT* Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta, 0.5);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta, 0.5);
	}
	Init_T[1] = 1;
	Mode_of_Y[1] *= -1;
}

void Round_line_3_lisan(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{


	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[2] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[2].z);
			Later_Center_Truck[2] = Center;
			Init_T[2] = 1;
			if (z2 > z1)
			{
				Mode_Tr[2] = 1;
			}
			else
			{
				Mode_Tr[2] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[2].z, z1, Later_Center_Truck[2].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[2] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[2].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[2].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[2].z)
				{
					Mode_Tr[2] = -1 * Mode_Tr[2];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[2].z)
				{
					Mode_Tr[2] = -1 * Mode_Tr[2];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[2].z, Later_Center_Truck[2].x,
				Center.z, Center.x,
				R, Mode_Tr[2]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[2] << endl;
			*/
			Later_Center_Truck[2] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[2] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[2] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[2] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2 - x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[2] == -1) {
		omega_of_y = 0.0 - omega_of_y;
	}
	if (Mode_Tr[2] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT* Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta, 0.5);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta, 0.5);
	}
	Init_T[2] = 1;
	Mode_of_Y[2] *= -1;
}

void Round_line_4_lisan(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{


	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[3] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[3].z);
			Later_Center_Truck[3] = Center;
			Init_T[3] = 1;
			if (z2 > z1)
			{
				Mode_Tr[3] = 1;
			}
			else
			{
				Mode_Tr[3] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[3].z, z1, Later_Center_Truck[3].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[3] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[3].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[3].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[3].z)
				{
					Mode_Tr[3] = -1 * Mode_Tr[3];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[3].z)
				{
					Mode_Tr[3] = -1 * Mode_Tr[3];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[3].z, Later_Center_Truck[3].x,
				Center.z, Center.x,
				R, Mode_Tr[3]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[3] << endl;
			*/
			Later_Center_Truck[3] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[3] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[3] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[3] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2 - x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[3] == -1) {
		omega_of_y = 0.0 - omega_of_y;
	}
	if (Mode_Tr[3] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT* Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta, 0.5);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta, 0.5);
	}
	Init_T[3] = 1;
	Mode_of_Y[3] *= -1;
}

void Round_line_5_lisan(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{


	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[4] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[4].z);
			Later_Center_Truck[4] = Center;
			Init_T[4] = 1;
			if (z2 > z1)
			{
				Mode_Tr[4] = 1;
			}
			else
			{
				Mode_Tr[4] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[4].z, z1, Later_Center_Truck[4].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[4] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[4].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[4].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[4].z)
				{
					Mode_Tr[4] = -1 * Mode_Tr[4];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[4].z)
				{
					Mode_Tr[4] = -1 * Mode_Tr[4];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[4].z, Later_Center_Truck[4].x,
				Center.z, Center.x,
				R, Mode_Tr[4]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[4] << endl;
			*/
			Later_Center_Truck[4] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[4] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[4] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[4] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2 - x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[4] == -1) {
		omega_of_y = 0.0 - omega_of_y;
	}
	if (Mode_Tr[4] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT* Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT* Lamta, deltaT* Lamta, deltaT* Lamta, (int)Lamta, 0.5);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta, 0.5);
	}
	Init_T[4] = 1;
	Mode_of_Y[4] *= -1;
}

void Round_line_6_lisan(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD)
{


	long double R;
	Point Center;
	Line L1;
	Line L2;
	Line L3;
	if (Init_T[5] == 0)
	{

		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		L3.k = 0;
		L3.b = x1;
		if (L2.k >= -0.000001 && L2.k <= 0.000001)
		{
			parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[5].z);
			Later_Center_Truck[5] = Center;
			Init_T[5] = 1;
			if (z2 > z1)
			{
				Mode_Tr[5] = 1;
			}
			else
			{
				Mode_Tr[5] = -1;
			}
		}
		long double R1 = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
		long double R2 = sqrt(((Center.x - x2) * (Center.x - x2)) + (((Center.z - z2) * (Center.z - z2))));
		R = (R1 + R2) * 0.5;
	}
	else
	{
		GetLine(z1, z2, x1, x2, L1);
		GetMidLine(L1, L2, z1, z2, x1, x2);
		GetLine(Later_Center_Truck[5].z, z1, Later_Center_Truck[5].x, x1, L3);
		long double test_line = L3.k - L2.k;
		if (test_line <= 0.000001 && test_line >= 0.000001)
		{
			round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
			Init_T[5] = 0;
			return;
		}
		else
		{
			GetCross(L3, L2, Center, Later_Center_Truck[5].z);

			R = sqrt(((Center.x - x1) * (Center.x - x1)) + (((Center.z - z1) * (Center.z - z1))));
			if (Center.z >= Later_Center_Truck[5].z)
			{
				if (z1 <= Center.z && z1 >= Later_Center_Truck[5].z)
				{
					Mode_Tr[5] = -1 * Mode_Tr[5];
				}
			}
			else
			{
				if (z1 >= Center.z && z1 <= Later_Center_Truck[5].z)
				{
					Mode_Tr[5] = -1 * Mode_Tr[5];
				}
			}
			printf(
				"上一次圆心：%Lf %Lf\n"
				"圆心：%Lf %Lf\n"
				"R=%Lf\n模式：%d\n",
				Later_Center_Truck[5].z, Later_Center_Truck[5].x,
				Center.z, Center.x,
				R, Mode_Tr[5]
			);
			/*
			cout << "上一次圆心：" << Later_Center.z << " " << Later_Center.x << endl;
			cout << "圆心：" << Center.z << " " << Center.x << endl;
			cout << "R=" << R << endl;
			cout << "模式：" << Mode_Tr[5] << endl;
			*/
			Later_Center_Truck[5] = Center;
			if (R > 200) {
				round_parabola_line(x1, x2, y1, y2, z1, z2, Lamta, ABCD);
				return;
			}
		}
	}
	long double C = 2 * pi * R;
	long double deltaT = abs(x2 - x1);
	Lamta = (long double)((int)((C * 5 / deltaT)));
	if (Lamta < 40) {
		Lamta = 40;
	}


	long double S = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));
	printf("两点间距离：%Lf\n", S);
	//cout << "两点间距离：" << S << endl;
	long double Theta = acos(S / (2 * R));
	printf("Theta：%Lf\n", Theta);
	//cout << "Theta：" << Theta << endl;
	long double Phi = pi - (2 * Theta);
	printf("Phi：%Lf\n", Phi);
	//cout << "Phi：" << Phi << endl;
	long double TTT = ((Center.x - L1.b) / L1.k);
	long double Omega = 0.0;
	if (Mode_Tr[5] == 1)
	{
		if (TTT <= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}
	if (Mode_Tr[5] == -1)
	{
		if (TTT >= Center.z)
		{
			Omega = Phi / (deltaT * Lamta);
		}
		else
		{
			Omega = ((2 * pi) - Phi) / (deltaT * Lamta);
		}
	}


	long double Omega_0;
	if (Init_T[5] != 0) {
		Omega_0 = atan(L3.k);
		if (z1 < Center.z) {
			Omega_0 = Omega_0 + pi;
		}
	}
	else {
		if (z1 < Center.z) {
			Omega_0 = pi;
		}
		else {
			Omega_0 = 0;
		}
	}
	long double R_of_Y = (x2 - x1) / 2.0;
	long double omega_of_y = pi / (deltaT * Lamta);
	double XXX = 1 / Lamta;
	int deltaT2 = (int)x1;//转换为整形
	if (Mode_of_Y[5] == -1) {
		omega_of_y = 0.0 - omega_of_y;
	}
	if (Mode_Tr[5] == -1) {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f + %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f + %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta, 0.5);
	}
	else {
		fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10Lf %.10Lf %.10Lf 0 0 0 0 %.10Lf \"x, y, z, cr, cg, cb = %.10f * sin(%.10f - %.10f * t)+0.5, %.10f*sin(t*%.10f), %.10f * cos(%.10f - %.10f * t)+0.5, cos(2*PI*t/(%.10f)) / 4 + 0.75, cos(2*PI*t/(%.10f)) / 4 + 0.75, sin(2*PI*t/(%.10f)) / 4 + 0.75\" 1 %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" %.10Lf\n", deltaT2, Center.x, y1 + 0.5, Center.z, deltaT * Lamta, R, Omega_0, Omega, R_of_Y, omega_of_y, R, Omega_0, Omega, deltaT * Lamta, deltaT * Lamta, deltaT * Lamta, (int)Lamta, 0.5);
	}
	Init_T[5] = 1;
	Mode_of_Y[5] *= -1;
}

void Round_Truck_lisan(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, short int Truck) {
	long double Lamta = 20;
	switch (Truck)
	{
	case 1:
		Round_line_1_lisan(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	case 2:
		Round_line_2_lisan(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	case 3:
		Round_line_3_lisan(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	case 4:
		Round_line_4_lisan(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	case 5:
		Round_line_5_lisan(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	case 6:
		Round_line_6_lisan(x1, x2, y1, y2, z1, z2, Lamta, "test");
		break;
	default:
		break;
	}
}

void BFLLLLLLLLL(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, short int Truck) {
	D_SmallFlower_Flash(x2, y2, z2);
}

void spiral_lines_lisan(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	//求平均速度（直线移动速度）
	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double vy = ((y2 - y1) / deltaT);//参数方程（Y轴）
	long double s = sqrt(((x2 - x1) * (x2 - x1)) + ((z2 - z1) * (z2 - z1)));//路程
	long double h = y2 - y1;//高度
	long double theta = atan((x2 - x1) / (z2 - z1));//水平偏转角
	long double phi = atan(h / s);//竖直偏转角
	long double omega = 4 * deltaT * pi / (Lamta * s);//转速
	long double AAA = s / 6;
	long double omega2 = pi / (Lamta * s);//转速
	int x_1 = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(s / deltaT)) * 20.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量
	long double r_r = 4;
	//螺线最大半径

	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = 0+(%.10f * t - (%.10f*sin(t*%.10f)^2 * ((cos(%.10f) * cos(%.10f * t)) + (sin(%.10f) * sin(%.10f) * sin(%.10f * t)))) + 0.5), %.10f * t + (%.10f*sin(t*%.10f) * (cos(%.10f) * sin(%.10f * t))) + 0.5, %.10f * t + (%.10f*sin(t*%.10f)^2 * ((sin(%.10f) * cos(%.10f * t)) - (cos(%.10f) * sin(%.10f) * sin(%.10f * t)))) + 0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" 0.5\n", x_1, x1, y1, z1, deltaT2, vx, r_r, pi / deltaT, theta, omega, theta, phi, omega, vy, r_r, pi / deltaT, phi, omega, vz, r_r, pi / deltaT, theta, omega, theta, phi, omega, NumBC_, (int)NumBC);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = 0+(%.10f * t - (%.10f*sin(t*%.10f)^2 * ((cos(%.10f) * cos(%.10f * t + (3.1415926535))) + (sin(%.10f) * sin(%.10f) * sin(%.10f * t+ (3.1415926535))))) + 0.5), %.10f * t + (%.10f*sin(t*%.10f)^2 * (cos(%.10f) * sin(%.10f * t+ (3.1415926535)))) + 0.5, %.10f * t + (%.10f*sin(t*%.10f)^2 * ((sin(%.10f) * cos(%.10f * t+ (3.1415926535))) - (cos(%.10f) * sin(%.10f) * sin(%.10f * t+ (3.1415926535))))) + 0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" 0.5\n", x_1, x1, y1, z1, deltaT2, vx, r_r, pi / deltaT, theta, omega, theta, phi, omega, vy, r_r, pi / deltaT, phi, omega, vz, r_r, pi / deltaT, theta, omega, theta, phi, omega, NumBC_, (int)NumBC);

}

void parabola_line_lisan(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {

	long double deltaT = abs(x2 - x1);//求时间间隔（Tick）
	int deltaT2 = (int)abs(x2 - x1);//转换为整形
	long double vz = ((z2 - z1) / deltaT);//参数方程（Z轴）
	long double vx = ((x2 - x1) / deltaT);//参数方程（X为参数）
	long double s = sqrt(s_qrt((x2 - x1)) + s_qrt((z2 - z1)));//求位移
	int x = (int)x1;//起始时间
	int x_2 = (int)x2;//终止时间
	long double NumBC = (long double)((int)(s / deltaT)) * 20.0; //每一刻计算的次数
	long double NumBC_ = 1.0000000 / NumBC;//每次计算的参数递增量


	if (abs(z2 - z1) >= deltaT) {
		Lamta = (long double)((int)(5 * (abs(z2 - z1) / deltaT)));
	}
	double H;//抛物线最高点
	double deltaY = y2 - y1;//Y轴相对坐标
	double deltaX = x2 - x1;//X轴相对坐标

	if (y2 > y1) {
		H = 0.2 * s + deltaY;//高度的定义
	}
	else {
		H = 0.2 * s;//高度的定义
	}

	double a;//y=bx(x-a)
	double b;//y=bx(x-a)
	if (deltaY != 0) {
		a = ((4 * H * deltaX) + sqrt((16 * H * H * deltaX * deltaX) - 16 * H * deltaY * deltaX * deltaX)) / (2 * deltaY);
		if (a / 2 < 0 || a / 2 > x2) {
			a = ((4 * H * deltaX) - sqrt((16 * H * H * deltaX * deltaX) - 16 * H * deltaY * deltaX * deltaX)) / (2 * deltaY);
		}
		b = (-4 * H) / (a * a);
	}
	else if (deltaY == 0) {
		a = deltaX;
		b = (-4 * H) / (a * a);
	}//求y轴参数方程

	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 %d \"x, y, z, cr, cg, cb = t+0.5, (%.10f*t*(t-%.10f))+0.5, %.10f*t+0.5, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" %.10f %d 25 \"(vx, vz) = ((random(), random()) - 0.5) * t / 10\" 0.5\n", x, x1, y1, z1, deltaT2, b, a, vz, NumBC_, (int)NumBC);
}





//上抛物线(带圆圈）
void round_parabola_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	parabola_line(x1, x2, y1, y2, z1, z2, 10, "test");
	print_round(x2, y2, z2);
}

//下抛物线(带圆圈）
void round_parabola_line_r(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	parabola_line_r(x1, x2, y1 - 20, y2 - 20, z1, z2, 10, "test");
	print_round(x2, y2, z2);
}



























































































//上下抛物线中心螺线链接(带圆圈）
void round_special_parabola_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	round_parabola_line(x1, x2, y1, y2, z1, z2, 10, "test");
	round_parabola_line_r(x1, x2, y1 - 20, y2 - 20, z1, z2, 10, "test");
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"x, y, z, cr, cg, cb = cos(t * (8 * PI / 10)), t, sin(t * (8 * PI / 10)), sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 - 20 + 0.5, z2 + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"x, y, z, cr, cg, cb = cos(t * (8 * PI / 10)), 0-t, sin(t * (8 * PI / 10)), sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 + 0.5, z2 + 0.5);
}

//上下抛物线中心螺线链接
void special_parabola_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	parabola_line(x1, x2, y1, y2, z1, z2, 10, "test");
	parabola_line_r(x1, x2, y1-20, y2-20, z1, z2, 10, "test");
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"x, y, z, cr, cg, cb = cos(t * (8 * PI / 10)), t, sin(t * (8 * PI / 10)), sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2+0.5, y2 - 20 + 0.5, z2 + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"x, y, z, cr, cg, cb = cos(t * (8 * PI / 10)), 0-t, sin(t * (8 * PI / 10)), sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 + 0.5, z2 + 0.5);
}

//上下抛物线中心螺线链接（有螺旋圈阵）
void special_parabola_line_round(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	spiral_round_parabola_line(x1, x2, y1, y2, z1, z2, 10, "test");
	spiral_round_parabola_line_r(x1, x2, y1 - 20, y2 - 20, z1, z2, 10, "test");
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"x, y, z, cr, cg, cb = cos(t * (8 * PI / 10)), t, sin(t * (8 * PI / 10)), sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 - 20 + 0.5, z2 + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"x, y, z, cr, cg, cb = cos(t * (8 * PI / 10)), 0-t, sin(t * (8 * PI / 10)), sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 + 0.5, z2 + 0.5);
}

//上下直线中心螺线链接
void special_straight_line(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	straight_line(x1, x2, y1, y2, z1, z2, 10, "test");
	straight_line(x1, x2, y1 - 20, y2 - 20, z1, z2, 10, "test");
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"x, y, z, cr, cg, cb = cos(t * (8 * PI / 10)), t, sin(t * (8 * PI / 10)), sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 - 20 + 0.5, z2 + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"x, y, z, cr, cg, cb = cos(t * (8 * PI / 10)), 0-t, sin(t * (8 * PI / 10)), sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 + 0.5, z2 + 0.5);
}

//上下抛物线中心直线链接
void special_parabola_line_s(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	parabola_line(x1, x2, y1, y2, z1, z2, 10, "test");
	parabola_line_r(x1, x2, y1 - 20, y2 - 20, z1, z2, 10, "test");
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"y, cr, cg, cb = t, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 - 20 + 0.5, z2 + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"y, cr, cg, cb = 0-t, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 + 0.5, z2 + 0.5);
}

//上下抛物线中心直线链接（有螺旋圈阵）
void special_parabola_line_s_round(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	spiral_round_parabola_line(x1, x2, y1, y2, z1, z2, 10, "test");
	spiral_round_parabola_line_r(x1, x2, y1 - 20, y2 - 20, z1, z2, 10, "test");
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"y, cr, cg, cb = t, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 - 20 + 0.5, z2 + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"y, cr, cg, cb = 0-t, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 + 0.5, z2 + 0.5);
}

//上下直线中心直线链接
void special_straight_line_s(long double x1, long double x2, long double y1, long double y2, long double z1, long double z2, long double Lamta, string ABCD) {
	straight_line(x1, x2, y1, y2, z1, z2, 10, "test");
	straight_line(x1, x2, y1 - 20, y2 - 20, z1, z2, 10, "test");
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"y, cr, cg, cb = t, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 - 20 + 0.5, z2 + 0.5);
	fprintf(file1, "execute if score @p Timer matches %d run particleex rgbatickparameter minecraft:end_rod %.10f %.10f %.10f 0 0 0 0 10 \"y, cr, cg, cb = 0-t, sin(t/7)/2+0.5, cos(t/5)/2+0.5, sin(t/3)/2+0.5\" 0.1 20 25\n", int(x2), x2 + 0.5, y2 + 0.5, z2 + 0.5);
}















#endif