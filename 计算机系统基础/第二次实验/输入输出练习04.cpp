#include <iostream>
using namespace std;

// 请根据汇编代码，填补C代码缺失的表达式。
// fun(long, long, long):
//        movq    %edi, %eax
//        ret
int fun(int x,int y,int z)
{
      int output = x;
      return output;
}

int main(int argc, char** argv)
{
       int x, y, z, output;
        cin >> x >> y >> z >> output;

        if( fun(x,y,z)==output)
            cout << "Pass." << endl;
        else
            cout << "No Pass." << endl;
}

