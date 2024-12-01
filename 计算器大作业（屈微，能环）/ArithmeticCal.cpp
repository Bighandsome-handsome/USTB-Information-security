#include "ArithmeticCal.h"
#include <iostream>
#include "Add.h"               //调入加、减、乘、除四个类的头文件
#include"Sub.h"
#include"Multiply.h"
#include"Divide.h"
#include "Stack.h"
using namespace std;
void ArithmeticCal::Input()                
//这是获取计算数值的接口，通过用户输入两个操作数
{
	cout << "\nEnter first number: ";
	cin >> num1;
	cout << "Enter second number: ";
	cin >> num2;
}
void ArithmeticCal::Menu(Calculator* pCal) 
{
	Stack s;              //定义了一个stack对象s，将计算结果储存在s（本质上是栈堆）中
	int choice2;          //下面是一个菜单
	do {
		// MENU
		cout << "\n\n\t1. Enter 10 to add";
		cout << "\n\t2. Enter 11 to subtract";
		cout << "\n\t3. Enter 12 to multiply";
		cout << "\n\t4. Enter 13 to divide";
		cout << "\n\t5. Enter 14 to show previous result";
		cout << "\n\t6. Enter 0 to return to main menu\n";
		cout << "\nEnter your ArithmeticCal choice: ";
		cin >> choice2;
		switch (choice2) 
		{
		case 10:
			pCal = new Add;                   //这是调用加法类，实现两个数的相加
			pCal->Input();                    //指针指向加法Add类的输入函数
			cout << "Result: " << pCal->calculate() << endl;
			s.push(pCal->calculate());       //用栈的压栈(push)函数将结果压入栈中
			break;
		case 11:
			pCal = new Sub;
			pCal->Input();
			cout << "Result: " << pCal->calculate() << endl;
			s.push(pCal->calculate());
			break;
		case 12:
			pCal = new Multiply;
			pCal->Input();
			cout << "Result: " << pCal->calculate() << endl;
			s.push(pCal->calculate());
			break;
		case 13:
			pCal = new Divide;
			pCal->Input();
			cout << "Result: " << pCal->calculate() << endl;
			s.push(pCal->calculate());
			break;
		case 14:
			cout << "Previous result: " << s.Top() << endl; /* Here we are printing the previous result stored in the array... */
			break;
		}
	} while (choice2 >= 10 && choice2 <= 14);
}