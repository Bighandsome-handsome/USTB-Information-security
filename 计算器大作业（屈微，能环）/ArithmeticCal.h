#pragma once
#include "Calculator.h"                 //����Calculatorͷ�ļ���Ҫ��Ȼ����̳�û�а취ʵ��
class ArithmeticCal :                   //�������������࣬�����м̳���Calculator����
    public Calculator
{
protected:
	double num1, num2;                   //��������������
public:
	void Input();                       //���벢��ȡ�������ݵĺ���
	double calculate() { return 0; };    //����������
	void Menu(Calculator *pCal);        //�˵�����
};

//ArithmeticCal��Calculator�඼�ǲ˵������ã����Ƕ������Ӿ�������������

