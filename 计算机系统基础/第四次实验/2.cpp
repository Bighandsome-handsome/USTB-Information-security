#include <iostream>
using namespace std;

int p=0;
void move(char a, char c)
{
     p=p+1;
     // 可以使用下面的语句理解move的实际操作
     // printf("%d: %c-->%c\n",p,a,c);
}

// 汇编代码
/*
hanoi(long n, long a, long b, long c):
# 输入：n in %rdi, a in %rsi, b in %rdx, c in %rcx
# 输出：%rax
        pushq   %r13                                        # 保存 callee-saved 寄存器
        pushq   %r12                                        # 保存 callee-saved 寄存器
        pushq   %rbp                                        # 保存 callee-saved 寄存器
        pushq   %rbx                                        # 保存 callee-saved 寄存器
        subq    $8, %rsp                                 
        movq    %rsi, %r12
        movq    %rdx, %rbp
        cmpq    $1, %rdi                                   # 比较，计算 Reg[rdi]-1
        je      .L5                                               # 相等，则跳转
        movq    %rcx, %r13
        leaq    -1(%rdi), %rbx
        movq    %rdx, %rcx
        movq    %r13, %rdx
        movq    %rbx, %rdi
        call    hanoi(long, long, long, long)        # 调用 hanoi 函数
        movq    %rbp, %rsi
        movq    %r12, %rdi
        call    move(long, long)                          # 调用 move 函数
        movq    %r12, %rcx
        movq    %rbp, %rdx
        movq    %r13, %rsi
        movq    %rbx, %rdi
        call    hanoi(long, long, long, long)       # 调用 hanoi 函数
.L1:
        addq    $8, %rsp                                  
        popq    %rbx                                        # 恢复 callee-saved 寄存器
        popq    %rbp                                        # 恢复 callee-saved 寄存器
        popq    %r12                                        # 恢复 callee-saved 寄存器
        popq    %r13                                        # 恢复 callee-saved 寄存器
        ret
.L5:
        movq    %rdx, %rsi
        movq    %r12, %rdi
        call    move(long, long)                         # 调用 move 函数
        jmp     .L1                                              # 无条件跳转
*/


void hanoi(long n, long a, long b, long c)
{
    if(n==1)
    {    
        move(a,b);
        return;
    }

    hanoi( n-1,a,c,b);  // 请根据汇编代码，填写 hanoi 函数的输入参数
    move(a,b);
    hanoi( n-1,b,a,c); // 请根据汇编代码，填写 hanoi 函数的输入参数
}

int main()
{
    int n;
    cin >>n;
    hanoi(n,'a','b','c');
    cout << p << endl;
    return 0;
}

