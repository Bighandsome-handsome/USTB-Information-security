#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

/*
max(unsigned long* a, long n):
# 输入：一维数组a in %rdi, 数组元素个数n in %rsi
# 输出：%rax, %eax是%rax的低32位
# 其他：%ecx是%rcx的低32位
        movl    $0, %eax		# Reg[rax]=0
        movl    $0, %ecx		# Reg[ecx]=0
        jmp     .L2				# 无条件跳转
.L3:
        addq    $1, %rax		# Reg[rax]=Reg[rax]+1
.L2:
        cmpq    %rsi, %rax		# Reg[rax]-Reg[rsi]
        jge     .L6				# 有符号比较，大于等于则跳转
        movq    (%rdi,%rax,8), %rdx
        cmpq    %rdx, %rcx		# Reg[rcx]-Reg[rdx]
        jnb     .L3				# 无符号比较，不小于则跳转
        movq    %rdx, %rcx
        jmp     .L3				# 无条件跳转
.L6:
        movq    %rcx, %rax
        ret
*/ 

unsigned long max(unsigned long a[], long n)
{
    unsigned long maxValue = a[0];
    for(long i=0; i<n; i++)
    {
        if(maxValue < a[i]) // 填写比较运算符
            maxValue =a[i];
    }
    return maxValue;
}

int main()
{
   long n;
   cin >> n;
   unsigned long *a = (unsigned long *)malloc(n*sizeof(long));
   for(int i=0;i<n;i++)
      cin >> a[i];
    
    cout<<max(a,n)<<endl;
    return 0;
}


