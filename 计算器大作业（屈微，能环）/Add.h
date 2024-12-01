#pragma once
#include "ArithmeticCal.h"
class Add :
    public ArithmeticCal         //公共继承ArithmeticCal类
	  //因此他继承了void Input()、calculate()和Meau()的函数
	  //同样的，在下面编写Sub(减法)，Multiply(乘法)和Divide(除法)类时都不用在写新的函数
	  //只需要改进calculate()函数，Input()函数直接利用从ArithmeticCal类继承过来的即可
{     
	double calculate();
};

