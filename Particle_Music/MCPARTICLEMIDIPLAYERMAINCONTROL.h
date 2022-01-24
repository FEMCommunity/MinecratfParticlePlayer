#ifndef MCPARTICLEMIDIPLAYERMAINCONTROL_
#define MCPARTICLEMIDIPLAYERMAINCONTROL_
#pragma warning(disable : 4996)
#include "D:\VisualStudioProj\MC���\Particle_Music\Particle_file_control.h"
int StartPos[2];
int TempYPos = 80;
char ParMode = 'a';
int Tem_SCANF;
void Tran_MODEA() {//A
	printf("\n\n\n\n������һ�е�������꣨x z����\n");
	Tem_SCANF = Tem_SCANF = scanf("%d %d", StartPos, StartPos+1);

	for (int i = 0; i < (int)MIDI_INFO_PARTICLE.size(); i++) {
		for (int j = 1; j < (int)MIDI_INFO_PARTICLE[i].size(); j++) {
			if (i == 0) {
				straight_line(*StartPos, MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, *(StartPos + 1), MIDI_INFO_PARTICLE[i][j], 20, "Tem");//���˺���������һ��else�к�������ΪParticle.h�е��κ�һ���������������з���������Բ�ĺ����ɸı���������
			}
			else {
				straight_line(MIDI_INFO_PARTICLE[i-1][0], MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, MIDI_INFO_PARTICLE[i-1][1], MIDI_INFO_PARTICLE[i][j], 20, "Tem");
			}
		}
	}
	printf("ת������\n");
	return;
}

void Tran_MODEB() {//B
	printf("\n\n\n\n������һ�е�������꣨x z����\n");
	Tem_SCANF = Tem_SCANF = scanf("%d %d", StartPos, StartPos + 1);

	for (int i = 0; i < (int)MIDI_INFO_PARTICLE.size(); i++) {
		for (int j = 1; j < (int)MIDI_INFO_PARTICLE[i].size(); j++) {
			if (i == 0) {
				straight_line(*StartPos, MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, *(StartPos + 1), MIDI_INFO_PARTICLE[i][j], 20, "Tem");//���˺���������һ��else�к�������ΪParticle.h�е��κ�һ���������������з���������Բ�ĺ����ɸı���������
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
	printf("ת������\n");
	return;
}

void Tran_MODEC() {//C
	printf("\n\n\n\n������һ�е�������꣨x z����\n");
	Tem_SCANF = Tem_SCANF = scanf("%d %d", StartPos, StartPos + 1);

	for (int i = 0; i < (int)MIDI_INFO_PARTICLE.size(); i++) {
		for (int j = 1; j < (int)MIDI_INFO_PARTICLE[i].size(); j++) {
			if (i == 0) {
				straight_line(*StartPos, MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, *(StartPos + 1), MIDI_INFO_PARTICLE[i][j], 20, "Tem");//���˺���������һ��else�к�������ΪParticle.h�е��κ�һ���������������з���������Բ�ĺ����ɸı���������
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
	printf("ת������\n");
	return;
}

void Tran_MODED() {//D
	printf("\n\n\n\n������һ�е�������꣨x z����\n");
	Tem_SCANF = Tem_SCANF = scanf("%d %d", StartPos, StartPos + 1);

	for (int i = 0; i < (int)MIDI_INFO_PARTICLE.size(); i++) {
		for (int j = 1; j < (int)MIDI_INFO_PARTICLE[i].size(); j++) {
			if (i == 0) {
				straight_line(*StartPos, MIDI_INFO_PARTICLE[i][0], TempYPos, TempYPos, *(StartPos + 1), MIDI_INFO_PARTICLE[i][j], 20, "Tem");//���˺���������һ��else�к�������ΪParticle.h�е��κ�һ���������������з���������Բ�ĺ����ɸı���������
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
	printf("ת������\n");
	return;
}

void StartProject() {
	file1 = fopen("Temp.mcfunction", "a+");//�޸��ļ���
	open_file();
	load_txt_file();
	printf("ÿһ�м�ΪͬһT��������\n");
	print_txt_file();
	PARTICLE_ERROR0_:
	printf("\n\n\n\n\n������y���꣨>0)��y = ");
	Tem_SCANF = scanf("%d", &TempYPos);
	if (TempYPos <= 0) {
		printf("�����ʽ����");
		goto PARTICLE_ERROR0_;
	}
	else {
		PARTICLE_ERROR1_:
		printf("\n\n\n\n\n������ģʽ��ABCD����\nģʽA��ÿһ�η�֧�����������ۺϣ���ÿһ�η�֧�����Ϊ����ĵ�һ�����������꣩\nģʽB��ÿһ�η�֧�����������ۺϣ���ÿһ�η�֧�����Ϊ���������ͬ��������������������Ŀ������һ�У��������ִӶ�������һ����ʼ��\nģʽC��ÿһ�η�֧����������ۺϣ��ۺϵ����ĵ�һ�����������꣩\nģʽD��ÿһ�η�֧����������ۺϣ��ۺϵ����������Bģʽ��\nģʽ = ");
		Tem_SCANF = scanf("%c", &ParMode);//���ڻ�������������һ������ĵĻس�����
		Tem_SCANF = scanf("%c", &ParMode);
		switch (ParMode) {
		case 'A': Tran_MODEA(); break;
		case 'B': Tran_MODEB(); break;
		case 'C': Tran_MODEC(); break;
		case 'D': Tran_MODED(); break;
		default: printf("�����������дA B C D�е�һ��\n"); goto PARTICLE_ERROR1_; break;
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
	printf("ת������\n");
	return;
}

void StartRound() {
	file1 = fopen("Temp.mcfunction", "a+");//�޸��ļ���
	open_file();
	load_txt_file();
	printf("ÿһ�м�ΪͬһT��������\n");
	print_txt_file();
PARTICLE_ERROR0_:
	printf("\n\n\n\n\n������y���꣨>0)��y = ");
	Tem_SCANF = scanf("%d", &TempYPos);
	if (TempYPos <= 0) {
		printf("�����ʽ����");
		goto PARTICLE_ERROR0_;
	}
	else {
		Tran_MODEROUND();
	}
	return;
}
































#endif // !MCPARTICLEMIDIPLAYERMAINCONTROL_
