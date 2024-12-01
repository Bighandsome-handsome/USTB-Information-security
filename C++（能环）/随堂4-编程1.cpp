/*
【编程题】参考下面代码，编写程序计算并输出
s =1/1!+ 1/2!+ … +1/ n!（注意以double类型存储）。
例：
输入：100
输出：s=1.71828
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
