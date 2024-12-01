#include <iostream>
using namespace std;

/*
swapOnCondition(long* xp, long* yp):
# 输入 xp in %rdi, yp in %rsi
# 输出 %rax, %eax是%rax的低32位。
        movq    (%rdi), %rax
        movq    (%rsi), %rdx
        cmpq    $9, %rax			# Reg[rax]-9
        jg      .L3					# 有符号比较，大于则跳转
        cmpq    $5, %rdx			# Reg[rdx]-5
        jle     .L3					# 有符号比较，小于等于则跳转
        movq    %rdx, (%rdi)
        movq    %rax, (%rsi)
        movl    $1, %eax			# Reg[rax]=1
        ret
.L3:
        movl    $0, %eax			# Reg[rax]=0
        ret
*/

long swapOnCondition(long *xp, long *yp)
{
    long x=*xp;
    long y=*yp;

    if(x<10  && y>5) // 填写逻辑运算符
    {
        *xp= y;
        *yp=x;
        return 1;
    }
    return 0;
}

int main()
{
   long x,y;
   cin >> x >> y;
   cout<<swapOnCondition(&x,&y)<<endl;
  cout<<x<<endl;
  cout<<y<<endl;
  return 0;
}

