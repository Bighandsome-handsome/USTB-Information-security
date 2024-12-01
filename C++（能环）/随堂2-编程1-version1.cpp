/*
下面代码可以编程计算123输出123的各位数码：
int a=123;
cout<<n/10/10%10<<n/10%10<<n%10<<endl;
请按照上面的规律，编写程序计算输出十进制97的16进制、8进制、2进制。 
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
