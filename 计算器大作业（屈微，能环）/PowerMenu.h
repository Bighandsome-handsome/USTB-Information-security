#pragma once
#include"Calculator.h"
#include"cmath"
using namespace std;
class PowerMenu :public Calculator   //乘方数类
{
public:
	double number1, number2;                       //定义了两个数据
	void Input();                                  //输入并获取计算数据的函数
	double calculate() { return 0; };              //计算器函数
	void Menu(Calculator* pCal);                   //菜单函数
};
class GetSqrt :public PowerMenu
{
public:
	double calculate()override { return sqrt(number1); }
};
class GetPow :public PowerMenu
{
public:
	double calculate()override { return pow(number1,number2); }
};
class GetCube :public PowerMenu
{
public:
	double calculate()override { return pow(number1,1.0/3.0); }
};
