#pragma once
#include "ArithmeticCal.h"
class Add :
    public ArithmeticCal         //�����̳�ArithmeticCal��
	  //������̳���void Input()��calculate()��Meau()�ĺ���
	  //ͬ���ģ��������дSub(����)��Multiply(�˷�)��Divide(����)��ʱ��������д�µĺ���
	  //ֻ��Ҫ�Ľ�calculate()������Input()����ֱ�����ô�ArithmeticCal��̳й����ļ���
{     
	double calculate();
};

