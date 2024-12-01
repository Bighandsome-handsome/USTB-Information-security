#include<iostream>
using namespace std;
int main()
{
   int row,count,space,line_space;
   cin>>row>>count>>space>>line_space;
   int flag=1;          //标记第几行的8正在打印 
   int myline;          //标记每行的8打印到了第几行 
   while(flag<=row)
   {
      myline=1;        //标记每个8的行
	  while(myline<=7)
	  {
	    if(myline%3==1)      //8的对称关系，第1,4,7行一样，第2,3,5,6行一样
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
	}                                    //第一行8打印完成 
	for(int i=0;i<line_space;i++)
	cout<<"\n";                          //打印换行 
	flag++;                              //自增，打印第二行
	myline=1;                            //myline归0 
   } 
}


