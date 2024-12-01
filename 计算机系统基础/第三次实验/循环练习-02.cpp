#include <iostream>
using namespace std;

/*
long  search(long  *a,  long  n,  long  x)
# 输入：一维数组a in %rdi, 数组元素个数n in %rsi, 待查询元素x in %rdx
# 输出：%rax, %eax是%rax的低32位
       testq   %rsi, %rsi				# Reg[rsi] & Reg[rsi]
        jle     .L5						# 有符号比较，结果小于等于0则跳转
        movl    $0, %eax				# Reg[rax]=0
.L4:
        cmpq    %rdx, (%rdi,%rax,8)	# MEM[Reg[rdi]+8*Reg[rax]]-Reg[rdx]
        je      .L3						# 相等则跳转
        addq    $1, %rax				# Reg[rax]=Reg[rax]+1
        cmpq    %rax, %rsi				# Reg[rsi]-Reg[rax]
        jne     .L4						# 不相等则跳转
        movq    $-1, %rax
        ret
.L3:
        cmpq    %rax, %rsi				# Reg[rsi]-Reg[rax]
        jle     .L8						# 有符号比较，小于等于则跳转
        ret
.L5:
        movq    $-1, %rax
        ret
.L8:
        movq    $-1, %rax
        ret
*/

long search(long a[], long n, long x)
{ 
    long i=0;
    while(i<n)
    {
        if(x== a[i])
            break;
        i++;
    }

    if(i<n)
          return  i;
    else
           return -1;
}

int main()
{
   long  a[20] = {41,22,33,24,35,46,27,18,29,10,11,222,43,34,25,16,27,228,129,30};
   long n=20;
   long x;
   cin >> x;
   cout << search(a,n,x) << endl;
   return 0;
}


