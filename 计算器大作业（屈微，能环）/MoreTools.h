#pragma once
//���ǵ�double���͵��ڴ����ռ����ޣ����ܴ���ϴ����ֵĳ˷��ͼӷ�
//����ཫ��ʵ�ִ����ĳ˷��ͼӷ�
#include<string.h>
#include<cstring>
#include"string"
#include<iostream>
const int maxn = 5000;
const int maxn2 = maxn * 2;
using namespace std;
class MoreTools
{
public:
	string expression1, expression2,str;
	MoreTools(string expression1, string expression2);
	int read_str(string str, int* a);
	void GetLargeMultiply();
	void GetLargeAdd();
    void GetExpression();
    void PrintMenu();
};
