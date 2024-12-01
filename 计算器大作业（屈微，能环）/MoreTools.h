#pragma once
//考虑到double类型的内存分配空间有限，不能处理较大数字的乘法和加法
//这个类将会实现大数的乘法和加法
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
