/*
�û�����һ�����ڣ������տո�ָ����ж����Ǹ��������еĵڼ��졣
    I�� ����ո�ָ���xxxx xx xx�����磺2024 3 10��
    P���ж����Ǹ��������еĵڼ��졣
    O�������ʽΪ����/365���� ��/366���� ���磺70/366��
*/
#include <iostream>
using namespace std;
int main()
{
   int nian, yue, ri, days, a;
   cin >> nian >> yue >> ri;
   days = 0;
   switch (yue - 1)
   {
   case 11: days += 30; 
   case 10: days += 31;
   case 9: days += 30;
   case 8: days += 31;
   case 7: days += 31;
   case 6: days += 30;
   case 5: days += 31;
   case 4: days += 30;
   case 3: days += 31;
   case 2: days += ((nian % 4 == 0 && nian % 100 != 0) || nian % 400 == 0 ? 29 : 28);
   case 1: days += 31;
   case 0: break;
}
((nian % 4 == 0 && nian % 100 != 0) || nian % 400 == 0)?( a = 366):( a = 365);
days += ri;
cout << days << "/"<< a<<endl;
return 0;
}


