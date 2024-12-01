#include <iostream>
using namespace std;

/*
relu(long x):
# 输入 x in %rdi
# 输出 %rax, %eax 是%rax的低32位
        movq    %rdi, %rax     
        testq   %rdi, %rdi 	# Reg[rdi] & Reg[rdi]
        js      .L3				# 负数，则跳转
        ret
.L3:
        movl    $0, %eax	    # Reg[rax]=0
        ret 
*/



long relu(long x)
{
    if(x <0)
        return 0;
    else
        return x;
}

int main()
{
   long x;
  cin >> x;
  cout << relu(x) << endl;
  return 0;
}


