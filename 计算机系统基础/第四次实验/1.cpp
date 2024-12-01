#include <iostream>
using namespace std;

/*
gcd(long a, long b):
# 输入：a in %rdi, b in %rsi
# 输出：%rax
        movq    %rsi, %rax
        cmpq    %rsi, %rdi           # 比较, 计算Reg[rdi]-Reg[rsi]
        jl      .L2                           # 有符号比较，小于则跳转
        movq    %rdi, %rax
        movq    %rsi, %rdi
.L2:
        testq   %rdi, %rdi            # Reg[rdi] & Reg[rdi]
        jne     .L8                        # 不为0，则跳转
        ret
.L8:
        subq    $8, %rsp             
        subq    %rdi, %rax          # Reg[rax] = Reg[rax] - Reg[rdi]
        movq    %rax, %rsi   
        call    gcd(long, long)      # 调用 gcd
        addq    $8, %rsp
        ret
*/

long gcd(long a, long b)
{
    if(a<b)
    {
        long t=a;
        a=b;
        b=t;
    }

    if(b==0)
        return a;
    else
        return gcd(a-b,b);        //请根据汇编代码，填写gcd函数的输入参数
}

int main()
{
    long a, b;
    cin >> a >> b;
    
    cout << gcd(a,b) << endl;
    return 0;

}

