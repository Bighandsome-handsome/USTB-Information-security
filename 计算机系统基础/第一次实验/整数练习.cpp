#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	long long number,time,result[10]; 
	long long n,i,operation;
	cin>>number>>time;
	i=0;
	while(i<time)
	{
		cin>>operation>>n;
		if(!operation) number+=n;
		else           number=fabs(number-n);
		result[i]=number;    
		i++;     
	}
	for(i=0;i<time;i++) 
	cout<<result[i]<<endl;
	return 0;
}






