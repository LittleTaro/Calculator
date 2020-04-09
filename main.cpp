#include "Calculator.h"

int range;    // 操作数范围
char p[100] = { 0 };
char* problem = p;  // 字符指针，指向生成的题目
FILE* fp_e = NULL;    // 题目文件的文件指针
FILE* fp_a = NULL;    // 答案文件的文件指针
//FILE* fp_g = NULL;    // 存放统计题目正误文件的文件指针
char* pro[12];	  // 存放题目的指针数组，每一元素对应一个单边括号或操作数或操作符
char r[10] = { 0 };
char* result = r;
int k = 0;		 // k指示当前操作数/操作符/单边括号在题目数组中的下标
int top1 = -1;    // 指示操作数栈的栈顶指针
int top2 = -1;    // 指示操作符栈的栈顶指针

int main(int argc, char* argv[])
{
	int num;     // 生成的题目数量
	char ind[10] = { 0 };
	char* index = ind;
	printf("  ================================ 输入提示 ==============================\n");
	printf("||		               生成 r以内的 n 道题目	      	          ||\n");
	printf("||       D:\\prj\\Test\\Debug Calculator.exe -r 范围数 -n 题目数             ||\n");
	printf("||			如：生成10以内的100道题目			  ||\n");
	printf("||	       D:\\prj\\Test\\Debug Calculator.exe -r 10 -n 100              ||\n");
	printf("  ========================================================================\n");
	printf("||			   对给定题目文件和答案文件判错并统计		  ||\n");
	printf("||	D:\\prj\\Test\\Debug Calculator.exe 题目文件名 答案文件名            ||\n");
	printf("||       如：检查统计题目文件Exercise.txt和答案文件Answer.txt             ||\n");
	printf("||     D:\\prj\\Test\\Debug Calculator.exe Exercise.txt Answer.txt           ||\n");
	printf("  ========================================================================\n");  

	// char* problem = NULL;  // 字符指针，指向生成的题目
	// 检查并解析参数
	if (argc == 3)
	{
		Check((FILE*)argv[1], (FILE*)argv[2]);
		return 0;
	}
	
	else if (argc == 5)
	{
		if (strcmp(argv[1], "-r") != 0 || strcmp(argv[3], "-n") != 0)
			printf("命令输入错误！\n 请参照输入提示输入");
	}

	range = atoi(argv[2]);
	num = atoi(argv[4]);
	//allsub = (AllSub*)malloc(sizeof(AllSub) * num);    // 开辟空间
	printf("请输入范围 题数：%d %d\n", range, num);
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		sign_s[i].sign = (char*)malloc(4);      // 为指向运算符或单边括号的指针分配内存
		//memset(sign_s[i].sign, 0, sizeof(sign_s[i].sign));  // 初始化内存空间
	}

	// 为存放题目的指针数组分配内存空间
	for (int i = 0; i < 12; i++)
	{
		pro[i] = (char*)malloc(N * 4);
	}
	fopen_s(&fp_e, "D:/prj/Calculator/Debug/Exercises.txt", "w+");
	fopen_s(&fp_a, "D:/prj/Calculator/Debug/Answers.txt", "w+");
	while (count < num)  // 未达到指定生成数量，继续生成
	{
		// 生成题目序号
		_itoa_s(count + 1, index, 10, 10); //把整数部分转换成字符串
		strcat_s(index, strlen(index) + 3, ". ");
		memset(problem, 0, sizeof(problem));  // 清空内存
		memset(result, 0, sizeof(result));  // 清空内存
		top1 = -1;    // 指示操作数栈的栈顶指针
		top2 = -1;    // 指示操作符栈的栈顶指针
		k = 0;
		GeneratePro();
		for (int j = 0; j < 12; j++)
		{
			if(pro[j])
				strcat_s(problem, strlen(problem) + strlen(pro[j]) + 1, pro[j]);
		}
		// fseek(fp_e, 0, SEEK_END);    // 把文件指针定位到文件末尾
		fputs(index, fp_e);          // 先写入序号
		fputs(index, fp_a);          // 先写入序号
		fputs(problem, fp_e);        // 写入题目
		fputs(result, fp_a);         // 写入答案
		fputs("\n", fp_e);           // 每写一题换行
		fputs("\n", fp_a);           // 每写一题换行
		printf("the problem is: ");
		puts(problem);
		printf("the answer is: ");
		puts(result);
		/* 讲题目写入文件
		/* 讲题目写入文件
		if(count == 0)
			fopen_s(&fp,"D:/prj/Calculator/Debug/temp.txt", "w+");
		fseek(fp, 0, SEEK_END);    // 把文件指针定位到文件末尾
		fputs(problem, fp);
		fputs("\n", fp);
		printf("the problem is: ");
		puts(problem);
		count++;
		*/
		memset(index, 0, sizeof(index));  // 清空内存
		count++;
		// 计算表达式结果：在其中要将中间结果写进另一文件
		// 出现负数，直接重新生成
	}
	fclose(fp_e);
	fclose(fp_a);
	// 释放内存空间
	for (int i = 0; i < 10; i++)
	{
		free(sign_s[i].sign);
		sign_s[i].sign = NULL;      // 指针置空
	}

	// 为存放题目的指针数组释放内存空间
	for (int i = 0; i < 12; i++)
	{
		free(pro[i]);
		pro[i] = NULL;      // 指针置空
	}
	return 0;
}

