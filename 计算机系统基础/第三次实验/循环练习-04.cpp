#include <iostream>
using namespace std;

/*
sum(long* a, long n):
# 输入：一维数组a in %rdi, 数组元素个数n in %rsi
# 输出：%rax, %eax是%rax的低32位
# 其他：%edx是%rdx的低32位
        testq   %rsi, %rsi				# Reg[rsi] & Reg[rsi]
        jle     .L4						# 有符号比较，小于等于跳转
        movq    %rdi, %rax
        leaq    (%rdi,%rsi,8), %rcx
        movl    $0, %edx				# Reg[rdx]=0
.L3:
        addq    (%rax), %rdx			# Reg[rdx]=Reg[rdx]+MEM[Reg[rax]]
        addq    $8, %rax				# Reg[rax]=Reg[rax]+8
        cmpq    %rcx, %rax				# Reg[rax]-Reg[rcx]
        jne     .L3
.L1:
        movq    %rdx, %rax
        ret
.L4:
        movl    $0, %edx				# Reg[rdx]=0
        jmp     .L1					# 无条件跳转
*/
long sum(long a[], long n)
{
    long sum=0;
    for(long i=0;  i<n; i++)
    {
        sum= sum+a[i];
    }
    return  sum ;
}

int main()
{
   long n;
   cin >> n;
   long *a = (long *)malloc(n*sizeof(long));
   for(int i=0;i<n;i++)
      cin >> a[i];
    
    cout<<sum(a,n)<<endl;
    return 0;
}


