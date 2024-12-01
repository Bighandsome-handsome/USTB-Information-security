#include "ArithmeticCal.h"
#include <iostream>
#include "Add.h"               //����ӡ������ˡ����ĸ����ͷ�ļ�
#include"Sub.h"
#include"Multiply.h"
#include"Divide.h"
#include "Stack.h"
using namespace std;
void ArithmeticCal::Input()                
//���ǻ�ȡ������ֵ�Ľӿڣ�ͨ���û���������������
{
	cout << "\nEnter first number: ";
	cin >> num1;
	cout << "Enter second number: ";
	cin >> num2;
}
void ArithmeticCal::Menu(Calculator* pCal) 
{
	Stack s;              //������һ��stack����s����������������s����������ջ�ѣ���
	int choice2;          //������һ���˵�
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
			pCal = new Add;                   //���ǵ��üӷ��࣬ʵ�������������
			pCal->Input();                    //ָ��ָ��ӷ�Add������뺯��
			cout << "Result: " << pCal->calculate() << endl;
			s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
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