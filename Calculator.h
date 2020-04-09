#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<time.h>
//#include <iostream>
using namespace std;

constexpr int N = 2;   // ����r��������λ�����ݶ�������2λ;

// �����Ų������Ľṹ�壬��������ͳһ�ɴ�������ʽ���
struct NUM {
	int numerator;   // ���Ӳ���
	int denominator;  // ��ĸ����
	// �˴�������һ��������ָʾ�ò���������Ŀ�е��±꣬�����Ϳ�ͨ���޸Ĳ�����У����Ŀ
	// ʱ�����ޣ��´�����
};

// �����Ų������Ľṹ�壬�����÷��Ŷ�Ӧ����Ŀ�е�λ��
struct SIGN {
	int sign_index;   // 0~5�ֱ��Ӧ"+-*/()"��ָʾ��������
	int pro_index;    // ָʾ����Ŀ�����е��±�
	char* sign;		  // ��ʼ������δ����ռ�
};

// �����ӱ��ʽ�ṹ��
struct SubPro {
	int a;   // ������1�ķ���
	int b;   // ������1�ķ�ĸ
	int c;   // ������2�ķ���
	int d;   // ������2�ķ�ĸ
	int sign_index;  // �ɱ�ʾ�ӱ��ʽ�����������
};

// ������һ����Ŀ�����ӱ��ʽ�Ľṹ��
struct AllSub {
	int sub_cnt;   // ��Ŀ�е��ӱ��ʽ����
	SubPro subpro[3]; // �ӱ��ʽ�ṹ������
};

// ��Ų�������ջ����һ���ṹ������
__declspec(selectany) struct NUM num_s[5];
// struct NUM num_s[5];
// ��Ų�������ջ,��һ���ṹ������
__declspec(selectany) struct SIGN sign_s[10];
// struct SIGN sign_s[10];
// ÿһ����ĿҪ��AllSub�ṹ�壬n����Ŀʹ��һ��AllSub�ṹ��ָ��
__declspec(selectany) struct AllSub* allsub;


// �����궨��
//template<typename T1, typename T2>
//constexpr auto random(T1 a, T2 b) { return (rand() % (b - a + 1) + a); }   // ����[a,b]����������

int random(int a, int b);  // ����[a,b]����������
int GeneratePro();
char* GenerateOperand();


int gcd(int m, int n);    // շת�������m, n���Լ��
int prior(int sign_index);   // ջ����������ȼ�С�ڶ�Ӧ�����ʱ����1�����򷵻�0
int CalculateSubPro(int sign_index, NUM num1, NUM num2);   // �����ӱ��ʽ�����ָ���������-1�����ֳ���Ϊ0������0
//int subPro(int a, int b, int c, int d, int sign_index);   // �����ӱ��ʽ
int LastRes();      // ����Ŀ���ս��ת�����ַ�����ʽ
int OutCal();     // �������ջ������Ӧ����
int InSign(int sign_index, int pro_index);     // �������ջ����ʵ���������ջ����Ӧһϵ�м����¼�ӱ��ʽ�Ĳ���
int LastCal();    // ������ȫ��ɨ����ϣ���������ջ�����ݻ����
void Check(FILE* fp_e, FILE* fp_a);    // ÿһ�д��һ��

#endif





/*
int record(int cnt, int number, char* Tuple);  // ���ص�ǰ��ȷ/������Ŀ����
{
	// ����ָ���ַ�������ŵ�ָ��(��ʼ���ڴ棬������Ҫȫ����0)
	numberPt = NULL;
	// ����temp;  numberPt ��"(, )���"����tempֻ��"���"
	cnt++;   // ������ȷ��Ŀ��
	// �жϸ����Ƿ�Ϊ��һ����ȷ��Ŀ
	if (strcmp(Tuple, "("))  // ���ǵ�һ��
	{
		strcat_s(numberPt������", ")
	}
	����Ŀ���ת�����ַ�����ʽ, ����temp
		iota(number);
	��temp���ӵ�numberPt // ��ʲôʱ����Ҫ�������,ÿ����Ŀ֮ǰ
		strcat_s(temp, numberPt);
	���ַ�������Ŀ���׷�ӵ���ȷ���Ԫ��
		strcat_s(Tuple, numberPt);
	return cnt;  // ���ص�ǰ��ȷ/������Ŀ��
}*/


