/*������⡿��Ǯ�ټ�
��һֻ����5ԪǮ��һֻĸ��3ԪǮ����ֻС��1ԪǮ��  
����һ��ԪǮȥ�򹫼���ĸ����С����һ��ֻ����
��Ӧ�������ֻ����������ֻĸ��������ֻС����
���룺��
������ո�ָ�������ĸ����С��ֻ��������������顣
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
