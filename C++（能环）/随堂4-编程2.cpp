#include<iostream>
using namespace std;
int main()
{
   int row,count,space,line_space;
   cin>>row>>count>>space>>line_space;
   int flag=1;          //��ǵڼ��е�8���ڴ�ӡ 
   int myline;          //���ÿ�е�8��ӡ���˵ڼ��� 
   while(flag<=row)
   {
      myline=1;        //���ÿ��8����
	  while(myline<=7)
	  {
	    if(myline%3==1)      //8�ĶԳƹ�ϵ����1,4,7��һ������2,3,5,6��һ��
		{
		  for(int j=0;j<count;j++)
		  {
		  cout<<"_###_";
		  for(int i=0;i<space;i++)
		  cout<<"_";
		} 
		cout<<"\n";
		myline++;
		}
		else
		{
		for(int j=0;j<count;j++)
		{
		cout<<"#___#";
		for(int i=0;i<space;i++)
		cout<<"_";
		} 
		cout<<"\n";
		myline++;
		}
	}                                    //��һ��8��ӡ��� 
	for(int i=0;i<line_space;i++)
	cout<<"\n";                          //��ӡ���� 
	flag++;                              //��������ӡ�ڶ���
	myline=1;                            //myline��0 
   } 
}


