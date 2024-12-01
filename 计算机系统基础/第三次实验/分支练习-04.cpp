#include <iostream>
using namespace std;

/*
piecewiseFunction(long x):
# 输入 x in %rdi
# 输出 %rax, %eax是%rax的低32位
        leaq    10(%rdi), %rax
        cmpq    $42, %rax				# 比较指令，计算Reg[rax]-42
        ja      .L3					# 无符号比较，如果大于则跳转
        leaq    (%rdi,%rdi,2), %rax
        ret
.L3:
        movl    $0, %eax				# Reg[rax]=-1
        ret
*/

long piecewiseFunction(long x)
{
    if((x<-10 )||(x>42))
        return 0;
    else
        return 3*x;
}

int main()
{
   long x;
  cin >> x;
  cout << piecewiseFunction(x) << endl;
  return 0;
}

