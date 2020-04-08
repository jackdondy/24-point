#include<stdio.h>
#include<stdlib.h>
#include<random>
#include<time.h>
#include<conio.h>
#include<windows.h>

#include"head.h"
#include"index.h"

//#define DEBUG

int index_number;
int temp[4];   //��ʾ��ʱ���ĸ���
int rank[4], count;

bool isUsed[4];

//����count(0~23)�õ�һ������,floor��ʾ��ǰ����0~3
void Mix(int floor){
	if(4 == floor)  {
		count--;
		return ;
	}
	if(0 == floor){
		isUsed[3] = isUsed[2] = isUsed[1] = isUsed[0] = false;
	}
	for(int i = 0 ; i < 4 ; i++){
		if(isUsed[i])  continue;
		rank[floor] = i;
		isUsed[i] = true;
		Mix(floor + 1);
		isUsed[i] = false;
		if(count == -1) return ;
	}
}

//��ȡindex[number]����Ŀ
void getQ(){
	//���������(0 ~ 23)
	long long lt = time(NULL);
	srand((lt) ^ (clock()));	//time����long long,clock����long
	count = rand() % 24;
	
	//�����������
	Mix(0);
	
	//��ȡ�����������ĸ�����
	for(int i = 0 ; i < 4 ; i++){
		temp[i] = allSample[index[index_number][0]].atom[rank[i]];
	}
}

typedef enum {
	Low, Medium, High
}Level;
Level t_level = Low;
int t_level_begin = low_level_begin;
int t_level_total = low_level_total;

//������������ȼ��� +- : 1 , */ : 2
int priority(unsigned char ope){
	switch (ope){
		default:
			return 0;
		case '*':
		case '/':
			return 2;
		case '-':
		case '+':
			return 1;
	}
	return 0;
}

void PrintQ(){
	system("cls");
	printf("\n��Level��\t");
	printf((t_level == Low) ? "��Low��" : "  Low  ");
	printf("\t\t");
	printf((t_level == Medium) ? "��Medium��" : "  Medium  ");
	printf("\t\t");
	printf((t_level == High) ? "��High��" : "  High  ");
	printf("\n\n\t\t��%5d ��\t\t��%5d ��\n��Problem��\n\t\t��%5d ��\t\t��%5d ��\n",
		temp[0], temp[1], temp[2], temp[3]);

}

void PrintA(){
	PrintQ();
	
	bool innerB, outerB;
	
	printf("\n��Answer��");
	//��ȡ�����
	for(int i = index[index_number][0] ;
		i < index[index_number][0] + index[index_number][1]; i++){
		printf("\n\t\t");
		switch (allSample[i].mode){
			case UpDown:
				innerB = true, outerB = true;

				if(priority(allSample[i].ope[0]) <= priority(allSample[i].ope[1]))
					innerB = false;
				if(priority(allSample[i].ope[0]) >= priority(allSample[i].ope[2]))
					outerB = false;
					
				printf((innerB ?
					(outerB ? "[%d %c (%d %c %d)] %c %d = 24" : "%d %c (%d %c %d) %c %d = 24") :
					(outerB ? "(%d %c %d %c %d) %c %d = 24" : "%d %c %d %c %d %c %d = 24")),
					allSample[i].atom[0],
					allSample[i].ope[0], allSample[i].atom[1],
					allSample[i].ope[1], allSample[i].atom[2],
					allSample[i].ope[2], allSample[i].atom[3]);
				break;
			case Straight:
				innerB = true, outerB = true;
				
				if(priority(allSample[i].ope[0]) >= priority(allSample[i].ope[1]))
					innerB = false;
				if(priority(allSample[i].ope[1]) >= priority(allSample[i].ope[2]))
					outerB = false;
					
				printf((innerB ?
					(outerB ? "[(%d %c %d) %c %d] %c %d = 24" : "(%d %c %d) %c %d %c %d = 24") :
					(outerB ? "(%d %c %d %c %d) %c %d = 24" : "%d %c %d %c %d %c %d = 24")),
					allSample[i].atom[0],
					allSample[i].ope[0], allSample[i].atom[1],
					allSample[i].ope[1], allSample[i].atom[2],
					allSample[i].ope[2], allSample[i].atom[3]);
				break;
			case Cross:
				printf(priority(allSample[i].ope[0]) >= priority(allSample[i].ope[1]) ?
					"%d %c %d %c %d %c %d = 24" :
					"(%d %c %d) %c (%d %c %d) = 24", allSample[i].atom[0],
					allSample[i].ope[0], allSample[i].atom[1],
					allSample[i].ope[1], allSample[i].atom[2],
					allSample[i].ope[2], allSample[i].atom[3]);
				break;
		}
	
	}
}

//����������
void NewQ(){
	long long lt = time(NULL);	//time����long long
	//���������number
	index_number = 0;
	for(int j = 0 ; j < 8 ; j++){
		//ÿ4bit
		srand((lt) & (clock()) ^ j);	//clock����long
		index_number = (index_number << 4) | (rand() & 0xf);
	}
	if(index_number > 0) index_number %= t_level_total;
	else index_number = (0 - index_number) % t_level_total;
	index_number += t_level_begin;
	getQ();
}

int main(){
	#include"sample.h"
	system("title 24 point");
	system("mode con cols=75 lines=32");
	system("color 0A"); //0 �ڵף�A ����
	
	int ope,
		BACK = 0, FORE = 10;     //ǰ��ɫ�뱳��ɫ
	char cmd[10];
	
	NewQ();
	
	while(true){
		//�����ʱ��4����
		PrintQ();
		
		printf("\n\n\n\tPress '1' to See The ANSWER\n\t"
		"Press '2' to Get Another SAMPLE\n\t"
		"Press '3' to Choose the LEVEL\n\t"
		"Press '6' AND '7' to change the BACK ground color\n\t"
		"Press '8' AND '9' to change the FORE ground color\n\t");
		
		switch (ope = getch()){
			default : break;
			//�ı�Level
			case '3':
				Choose:
				t_level = (Level)( ((int)t_level + 1) % 3);
				switch (t_level){
					default : break;
					case High:
						t_level_begin = high_level_begin;
						t_level_total = high_level_total;
						break;
					case Medium:
						t_level_begin = medium_level_begin;
						t_level_total = medium_level_total;
						break;
					case Low:
						t_level_begin = low_level_begin;
						t_level_total = low_level_total;
						break;
				}
				NewQ();
				break;
			//�鿴��
			case '1':
				PrintA();
				printf("\n\n\n\tPress '3' to Choose The LEVEL\n\t"
				"Press ANY OTER KEY to CONTINUE");
				if(getch() == '3'){
					goto Choose;
				};
				//����ȡ��һ���ӣ�
			//��һ������
			case '2':
				NewQ();
				break;
			//�˳�
			case '\r':
			case '\n':
				#if 0
				HWND hwnd = FindWindow(NULL, "24 point");
				SendMessage(hwnd, WM_CLOSE, 0, 0);
				
				return 0;
				#endif
				break;
			/*�ı���ɫ*/
			case '9':
			case '8':
				do{
					BACK = (BACK + 15 + (ope - '8') * 2 ) % 16;
				}while(BACK == FORE);
				sprintf(cmd, "color %x%x", BACK, FORE);
				system(cmd);
				break;
			case '7':
			case '6':
				do{
					FORE = (FORE + 15 + (ope - '6') * 2 ) % 16;
				}while(BACK == FORE);
				sprintf(cmd, "color %x%x", BACK, FORE);
				system(cmd);
				break;
		}
	}
	return 0;
}
