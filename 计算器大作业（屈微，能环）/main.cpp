//������˵����
// (1)���ܣ�1. С������������
//          2. ���Ǻ�������
//          3. ƽ���������������ݵļ���
//          4. �����ĳ˷��ͼӷ��������
//          5. �����Ķ�����ת����ʮ����ת���ɶ����ƣ�
//          6. �����˻�ϼ��������ܣ�֧�ּӼ��˳�С���ŵĻ�����㡣
#include <iostream>
#include <math.h>
#include "Calculator.h"
#include "ArithmeticCal.h"
#include"TrigonometricMenu.h"
#include"PowerMenu.h"
#include"MoreTools.h"
#include"Binary.h"
#include"MixCalculate.h"
using namespace std;
void printMainMenu()
{
	cout << "\n\t Scientific Calculator!";
	cout << "\n\t\t **MENU**";
	cout << "\n\t1. Arithmetic Operations (+ , - , * , /)";
	cout << "\n\t2. Trigonometric Operations (sin , cos , tan , inverse)";
	cout << "\n\t3. Power functions (power , squareroot , cuberoot)";
	cout << "\n\t4. Large Interger Calculations";
	cout << "\n\t5. Get Binary Calculations";
	cout << "\n\t6. Enter 6 to calculate mix expressions";
	cout << "\n\t0. Enter 0 to Exit\n";
	cout << "Enter your Meau choice: ";
}
void mysign()
{
	cout << "Coding by Big handsome, USTB" << endl;
	cout << "                         Bonjour!\n";
	cout << "________________________________________________________________________";
}
int main() 
{
	mysign();
	long long number;
	string expression1, expression2,mixexpression;
	Calculator* cal = new ArithmeticCal;
	TrigonometricMenu* ca2 = new TrigonometricMenu;
	PowerMenu* ca3 = new PowerMenu;
	MoreTools test(expression1, expression2);
	int choice1;
	while(true)
	{
		printMainMenu();
		cin >> choice1;
		if(choice1==1)
			cal->Menu(cal);
		if (choice1 == 2)
			ca2->Menu(ca2);
		if (choice1 == 3)
			ca3->Menu(ca3);
		if (choice1 == 4)
		{
			test.PrintMenu();
			test.GetExpression();
			cout << endl;
			cout << "Add Answer:";
			test.GetLargeAdd();
			cout << "Multiply Answer:";
			test.GetLargeMultiply();
		}
		if (choice1 == 5)
		{
			cout << "Input an INTEGER:";
			cin >> number;
			Binary Bin(number);
			cout << "Binary Result is:" << Bin.GetBinary(number) << endl;
		}
		if (choice1 == 6)
		{
			cout << "Input a mix expression:";
			cin >> mixexpression;
			MixCalculate mixcalculator(mixexpression);
			mixcalculator.getResult();
		}
		if(choice1>6||choice1<0)
		{
			cout << "Invaild choice! Check menu again!" << endl;
			printMainMenu();
		}
		if (choice1 == 0) break;
	}
	return 0;
}