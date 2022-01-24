#ifndef MCPARTICLEMIDIPLAYERMAINCONTROL_
#define MCPARTICLEMIDIPLAYERMAINCONTROL_
#pragma warning(disable : 4996)
#include "D:\VisualStudioProj\MC相关\Particle_Music\Particle_file_control.h"
int StartPos[2];
int TempYPos = 80;
char ParMode = 'a';
int Tem_SCANF;
void Tran_MODEA() {//A
	printf("\n\n\n\n请输入一切的起点坐标（x z）：\n");
	Tem_SCANF = Tem_SCANF = scanf("%d %d", StartPos, StartPos+1);

	for (int i = 0; i < (int)MIDI_INFO_PARTICLE.size(); i++) {
		for (int j = 1; j < (int)MIDI_INFO_PARTICLE[i].size(); j++) {
			if (i == 0) {
				straight_line(*StartPos, MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, *(StartPos + 1), MIDI_INFO_PARTICLE[i][j], 20, "Tem");//将此函数名与下一个else中函数名改为Particle.h中的任何一个绘制线条分组中非连续相切圆的函数可改变线条类型
			}
			else {
				straight_line(MIDI_INFO_PARTICLE[i-1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i-1][1], MIDI_INFO_PARTICLE[i][j], 20, "Tem");
			}
		}
	}
	printf("转换结束\n");
	return;
}

void Tran_MODEB() {//B
	printf("\n\n\n\n请输入一切的起点坐标（x z）：\n");
	Tem_SCANF = Tem_SCANF = scanf("%d %d", StartPos, StartPos + 1);

	for (int i = 0; i < (int)MIDI_INFO_PARTICLE.size(); i++) {
		for (int j = 1; j < (int)MIDI_INFO_PARTICLE[i].size(); j++) {
			if (i == 0) {
				straight_line(*StartPos, MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, *(StartPos + 1), MIDI_INFO_PARTICLE[i][j], 20, "Tem");//将此函数名与下一个else中函数名改为Particle.h中的任何一个绘制线条分组中非连续相切圆的函数可改变线条类型
			}
			else {
				if (i > (int)MIDI_INFO_PARTICLE[i - 1].size()) {
					straight_line(MIDI_INFO_PARTICLE[i - 1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i - 1][(int)MIDI_INFO_PARTICLE[i - 1].size()-1], MIDI_INFO_PARTICLE[i][j], 20, "Tem");
				}
				else {
					straight_line(MIDI_INFO_PARTICLE[i - 1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i - 1][j], MIDI_INFO_PARTICLE[i][j], 20, "Tem");
				}
				
			}
		}
	}
	printf("转换结束\n");
	return;
}

void Tran_MODEC() {//C
	printf("\n\n\n\n请输入一切的起点坐标（x z）：\n");
	Tem_SCANF = Tem_SCANF = scanf("%d %d", StartPos, StartPos + 1);

	for (int i = 0; i < (int)MIDI_INFO_PARTICLE.size(); i++) {
		for (int j = 1; j < (int)MIDI_INFO_PARTICLE[i].size(); j++) {
			if (i == 0) {
				straight_line(*StartPos, MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, *(StartPos + 1), MIDI_INFO_PARTICLE[i][j], 20, "Tem");//将此函数名与下一个else中函数名改为Particle.h中的任何一个绘制线条分组中非连续相切圆的函数可改变线条类型
			}
			else {
				straight_line(MIDI_INFO_PARTICLE[i - 1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i - 1][1], MIDI_INFO_PARTICLE[i][j], 20, "Tem");
			}
		}
		if ((int)MIDI_INFO_PARTICLE[i - 1].size() > (int)MIDI_INFO_PARTICLE[i].size()) {
			for (int j = (int)MIDI_INFO_PARTICLE[i].size() - 1; j < (int)MIDI_INFO_PARTICLE[i - 1].size(); j++) {
				straight_line(MIDI_INFO_PARTICLE[i - 1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i - 1][j], MIDI_INFO_PARTICLE[i][1], 20, "Tem");
			}
		}
	}
	printf("转换结束\n");
	return;
}

void Tran_MODED() {//D
	printf("\n\n\n\n请输入一切的起点坐标（x z）：\n");
	Tem_SCANF = Tem_SCANF = scanf("%d %d", StartPos, StartPos + 1);

	for (int i = 0; i < (int)MIDI_INFO_PARTICLE.size(); i++) {
		for (int j = 1; j < (int)MIDI_INFO_PARTICLE[i].size(); j++) {
			if (i == 0) {
				straight_line(*StartPos, MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, *(StartPos + 1), MIDI_INFO_PARTICLE[i][j], 20, "Tem");//将此函数名与下一个else中函数名改为Particle.h中的任何一个绘制线条分组中非连续相切圆的函数可改变线条类型
			}
			else {
				if (i > (int)MIDI_INFO_PARTICLE[i - 1].size()) {
					straight_line(MIDI_INFO_PARTICLE[i - 1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i - 1][(int)MIDI_INFO_PARTICLE[i - 1].size() - 1], MIDI_INFO_PARTICLE[i][j], 20, "Tem");
				}
				else {
					straight_line(MIDI_INFO_PARTICLE[i - 1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i - 1][j], MIDI_INFO_PARTICLE[i][j], 20, "Tem");
				}
			}
		}
		if ((int)MIDI_INFO_PARTICLE[i - 1].size() > (int)MIDI_INFO_PARTICLE[i].size()) {
			for (int j = (int)MIDI_INFO_PARTICLE[i].size() - 1; j < (int)MIDI_INFO_PARTICLE[i - 1].size(); j++) {
				straight_line(MIDI_INFO_PARTICLE[i - 1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i - 1][j], MIDI_INFO_PARTICLE[i][(int)MIDI_INFO_PARTICLE[i].size() - 1], 20, "Tem");
			}
		}
	}
	printf("转换结束\n");
	return;
}

void StartProject() {
	file1 = fopen("Temp.mcfunction", "a+");//修改文件名
	open_file();
	load_txt_file();
	printf("每一行即为同一T的音符：\n");
	print_txt_file();
	PARTICLE_ERROR0_:
	printf("\n\n\n\n\n请输入y坐标（>0)：y = ");
	Tem_SCANF = scanf("%d", &TempYPos);
	if (TempYPos <= 0) {
		printf("输入格式错误");
		goto PARTICLE_ERROR0_;
	}
	else {
		PARTICLE_ERROR1_:
		printf("\n\n\n\n\n请输入模式（ABCD）：\n模式A（每一次分支出的线条不聚合，且每一次分支的起点为读入的第一个音符的坐标）\n模式B（每一次分支出的线条不聚合，且每一次分支的起点为读入次序相同的音符，若本行音符数目大于上一行，则多出部分从读入的最后一个起始）\n模式C（每一次分支出的线条会聚合，聚合点读入的第一个音符的坐标）\n模式D（每一次分支出的线条会聚合，聚合点规则类似于B模式）\n模式 = ");
		Tem_SCANF = scanf("%c", &ParMode);//用于回收输入流中上一次输入的的回车符号
		Tem_SCANF = scanf("%c", &ParMode);
		switch (ParMode) {
		case 'A': Tran_MODEA(); break;
		case 'B': Tran_MODEB(); break;
		case 'C': Tran_MODEC(); break;
		case 'D': Tran_MODED(); break;
		default: printf("错误，请输入大写A B C D中的一个\n"); goto PARTICLE_ERROR1_; break;
		}
	}
	return;
}

void Tran_MODEROUND() {//ROUND
	for (int i = 1; i < (int)MIDI_INFO_PARTICLE.size(); i++) {
		if ((int)MIDI_INFO_PARTICLE[i].size() > (int)MIDI_INFO_PARTICLE[i - 1].size()) {
			Init_Reset((int)MIDI_INFO_PARTICLE[i - 1].size());
		}
		for (int j = 1; j < (int)MIDI_INFO_PARTICLE[i].size(); j++) {
			if (j < (int)MIDI_INFO_PARTICLE[i - 1].size()) {
				Round_Truck_lisan(MIDI_INFO_PARTICLE[i - 1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i - 1][j], MIDI_INFO_PARTICLE[i][j], j);
			}
			else {
				Round_Truck_lisan(MIDI_INFO_PARTICLE[i - 1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i - 1][(int)MIDI_INFO_PARTICLE[i - 1].size()-1], MIDI_INFO_PARTICLE[i][j], j);
			}
		}
	}
	printf("转换结束\n");
	return;
}

void StartRound() {
	file1 = fopen("Temp.mcfunction", "a+");//修改文件名
	open_file();
	load_txt_file();
	printf("每一行即为同一T的音符：\n");
	print_txt_file();
PARTICLE_ERROR0_:
	printf("\n\n\n\n\n请输入y坐标（>0)：y = ");
	Tem_SCANF = scanf("%d", &TempYPos);
	if (TempYPos <= 0) {
		printf("输入格式错误");
		goto PARTICLE_ERROR0_;
	}
	else {
		Tran_MODEROUND();
	}
	return;
}
































#endif // !MCPARTICLEMIDIPLAYERMAINCONTROL_
