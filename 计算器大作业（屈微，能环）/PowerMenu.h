#pragma once
#include"Calculator.h"
#include"cmath"
using namespace std;
class PowerMenu :public Calculator   //�˷�����
{
public:
	double number1, number2;                       //��������������
	void Input();                                  //���벢��ȡ�������ݵĺ���
	double calculate() { return 0; };              //����������
	void Menu(Calculator* pCal);                   //�˵�����
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
