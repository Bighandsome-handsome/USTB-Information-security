#include <iostream>
using namespace std;


//fun(long, long, long):
//        leaq    (%rdi,%rdi,2), %rax
//        leaq    (%rsi,%rsi,2), %rcx
//        leaq    (%rax,%rcx,2), %rax
//        leaq    (%rdx,%rdx,4), %rdx
//        addq    %rdx, %rax
//        ret
long fun(long x, long y, long z)
{
    long output =(3*x+6*y)+5*z;
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

