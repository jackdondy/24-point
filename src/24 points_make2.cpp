#include<stdio.h>
#include<malloc.h>
#include"24 point\head.h"
#include"getFingerPrint.h"

FILE *fp = fopen("24 point/index.h", "w"), *fp2 = fopen("24 point/head.h", "a");
/*
将allSample[]中相同的题目综合，建立目录，
同时该目录是按照题目的解数从小到大排序的
*/

typedef struct _{
	int begin;
	int num;
	struct _ *left, *right;
}indexNode;
indexNode *indexRoot = NULL;

//建立二叉排序树，按num从小到大排序，如果num相同，插入右侧
void Count2(int begin, int num){
	//建立新节点
	indexNode *newNode = (indexNode*)malloc(sizeof(indexNode));
	newNode->left = newNode->right = NULL;
	newNode->begin = begin;
	newNode->num = num;
	
	//插入树中
	if(NULL == indexRoot){
		indexRoot = newNode;
		return ;
	}
	
	for(indexNode *t = indexRoot; t != NULL; ){
		if(newNode->num < t->num){
			//插入左边
			if(NULL == t->left) {
				t->left = newNode;
				return ;
			}
			t = t->left;
		}else{
			//插入右边
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
		//下标从index开始

		finger1 = getFingerPrint(allSample[begin].atom);

		//数出共有num个解
		for(num = 1; ; num++){
			//说明此时已与最后一项对比,且最后一项也相同
			if(begin + num == Total){
				Count2(begin, num);
				fclose(fp);
				return ;
			}

			finger2 = getFingerPrint(allSample[begin + num].atom);

			if(finger2 == finger1)  continue;
			else {

				Count2(begin, num);
				
				//更新状态
				begin += num;
				finger1 = finger2;
				
				break;
			}

		}

		if(begin == Total - 1){
			//此时最后一项单独
			Count2(begin, 1);
			return ;
		}
	}
}

/*难度：高 (只有一个解)中 (2或3个解)低 (4个解以上)*/

int medium_level_begin, low_level_begin;

int count = 0;  //注释出在index中每项的下标
int last_num = 0;
void printIndex(indexNode *t){
	if(NULL == t)   return ;
	
	//将二叉树输出
	//首先输出左子树
	printIndex(t->left);
	
	if(t->num != last_num){
		fprintf(fp, "\n\n");
		if(2 == t->num) medium_level_begin = count;
		if(4 == t->num) low_level_begin = count;
	}
	last_num = t->num;
	//输出t节点
	fprintf(fp, "\n\t{%5d,%5d},\t//%d", t->begin, t->num, count++);
	
	//输出右子树
	printIndex(t->right);
	
	//释放
	free(t);
}
int main(){
	#include"24 point/sample.h"
	
	makeIndex();
	
	fprintf(fp, "int index[][2] = {");
	printIndex(indexRoot);
	fprintf(fp, "\n};\n\n");
	
	fprintf(fp2, "\n#define indexTotal %d\n", count);
	
	fprintf(fp2, "\n/*难度："
	"高 (只有一个解)"
	"中 (2或3个解)"
	"低 (4个解以上)*/"
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
