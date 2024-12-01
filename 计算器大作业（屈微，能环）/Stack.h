#pragma once

class Stack {
    double arr[100];             //100个元素构成的数组，储存每次计算的结果(float类型)
    int top;                    //一个int类型的数据起到了栈顶指针的作用
public:
    Stack();                     //构造函数
    void push(double x);          //这是将计算结果x压入（存储）到栈（即arr）中
    void pop();                  //这是用于从栈中弹出并丢弃栈顶元素
    double Top();                 //用于返回（即输出）栈顶的元素值但是不移除
};
