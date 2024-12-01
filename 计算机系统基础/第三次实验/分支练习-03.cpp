#include <iostream>
using namespace std;

/*
convertASCIItoNumber(char x):
# 输入 x in %rdi, %dil是%rdi的低8位, %edi是%rdi的低32位
# 输出 %rax，%al是%rax的低8位，%eax是%rax的低32位
# 
        leal    -48(%rdi), %eax
        cmpb    $9, %al                	# Reg[al]-9
        ja      .L3                     	# 无符号比较，如果大于则跳转
        movsbl  %dil, %edi 				# 有符号扩展, 对于非负数，
# Reg[rdi]=Reg[dil]
        leal    -48(%rdi), %eax  			
        ret
.L3:
        movl    $-1, %eax 					# Reg[eax]=-1	
        ret
*/

int convertASCIItoNumber(char x)
{
    if(( '0'<=x)&&(x<='9' ))
        return   x-48 ; 
    else
        return -1;
}

int main()
{
   char c;
   cin >> c;
   cout << convertASCIItoNumber(c) << endl;
   return 0;
}

