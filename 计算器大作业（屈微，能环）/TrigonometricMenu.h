//����Ҫ�ǰ���������ֿ�д����ô�ļ�������ܶ�
//��˽��������й����Ǻ����������ȫ��д��TrigonometricMenu��ͷ�ļ���
#pragma once
#include"Calculator.h"
#include"cmath"
using namespace std;
class TrigonometricMenu:public Calculator   //���Ǻ�����
{   	
public:
	    double number;                       //������һ������
		void Input();                       //���벢��ȡ�������ݵĺ���
		double calculate() { return 0; };    //����������
		void Menu(Calculator* pCal);        //�˵�����
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
