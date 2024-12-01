#include <iostream>
using namespace std;


//fun(long, long, long):
//        leaq    (%rdi,%rdi,2), %rax
//        leaq    (%rsi,%rsi,4), %rdx
//        addq    %rdx, %rax
//        ret
long fun(long x, long y, long z)
{
    long output=x+x+x+y+y+y+y+y;
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

