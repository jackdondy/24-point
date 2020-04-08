#include<stdio.h>
#include<malloc.h>
#include"24 point\head.h"
#include"getFingerPrint.h"

FILE *fp = fopen("24 point/index.h", "w"), *fp2 = fopen("24 point/head.h", "a");
/*
��allSample[]����ͬ����Ŀ�ۺϣ�����Ŀ¼��
ͬʱ��Ŀ¼�ǰ�����Ŀ�Ľ�����С���������
*/

typedef struct _{
	int begin;
	int num;
	struct _ *left, *right;
}indexNode;
indexNode *indexRoot = NULL;

//������������������num��С�����������num��ͬ�������Ҳ�
void Count2(int begin, int num){
	//�����½ڵ�
	indexNode *newNode = (indexNode*)malloc(sizeof(indexNode));
	newNode->left = newNode->right = NULL;
	newNode->begin = begin;
	newNode->num = num;
	
	//��������
	if(NULL == indexRoot){
		indexRoot = newNode;
		return ;
	}
	
	for(indexNode *t = indexRoot; t != NULL; ){
		if(newNode->num < t->num){
			//�������
			if(NULL == t->left) {
				t->left = newNode;
				return ;
			}
			t = t->left;
		}else{
			//�����ұ�
			if(NULL == t->right){
				t->right = newNode;
				return ;
			}
			t = t->right;
		}
	}
}



void makeIndex(){
	long long finger1, finger2;

	int num;
	for(int begin = 0 ; begin < Total; ){
		//�±��index��ʼ

		finger1 = getFingerPrint(allSample[begin].atom);

		//��������num����
		for(num = 1; ; num++){
			//˵����ʱ�������һ��Ա�,�����һ��Ҳ��ͬ
			if(begin + num == Total){
				Count2(begin, num);
				fclose(fp);
				return ;
			}

			finger2 = getFingerPrint(allSample[begin + num].atom);

			if(finger2 == finger1)  continue;
			else {

				Count2(begin, num);
				
				//����״̬
				begin += num;
				finger1 = finger2;
				
				break;
			}

		}

		if(begin == Total - 1){
			//��ʱ���һ���
			Count2(begin, 1);
			return ;
		}
	}
}

/*�Ѷȣ��� (ֻ��һ����)�� (2��3����)�� (4��������)*/

int medium_level_begin, low_level_begin;

int count = 0;  //ע�ͳ���index��ÿ����±�
int last_num = 0;
void printIndex(indexNode *t){
	if(NULL == t)   return ;
	
	//�����������
	//�������������
	printIndex(t->left);
	
	if(t->num != last_num){
		fprintf(fp, "\n\n");
		if(2 == t->num) medium_level_begin = count;
		if(4 == t->num) low_level_begin = count;
	}
	last_num = t->num;
	//���t�ڵ�
	fprintf(fp, "\n\t{%5d,%5d},\t//%d", t->begin, t->num, count++);
	
	//���������
	printIndex(t->right);
	
	//�ͷ�
	free(t);
}
int main(){
	#include"24 point/sample.h"
	
	makeIndex();
	
	fprintf(fp, "int index[][2] = {");
	printIndex(indexRoot);
	fprintf(fp, "\n};\n\n");
	
	fprintf(fp2, "\n#define indexTotal %d\n", count);
	
	fprintf(fp2, "\n/*�Ѷȣ�"
	"�� (ֻ��һ����)"
	"�� (2��3����)"
	"�� (4��������)*/"
	);
	
	fprintf(fp2, "\n#define high_level_begin 0"
	"\n#define high_level_total %d\n"
	"\n#define medium_level_begin %d"
	"\n#define medium_level_total %d\n"
	"\n#define low_level_begin %d"
	"\n#define low_level_total %d",
	medium_level_begin,                     //high_level_total
	medium_level_begin,
	low_level_begin - medium_level_begin,   //medium_level_total
	low_level_begin,
	count - low_level_begin                 //low_level_total
	);

	fclose(fp), fclose(fp2);
	return 0;
}
