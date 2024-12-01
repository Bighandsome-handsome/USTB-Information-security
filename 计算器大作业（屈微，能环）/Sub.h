#pragma once
#include "ArithmeticCal.h"             //这里调用ArithmeticCal类的头文件
class Sub:public ArithmeticCal
{
	double calculate() override;
	//保险起见，这个calculate()函数是只针对Sub类的，用override重写                             
};

