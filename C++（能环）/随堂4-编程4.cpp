/*【编程题】百钱百鸡
现一只公鸡5元钱，一只母鸡3元钱，三只小鸡1元钱。  
给你一百元钱去买公鸡、母鸡、小鸡共一百只，问
你应当买多少只公鸡？多少只母鸡？多少只小鸡？
输入：无
输出：空格分隔公鸡，母鸡和小鸡只数分行输出若干组。
cocks:0 hens:25 chicken:75
*/

#include <iostream>
using namespace std;
int main()
{
    int x,y,z;
    for(int x=0;x<=20;x++)
    for(int y=0;y<=33;y++)
    for(int z=0;z<=300;z++)
        {
            if(z%3!=0) continue;
               else
                {
                    if(z/3+y*3+x*5==100&&x+y+z==100)
					 cout<<"cocks:"<<x<<" hens:"<<y<<" chicken:"<<z<<endl;
                }
        }
	return 0;
}
