/*
������⡿
�Ӽ���������nλ��������ʹ��ѭ���ṹ����������λ����
(ÿ�����ֺ����һ���ո�)��ͬʱ�����λ����֮�͡�
���룺123
�����
3 2 1
6
*/
#include<iostream>
using namespace std;
int main()
{
   int number,sum=0;
   cin>>number;
   while(number)
   {
      cout<<number%10<<" ";
	  sum+=number%10;
	  number=number/10;
   }
   cout<<"\n";
   cout<<sum;
}
