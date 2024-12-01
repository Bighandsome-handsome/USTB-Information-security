#include <iostream>
using namespace std;

long globalArray[5] = {123,245,456,897,897};


// fun(long, long, long):
//       movq    globalArray(,%rdi,8), %rax
//       ret
long fun(long x, long y, long z)
{
      long output =  globalArray[x];
      return output;
}

int main(int argc, char** argv)
{
       long x, y, z, output;
        cin >> x >> y >> z >> output;

        if( fun(x,y,z)==output)
            cout << "Pass." << endl;
        else
            cout << "No Pass." << endl;
}

