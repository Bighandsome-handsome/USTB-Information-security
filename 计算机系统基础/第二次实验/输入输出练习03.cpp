#include <iostream>
using namespace std;


// fun(long, long, long):
//        movq    (%rsi), %rax
//        ret
long fun(long *x, long *y, long *z)
{
      long output = *y;
      return output;
}

int main(int argc, char** argv)
{
       long x, y, z, output;
        cin >> x >> y >> z >> output;

        if( fun(&x,&y,&z)==output)
            cout << "Pass." << endl;
        else
            cout << "No Pass." << endl;
}


