#include "Binary.h"
#include<iostream>
#include<string>
#include<cstring>
#include<string.h>
using namespace std;
Binary::Binary(int number) { this->number = number; }
//�����õݹ麯���������
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
	cout << "����һ��ʮ��������:";
	cin >> number;
}