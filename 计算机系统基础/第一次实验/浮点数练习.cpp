#include <iostream>
using namespace std;

//测试用例1： 填空，使得函数返回true
bool test01_assertSame(){
    float x =  2e10;
    bool isSame = (x==x+1);
    return isSame;
}

//测试用例2： 填空，使得函数返回true
bool test02_assertSame(){
   float x =  0.0/0;
   bool isSame = (x!=x);
   return isSame;
}

//测试用例3： 填空，使得函数返回true 
bool test03_assertSame(){
    float x = 0.00;
    return (x==-x);
}

//测试用例4： 填空，使得函数返回true
bool test04_assertSame(){
    float x =  0.1+0.2;
    bool isSame = (x==x-1e-100);
    return isSame;
}

//测试用例5： 填空，使得函数返回true
bool test05_assertTrue(){
    int a = 1024;
    float x =  a + 0.6;
    bool isSame = ((int)x==1024);
    return isSame;
}

// 依次测试五个用例，测试用例正确则输出 Pass. 代码不用读懂。
int main(int argc,char** argv)
{
    bool test[5]={test01_assertSame(),test02_assertSame(),test03_assertSame(),test04_assertSame(),test05_assertTrue()};
    
    int testId = argv[1][0]-'1';
    if(test[testId])
       cout << "Pass." << endl;
    else
        cout << "No Pass." << endl;
    return 0;
}

