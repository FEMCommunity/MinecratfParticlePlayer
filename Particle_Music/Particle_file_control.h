
#pragma warning(disable : 4996)
#ifndef FILE_CONTROL_PARTICLE
#define FILE_CONTROL_PARTICLE
#include "D:\VisualStudioProj\MC���\Particle_Music\Particle.h"

//�ļ���ʽ��ÿһ�зֱ�Ϊ����ʼʱ��	��ˮƽ�Ʊ���� ����


FILE* PARTICLEFILECONTROL = nullptr;
char PARTICLEFILELOCATE[255] = "Input.txt";
vector<vector<int>> MIDI_INFO_PARTICLE;

void open_file() {
	PARTICLEFILECONTROL = fopen(PARTICLEFILELOCATE, "a+");
}

void load_txt_file(){
	int TEMP_NOTE[2];
	for (int i=0; fscanf(PARTICLEFILECONTROL, "%d %d", TEMP_NOTE, TEMP_NOTE + 1)!=EOF;) {
		if (MIDI_INFO_PARTICLE.size() == 0) {
			vector<int> TEM_NOTE;
			TEM_NOTE.push_back(*TEMP_NOTE);
			TEM_NOTE.push_back(*(TEMP_NOTE + 1));
			MIDI_INFO_PARTICLE.push_back(TEM_NOTE);
		}
		else {
			if (*TEMP_NOTE == MIDI_INFO_PARTICLE[i][0]) {
				MIDI_INFO_PARTICLE[i].push_back(*(TEMP_NOTE + 1));
			}
			else {
				i++;
				vector<int> TEM_NOTE;
				TEM_NOTE.push_back(*TEMP_NOTE);
				TEM_NOTE.push_back(*(TEMP_NOTE + 1));
				MIDI_INFO_PARTICLE.push_back(TEM_NOTE);
			}
		}
	}
}

void print_txt_file() {
	for (int i = 0; i < (int)MIDI_INFO_PARTICLE.size(); i++) {
		for (int j = 0; j < (int)MIDI_INFO_PARTICLE[i].size(); j++) {
			printf("%d    ", MIDI_INFO_PARTICLE[i][j]);
		}
		printf("\n");
	}
}

#endif