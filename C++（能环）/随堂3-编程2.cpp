/*
【编程题】
从键盘上输入n位数整数，使用循环结构逆序输出其各位数字
(每个数字后输出一个空格)，同时求出各位数字之和。
输入：123
输出：
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
