#pragma once
#include <iostream>  
#include <stack>  
#include <sstream>  
#include <cctype>  
using namespace std;
class MixCalculate
{
public:
	string expression;
	MixCalculate(string expression);
	bool isOperator(char c);            // ���ڼ���Ƿ��������  
	int precedence(char op);            //���ڱȽ�����������ȼ�  
	int applyOp(int a, int b, char op); // ����Ӧ�����������������
	void getResult();                   //��ӡ������
};

