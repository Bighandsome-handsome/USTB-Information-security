/*
用户输入一个日期，年月日空格分隔，判断其是该年天数中的第几天。
    I： 输入空格分隔：xxxx xx xx，例如：2024 3 10。
    P：判断其是该年天数中的第几天。
    O：输出格式为：？/365（或 ？/366）， 例如：70/366。
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


