#include "Calculator.h"

int range;    // ��������Χ
char p[100] = { 0 };
char* problem = p;  // �ַ�ָ�룬ָ�����ɵ���Ŀ
FILE* fp_e = NULL;    // ��Ŀ�ļ����ļ�ָ��
FILE* fp_a = NULL;    // ���ļ����ļ�ָ��
//FILE* fp_g = NULL;    // ���ͳ����Ŀ�����ļ����ļ�ָ��
char* pro[12];	  // �����Ŀ��ָ�����飬ÿһԪ�ض�Ӧһ���������Ż�������������
char r[10] = { 0 };
char* result = r;
int k = 0;		 // kָʾ��ǰ������/������/������������Ŀ�����е��±�
int top1 = -1;    // ָʾ������ջ��ջ��ָ��
int top2 = -1;    // ָʾ������ջ��ջ��ָ��

int main(int argc, char* argv[])
{
	int num;     // ���ɵ���Ŀ����
	char ind[10] = { 0 };
	char* index = ind;
	printf("  ================================ ������ʾ ==============================\n");
	printf("||		               ���� r���ڵ� n ����Ŀ	      	          ||\n");
	printf("||       D:\\prj\\Test\\Debug Calculator.exe -r ��Χ�� -n ��Ŀ��             ||\n");
	printf("||			�磺����10���ڵ�100����Ŀ			  ||\n");
	printf("||	       D:\\prj\\Test\\Debug Calculator.exe -r 10 -n 100              ||\n");
	printf("  ========================================================================\n");
	printf("||			   �Ը�����Ŀ�ļ��ʹ��ļ��д�ͳ��		  ||\n");
	printf("||	D:\\prj\\Test\\Debug Calculator.exe ��Ŀ�ļ��� ���ļ���            ||\n");
	printf("||       �磺���ͳ����Ŀ�ļ�Exercise.txt�ʹ��ļ�Answer.txt             ||\n");
	printf("||     D:\\prj\\Test\\Debug Calculator.exe Exercise.txt Answer.txt           ||\n");
	printf("  ========================================================================\n");  

	// char* problem = NULL;  // �ַ�ָ�룬ָ�����ɵ���Ŀ
	// ��鲢��������
	if (argc == 3)
	{
		Check((FILE*)argv[1], (FILE*)argv[2]);
		return 0;
	}
	
	else if (argc == 5)
	{
		if (strcmp(argv[1], "-r") != 0 || strcmp(argv[3], "-n") != 0)
			printf("�����������\n �����������ʾ����");
	}

	range = atoi(argv[2]);
	num = atoi(argv[4]);
	//allsub = (AllSub*)malloc(sizeof(AllSub) * num);    // ���ٿռ�
	printf("�����뷶Χ ������%d %d\n", range, num);
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		sign_s[i].sign = (char*)malloc(4);      // Ϊָ��������򵥱����ŵ�ָ������ڴ�
		//memset(sign_s[i].sign, 0, sizeof(sign_s[i].sign));  // ��ʼ���ڴ�ռ�
	}

	// Ϊ�����Ŀ��ָ����������ڴ�ռ�
	for (int i = 0; i < 12; i++)
	{
		pro[i] = (char*)malloc(N * 4);
	}
	fopen_s(&fp_e, "D:/prj/Calculator/Debug/Exercises.txt", "w+");
	fopen_s(&fp_a, "D:/prj/Calculator/Debug/Answers.txt", "w+");
	while (count < num)  // δ�ﵽָ��������������������
	{
		// ������Ŀ���
		_itoa_s(count + 1, index, 10, 10); //����������ת�����ַ���
		strcat_s(index, strlen(index) + 3, ". ");
		memset(problem, 0, sizeof(problem));  // ����ڴ�
		memset(result, 0, sizeof(result));  // ����ڴ�
		top1 = -1;    // ָʾ������ջ��ջ��ָ��
		top2 = -1;    // ָʾ������ջ��ջ��ָ��
		k = 0;
		GeneratePro();
		for (int j = 0; j < 12; j++)
		{
			if(pro[j])
				strcat_s(problem, strlen(problem) + strlen(pro[j]) + 1, pro[j]);
		}
		// fseek(fp_e, 0, SEEK_END);    // ���ļ�ָ�붨λ���ļ�ĩβ
		fputs(index, fp_e);          // ��д�����
		fputs(index, fp_a);          // ��д�����
		fputs(problem, fp_e);        // д����Ŀ
		fputs(result, fp_a);         // д���
		fputs("\n", fp_e);           // ÿдһ�⻻��
		fputs("\n", fp_a);           // ÿдһ�⻻��
		printf("the problem is: ");
		puts(problem);
		printf("the answer is: ");
		puts(result);
		/* ����Ŀд���ļ�
		/* ����Ŀд���ļ�
		if(count == 0)
			fopen_s(&fp,"D:/prj/Calculator/Debug/temp.txt", "w+");
		fseek(fp, 0, SEEK_END);    // ���ļ�ָ�붨λ���ļ�ĩβ
		fputs(problem, fp);
		fputs("\n", fp);
		printf("the problem is: ");
		puts(problem);
		count++;
		*/
		memset(index, 0, sizeof(index));  // ����ڴ�
		count++;
		// ������ʽ�����������Ҫ���м���д����һ�ļ�
		// ���ָ�����ֱ����������
	}
	fclose(fp_e);
	fclose(fp_a);
	// �ͷ��ڴ�ռ�
	for (int i = 0; i < 10; i++)
	{
		free(sign_s[i].sign);
		sign_s[i].sign = NULL;      // ָ���ÿ�
	}

	// Ϊ�����Ŀ��ָ�������ͷ��ڴ�ռ�
	for (int i = 0; i < 12; i++)
	{
		free(pro[i]);
		pro[i] = NULL;      // ָ���ÿ�
	}
	return 0;
}

