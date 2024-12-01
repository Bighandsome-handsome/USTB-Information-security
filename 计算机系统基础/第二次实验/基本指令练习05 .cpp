#include <iostream>
using namespace std;
short a[3];

//fun(short):
//        movl    %edi, %eax
//        addw    a+2(%rip), %ax
//        ret
short fun(short x)
{
    int  output=x+a[1];
    return output;
}
int main(int argc, char** argv)
{
    short x, output;
    cin >> x >> a[0] >> a[1] >> a[2] >> output;

    if( fun(x)==output)
        cout << "Pass." << endl;
    else
        cout << "No Pass." << endl;
}

