/*
������⡿�ο�������룬��д������㲢���
s =1/1!+ 1/2!+ �� +1/ n!��ע����double���ʹ洢����
����
���룺100
�����s=1.71828
*/
#include <iostream>
using namespace std;
int main()
{ 
    int i,n;
	double s=0,p=1;
	cin >> n;
	for(i=1; i<=n; i++)
	{
	p=p*(1.0/i);
	s=s+p;
	}
    cout<<"s="<<s;
	return 0; 
}
