#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//#include <iostream>
using namespace std;

// �����궨��
//template<typename T1, typename T2>
//constexpr auto random(T1 a, T2 b) { return (rand() % (b - a + 1) + a); }   // ����[a,b]����������

int random(int a, int b);  // ����[a,b]����������
char* GeneratePro();
char* GenerateOperand();