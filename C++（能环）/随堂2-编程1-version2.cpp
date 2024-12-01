/*
下面代码可以编程计算123输出123的各位数码：
int a=123;
cout<<n/10/10%10<<n/10%10<<n%10<<endl;
请按照上面的规律，编写程序计算输出十进制97的16进制、8进制、2进制。 
*/
//Version 2.0 
#include<iostream>
#include<string>
#include<cstring>
#include<string.h>
#include<algorithm>
using namespace std;
class Solution
{
private:
	int number;
	int transfer;
public:
	Solution(int number,int transfer)
	{
		this->number=number;
		this->transfer=transfer;
	}
	string GetAnswer()
    {  
    if (number==0)   return "0"; 
    string result="";  
    int remainder;  
    while (number!=0) 
	{  
        remainder=number%transfer; // 求余数  
        // 如果余数大于等于10，我们需要将其转换为'A'-'F'之间的字符  
        if(remainder<10) 
		result+=(remainder+'0'); 
        else 
        result += (remainder - 10 + 'A');   
        number=number/transfer; 
    }  
    std::reverse(result.begin(), result.end());  
    return result;
	}
};
int main()
{
	Solution s1(97,16);
	Solution s2(97,8);
	Solution s3(97,2);
	cout<<s1.GetAnswer()<<endl;
	cout<<s2.GetAnswer()<<endl;
	cout<<"0"+s3.GetAnswer()<<endl;
}


