#include <iostream>
using namespace std;
long a[1000];
long n, m;


// 汇编代码
/*           
binarySearch(long, long, long):
# 输入：num in %rdi, left in %rsi, right in %rdx
# 输出：%rax
        movq    %rsi, %rax
.L3:
        cmpq    %rdx, %rax              # 比较，计算 Reg[rax]-Reg[rdx]
        jge     .L7                     # 大于等于，则跳转
        leaq    (%rax,%rdx), %rcx
        sarq    %rcx                    # Reg[rcx] = Reg[rcx] >> 1 (算术右移)
        cmpq    %rdi, a(,%rcx,8)        # 比较，计算 Mem[8*Reg[rcx]+a]-Reg[rdi]
        jl      .L8                     # 小于，则跳转
        movq    %rcx, %rdx
        jmp     .L3                     # 无条件跳转
.L8:
        leaq    1(%rcx), %rax
        jmp     .L3                     # 无条件跳转
.L7:
        cmpq    %rdi, a(,%rax,8)        # 比较，计算 Mem[8*Reg[rax]+a]-Reg[rdi]
        jne     .L9                     # 不等于，则跳转
        ret
.L9:
        movq    $-1, %rax
        ret
*/
long binarySearch(long num, long left, long right){
    while(left < right){
        long mid = (left + right) >> 1;
        if (a[mid] < num){
            left = mid+1;
        }else{
            right = mid;
        }
    }
    if (a[left] == num)
        return left;
    return -1;
}

int main(){
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    long num;
    for (int i = 0; i < m; i++){
        cin >> num;
        cout << binarySearch(num, 0, n-1) << endl;
    }
    return 0;
}

