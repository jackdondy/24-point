/*
24点
4个数字(1,2,3,4,5,6,7,8,9,10,11,12,13)，通过加减乘除得到24.
遍历出所有情况

*/

#include<stdio.h>
#include<malloc.h>

#include"24 point\head.h"

FILE *fp = fopen("24 point/sample.h", "w"), *fp2 = fopen("24 point/head.h", "a");

int count = 0;  //记录当前已到第几个情况

void Print(Sample *sample){
	fprintf(fp, "\nallSample[%d].mode = ", count);
	switch (sample->mode){
		case UpDown:
			fprintf(fp, "UpDown");
			break;
		case Straight:
			fprintf(fp, "Straight");
			break;
		case Cross:
			fprintf(fp, "Cross");
			break;
	}
	fprintf(fp, ";\nallSample[%d].atom[0] = %d;\n", count, sample->atom[0]);
	fprintf(fp, "allSample[%d].atom[1] = %d;\n", count, sample->atom[1]);
	fprintf(fp, "allSample[%d].atom[2] = %d;\n", count, sample->atom[2]);
	fprintf(fp, "allSample[%d].atom[3] = %d;\n", count, sample->atom[3]);
	fprintf(fp, "allSample[%d].ope[0] = \'%c\';\n", count, sample->ope[0]);
	fprintf(fp, "allSample[%d].ope[1] = \'%c\';\n", count, sample->ope[1]);
	fprintf(fp, "allSample[%d].ope[2] = \'%c\';\n", count, sample->ope[2]);
	count++;
}

//作为全局变量被Sample1~4直接使用，并适时被Count统计
int atom[4];
unsigned char ope[3];
Mode mode;

int total = 0;
typedef struct _Node{
	long long fingerPrint;
	Sample *sample;
	_Node *left, *right;
}Node;
Node *head = NULL;

#include"getFingerPrint.h"
void Count(){
	//将所有样例边排序边统计,采用链表，二叉查找树
	
	Sample *_t = (Sample*)malloc(sizeof(Sample));
	_t->mode = mode;
	_t->ope[0] = ope[0];
	_t->ope[1] = ope[1];
	_t->ope[2] = ope[2];
	_t->atom[0] = atom[0];
	_t->atom[1] = atom[1];
	_t->atom[2] = atom[2];
	_t->atom[3] = atom[3];
	
	Node *t = (Node*)malloc(sizeof(Node));
	t->sample = _t;
	t->left = t->right = NULL;
	t->fingerPrint = getFingerPrint(_t->atom);
	
	if(NULL == head){
		head = t;
	}else for(Node *temp = head ; temp != NULL ; ){
			if(t->fingerPrint < temp->fingerPrint){
				//往左
				if(temp->left != NULL){
					temp = temp->left;
					continue;
				}
				temp->left = t;
				return ;
			}else{
				//往右
				if(temp->right != NULL){
					temp = temp->right;
					continue;
				}
				temp->right = t;
				return ;
			}
	}
	
}

void End(Node *t){
	//把二叉树按序输出
	//输出左边
	if(NULL == t)   return ;
	End(t->left);
	
	Print(t->sample);
	
	End(t->right);
	
	free(t->sample);
	free(t);
}

int r1, r2;
#include"Sample1.h"
#include"Sample2.h"
#include"Sample3.h"
#include"Sample4.h"

int main(){
	
	Sample1();
	Sample2();
	Sample3();
	Sample4();
	
	End(head);
	
	fprintf(fp2, "\n#define Total %d\n"
	"Sample allSample[Total];\n", count);
	
	fclose(fp), fclose(fp2);
	
	return 0;
}
