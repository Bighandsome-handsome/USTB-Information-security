#include <iostream>
using namespace std;

const unsigned long MAXLENGTH = 128;
unsigned long stack[MAXLENGTH];

/*===================================
push(long &, unsigned long):
# 输入： &top_pointer in %rdi, e in %rsi
# 返回： %rax: 成功返回1; 失败返回0。
    movq    (%rdi), %rax
    testq   %rax, %rax			  # Reg[rax] & Reg[rax]
    je      .L3					  # 为0，则跳转
    subq    $1, %rax			  # Reg[rax] = Reg[rax] - 1
    movq    %rax, (%rdi)          
    movq    %rsi, stack(,%rax,8)
    movl    $1, %eax              # Reg[rax] = 1
    ret
.L3:
    movl    $0, %eax			  # Reg[rax] = 0
    ret
==================================*/

bool push(long &top_pointer, unsigned long e)
{
    if(top_pointer ==0)
        return false;
    
    // 请根据汇编代码，实现push操作，完成C++代码。
     if(top_pointer!=0)
            {
    	top_pointer--;
           stack[top_pointer]=e;
            }

    return true;
}

/*===================================
pop(long &, unsigned long &):
# 输入： &top_pointer in %rdi, &e in %rsi
# 返回： %rax: 成功返回1; 失败返回0。
    movq    (%rdi), %rax
    cmpq    $127, %rax			  # 比较, Reg[rax]-127
                                  # 127=MAXLENGTH-1
    je      .L6					  # 相等, 则跳转
    movq    stack(,%rax,8), %rdx
    movq    %rax, (%rsi)
    movq    (%rdi), %rax
    addq    $1, %rax              # Reg[rax]=Reg[rax]+1
    movq    %rax, (%rdi)
    movl    $1, %eax              # Reg[rax]=1
    ret
.L6:
    movl    $0, %eax              # Reg[rax]=0
    ret
==================================*/

bool pop(long &top_pointer, unsigned long &e)
{
    if(top_pointer == MAXLENGTH-1)
       return false;
    
    // 请根据汇编代码，实现pop操作，完成C++代码。
     else
            {
            e=stack[top_pointer];
    	top_pointer++;
            }

    return true;
}

int main()
{
    long top_pointer = MAXLENGTH-1;
    unsigned long e;
    int n;
    cin >> n;
    
    int i=0;
    char op; // ’i' for push, 'o' for pop
    unsigned long ie;
    bool success;

    while(i<n)
    {
        cin >> op;
        switch(op)  //push
        {
               case 'i': // push
                            cin >> ie;
                            success = push(top_pointer, ie);
                            break;
               case 'o': // pop
                            success = pop(top_pointer, e);
                            cout << e << endl;
                            break;
                default:    success = false;
         }
    
       if(success)
           i++;
       else
       {
           cout << "segmentation fault." << endl;
           break;
       }
    }
    
    return 0;
}

