#include "TrigonometricMenu.h"
#include "Stack.h"
#include<cmath>
#include<iostream>
using namespace std;
void TrigonometricMenu::Input()
//���ǻ�ȡ������ֵ�Ľӿڣ�ͨ���û���������������
{
	cout<<"\nEnter number: ";  
	cin >> number;
}
void TrigonometricMenu::Menu(Calculator* pCal)
{
      Stack s;              //������һ��stack����s����������������s����������ջ�ѣ���
      int choice3;          //������һ���˵�
    do {
	    // MENU
	     cout << "\n\n\t1. Enter 10 to get sin(number)";
	     cout << "\n\t2. Enter 11 to get cos(number)";
	     cout << "\n\t3. Enter 12 to get tan(number)";
	     cout << "\n\t4. Enter 13 to get csc(number)";
		 cout << "\n\t5. Enter 14 to get sec(number)";
		 cout << "\n\t6. Enter 15 to get cot(number)";
		 cout << "\n\t7. Enter 16 to get inverse(number)";
	     cout << "\n\t8. Enter 17 to show previous result";
	     cout << "\n\t9. Enter 0 to return to main menu\n";
	     cout << "\nEnter your ArithmeticCal choice: ";
	     cin >> choice3;
	switch (choice3)
	{
	case 10:
		pCal = new GetSin;
		pCal->Input();
		cout << "Result: " << pCal->calculate() << endl;
		s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
		break;
	case 11:
		pCal = new GetCos;
		pCal->Input();
		cout << "Result: " << pCal->calculate() << endl;
		s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
		break;
	case 12:
		pCal = new GetTan;
		pCal->Input();
		cout << "Result: " << pCal->calculate() << endl;
		s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
		break;
	case 13:
		pCal = new GetSec;
		pCal->Input();
		cout << "Result: " << pCal->calculate() << endl;
		s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
		break;
	case 14:
		pCal = new GetCot;
		pCal->Input();
		cout << "Result: " << pCal->calculate() << endl;
		s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
		break;
	case 15:
		pCal = new GetCsc;
		pCal->Input();
		cout << "Result: " << pCal->calculate() << endl;
		s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
		break;
	case 16:
		pCal = new GetInverse;
		pCal->Input();
		cout << "Result: " << pCal->calculate() << endl;
		s.push(pCal->calculate());       //��ջ��ѹջ(push)���������ѹ��ջ��
		break;
	case 17:
		cout << "Previous result: " << s.Top() << endl; /* Here we are printing the previous result stored in the array... */
		break;
	}
} while (choice3 >= 10 && choice3 <= 17);
}