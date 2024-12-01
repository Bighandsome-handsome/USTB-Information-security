#pragma once
#include "Calculator.h"                 //调入Calculator头文件，要不然下面继承没有办法实现
class ArithmeticCal :                   //这是四则运算类，它公有继承了Calculator的类
    public Calculator
{
protected:
	double num1, num2;                   //定义了两个数据
public:
	void Input();                       //输入并获取计算数据的函数
	double calculate() { return 0; };    //计算器函数
	void Menu(Calculator *pCal);        //菜单函数
};

//ArithmeticCal和Calculator类都是菜单的作用，它们都是连接具体计算操作的类

