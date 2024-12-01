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
	bool isOperator(char c);            // 用于检查是否是运算符  
	int precedence(char op);            //用于比较运算符的优先级  
	int applyOp(int a, int b, char op); // 用于应用运算符到两个数上
	void getResult();                   //打印输出结果
};

