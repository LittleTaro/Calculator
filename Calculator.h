#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<time.h>
//#include <iostream>
using namespace std;

constexpr int N = 2;   // 参数r的最大可能位数，暂定不超过2位;

// 定义存放操作数的结构体，将操作数统一成带分数形式存放
struct NUM {
	int numerator;   // 分子部分
	int denominator;  // 分母部分
	// 此处可增加一个索引，指示该操作数在题目中的下标，这样就可通过修改操作数校正题目
	// 时间有限，下次再试
};

// 定义存放操作符的结构体，包括该符号对应在题目中的位序
struct SIGN {
	int sign_index;   // 0~5分别对应"+-*/()"，指示符号类型
	int pro_index;    // 指示在题目数组中的下标
	char* sign;		  // 初始化，还未分配空间
};

// 定义子表达式结构体
struct SubPro {
	int a;   // 操作数1的分子
	int b;   // 操作数1的分母
	int c;   // 操作数2的分子
	int d;   // 操作数2的分母
	int sign_index;  // 可表示子表达式的运算符类型
};

// 定义存放一条题目所有子表达式的结构体
struct AllSub {
	int sub_cnt;   // 题目中的子表达式个数
	SubPro subpro[3]; // 子表达式结构体数组
};

// 存放操作数的栈，是一个结构体数组
__declspec(selectany) struct NUM num_s[5];
// struct NUM num_s[5];
// 存放操作符的栈,是一个结构体数组
__declspec(selectany) struct SIGN sign_s[10];
// struct SIGN sign_s[10];
// 每一道题目要有AllSub结构体，n道题目使用一个AllSub结构体指针
__declspec(selectany) struct AllSub* allsub;


// 函数宏定义
//template<typename T1, typename T2>
//constexpr auto random(T1 a, T2 b) { return (rand() % (b - a + 1) + a); }   // 生成[a,b]间的随机整数

int random(int a, int b);  // 生成[a,b]间的随机整数
int GeneratePro();
char* GenerateOperand();


int gcd(int m, int n);    // 辗转相除法求m, n最大公约数
int prior(int sign_index);   // 栈顶运算符优先级小于对应运算符时返回1，否则返回0
int CalculateSubPro(int sign_index, NUM num1, NUM num2);   // 计算子表达式，出现负数，返回-1；出现除数为0，返回0
//int subPro(int a, int b, int c, int d, int sign_index);   // 返回子表达式
int LastRes();      // 将题目最终结果转换成字符串形式
int OutCal();     // 运算符出栈及其相应计算
int InSign(int sign_index, int pro_index);     // 运算符入栈函数实现运算符入栈及相应一系列计算记录子表达式的操作
int LastCal();    // 数字已全部扫描完毕，继续处理栈中数据或符号
void Check(FILE* fp_e, FILE* fp_a);    // 每一行存放一题

#endif





/*
int record(int cnt, int number, char* Tuple);  // 返回当前正确/错误题目数量
{
	// 定义指向字符串型序号的指针(初始化内存，但内容要全部置0)
	numberPt = NULL;
	// 定义temp;  numberPt 是"(, )序号"，而temp只是"序号"
	cnt++;   // 更新正确题目数
	// 判断该题是否为第一道正确题目
	if (strcmp(Tuple, "("))  // 不是第一道
	{
		strcat_s(numberPt连接上", ")
	}
	将题目序号转换成字符串形式, 存于temp
		iota(number);
	将temp连接到numberPt // 它什么时候需要清空内容,每个题目之前
		strcat_s(temp, numberPt);
	将字符串的题目序号追加到正确结果元组
		strcat_s(Tuple, numberPt);
	return cnt;  // 返回当前正确/错误题目数
}*/


