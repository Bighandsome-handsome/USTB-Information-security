#include "Binary.h"
#include<iostream>
#include<string>
#include<cstring>
#include<string.h>
using namespace std;
Binary::Binary(int number) { this->number = number; }
//下面用递归函数求二进制
string Binary::GetBinary(long long number)   
{
	if (number == 0) return "0";
	if (number == 1)    return "1";
	else
	{
		string binary = GetBinary(number / 2);
		binary = (number % 2 == 0 ? "0" : "1") + binary;
		return binary;
	}
}
void Binary::GetNumber()
{
	cout << "输入一个十进制整数:";
	cin >> number;
}