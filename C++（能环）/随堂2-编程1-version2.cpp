/*
���������Ա�̼���123���123�ĸ�λ���룺
int a=123;
cout<<n/10/10%10<<n/10%10<<n%10<<endl;
�밴������Ĺ��ɣ���д����������ʮ����97��16���ơ�8���ơ�2���ơ� 
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
        remainder=number%transfer; // ������  
        // ����������ڵ���10��������Ҫ����ת��Ϊ'A'-'F'֮����ַ�  
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


