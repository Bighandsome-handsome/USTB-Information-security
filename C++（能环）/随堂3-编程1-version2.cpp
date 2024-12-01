/*
�û�����һ�����ڣ������տո�ָ����ж����Ǹ��������еĵڼ��졣
    I�� ����ո�ָ���xxxx xx xx�����磺2024 3 10��
    P���ж����Ǹ��������еĵڼ��졣
    O�������ʽΪ����/365���� ��/366���� ���磺70/366��
*/
#include<iostream>
using namespace std;
class GetDay
{
	int year,month,day;
public:
	GetDay(int year,int month,int day)
	{
		this->day=day;
		this->month=month;
		this->year=year;
	}
	bool isLeapYear()
	{
		if((year%4==0&&year%100!=0)||year%400==0) return true;
		else  return false;
	} 
	int CountDay()
	{
		int count=0;
		int daysInMonth[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
		for(int i=0;i<month;i++)
		count+=daysInMonth[i];
		if(isLeapYear())
		{
			if(month>2) count++;
		}
		return count+=day;
	}
	void print()
	{
		cout<<CountDay()<<"/";
		if(isLeapYear()) cout<<"366";
		else             cout<<"365";
	}
};
int main()
{
	int year,month,day;
	cin>>year>>month>>day;
	GetDay get(year,month,day);
	get.print(); 
}
