//考虑要是把所有运算分开写，那么文件数量会很多
//因此接下来把有关三角函数运算的类全部写在TrigonometricMenu的头文件中
#pragma once
#include"Calculator.h"
#include"cmath"
using namespace std;
class TrigonometricMenu:public Calculator   //三角函数类
{   	
public:
	    double number;                       //定义了一个数据
		void Input();                       //输入并获取计算数据的函数
		double calculate() { return 0; };    //计算器函数
		void Menu(Calculator* pCal);        //菜单函数
};
class GetSin :public TrigonometricMenu
{
public:
	double calculate() override  { return sin(number); }
};
class GetCos :public TrigonometricMenu
{
public:
	double calculate() override  { return cos(number); }
};
class GetTan :public TrigonometricMenu
{
public:
	double calculate() override   { return tan(number);}
};
class GetCot :public TrigonometricMenu
{
public:
	double calculate() override   { return 1.0/tan(number); }
};
class GetCsc :public TrigonometricMenu
{
public:
	double calculate() override    { return 1.0 / sin(number); }
};
class GetSec :public TrigonometricMenu
{
public:
	double calculate() override     { return 1.0 / cos(number); }
};
class GetInverse :public TrigonometricMenu
{
public:
	double calculate() override { return 1.0 / (number); }
};
