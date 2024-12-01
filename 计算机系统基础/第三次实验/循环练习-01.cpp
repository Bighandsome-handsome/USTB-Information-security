#include <iostream>
using namespace std;

/*
collatzConjecture(unsigned long x):
# 输入：一维数组x in %rdi, %dil是的%rdi低8位
# 输出：%rax, %eax是%rax的低32位
        movl    $0, %eax         # Reg[rax]=0
        jmp     .L2                    # 无条件跳转
.L3:
        shrq    %rdi                 # Reg[rdi]=Reg[rdi]>>1
.L4:
        addq    $1, %rax         # Reg[rax]=Reg[rax]+1
.L2:
        cmpq    $1, %rdi         # Reg[rdi]-1
        je      .L6                     # 相等，则跳转
        testb   $1, %dil           # Reg[dil] & 0x1
        je      .L3	                   # 等于0，则跳转
        leaq    1(%rdi,%rdi,2), %rdi
        jmp     .L4		   # 无条件跳转
.L6:
        ret*/
long collatzConjecture(unsigned long x)
{
    long step=0;
    while(x!=1)
    {
        if(x%2==1)
            x=3*x+1;
        else
            x=x/2;
        step=step+1;
    }
    return step;
}

int main()
{
    long x;
   cin >> x;
   cout << collatzConjecture(x) << endl;
   return 0;
}


