#pragma once
#include "ArithmeticCal.h"             //�������ArithmeticCal���ͷ�ļ�
class Multiply :public ArithmeticCal
{
	double calculate() override;
	//������������calculate()������ֻ���Multiply��ģ���override��д                             
};