/*
���������Ա�̼���123���123�ĸ�λ���룺
int a=123;
cout<<n/10/10%10<<n/10%10<<n%10<<endl;
�밴������Ĺ��ɣ���д����������ʮ����97��16���ơ�8���ơ�2���ơ� 
*/
//Version 1.0 
#include<iostream>
using namespace std;
int main()
{
   int n=97;
   cout<<n/16%16;
   cout<<n%16<<endl;
   cout<<n/8/8%8;
   cout<<n/8%8;
   cout<<n%8<<endl;
   cout<<n/2/2/2/2/2/2/2%2;
   cout<<n/2/2/2/2/2/2%2;
   cout<<n/2/2/2/2/2%2;
   cout<<n/2/2/2/2%2;
   cout<<n/2/2/2%2;
   cout<<n/2/2%2;
   cout<<n/2%2;
   cout<<n%2<<endl;
}
