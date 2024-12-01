#pragma once
//为了后面使用pow sqrt sin等函数的时候有“从“double”转换到“float”，可能丢失数据”的警告
//将原来的float类型数据全部改为double
class Calculator                                  //这是一个虚基类
{
public:
	virtual void Input() = 0;                    //虚函数：输入并取计算所需的数据
	virtual double calculate()=0;                 //虚函数：执行实际的计算，并返回结果
	virtual void Menu(Calculator* pCal)=0;       //虚函数：选择菜单功能（执行哪种运算）
	 //pCal是指向当前计算器运算的对象的指针
};