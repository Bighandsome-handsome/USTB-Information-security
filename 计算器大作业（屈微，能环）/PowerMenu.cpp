#include "PowerMenu.h"
#include "Stack.h"
#include<cmath>
#include<iostream>
using namespace std;
void PowerMenu::Input()
//���ǻ�ȡ������ֵ�Ľӿڣ�ͨ���û���������������
{
	cout << "Attention: IF YOU want to get sqrt or Cuberoot,Input 0 AS NUMBER 2.";
	cout << "\nEnter number 1: ";
	cin >> number1;
	cout << "\nEnter number 2: ";
	cin >> number2;
}
void  PowerMenu::Menu(Calculator* pCal)
{
	Stack s;              //������һ��stack����s����������������s����������ջ�ѣ���
	int choice4;          //������һ���˵�
	do {
		// MENU
		cout << "\n\n\t1. Enter 10 to get SQRT";
		cout << "\n\t2. Enter 11 to get POW";
		cout << "\n\t3. Enter 12 to get CUBEROOT";
		cout << "\n\t4. Enter 13 to show previous result";
		cout << "\n\t5. Enter 0 to return to main menu\n";
		cout << "\nEnter your ArithmeticCal choice: ";
		cin >> choice4;
		switch (choice4)
		{
		case 10:
			pCal = new GetSqrt;
			pCal->Input();
			cout << "Result: " << pCal->calculate() << endl;
			s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
			break;
		case 11:
			pCal = new GetPow;
			pCal->Input();
			cout << "Result: " << pCal->calculate() << endl;
			s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
			break;
		case 12:
			pCal = new GetCube;
			pCal->Input();
			cout << "Result: " << pCal->calculate() << endl;
			s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
			break;
		case 13:
			cout << "Previous result: " << s.Top() << endl; /* Here we are printing the previous result stored in the array... */
			break;
		}
	} while (choice4 >= 10 && choice4 <= 13);
}