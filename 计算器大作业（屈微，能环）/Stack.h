#pragma once

class Stack {
    double arr[100];             //100��Ԫ�ع��ɵ����飬����ÿ�μ���Ľ��(float����)
    int top;                    //һ��int���͵���������ջ��ָ�������
public:
    Stack();                     //���캯��
    void push(double x);          //���ǽ�������xѹ�루�洢����ջ����arr����
    void pop();                  //�������ڴ�ջ�е���������ջ��Ԫ��
    double Top();                 //���ڷ��أ��������ջ����Ԫ��ֵ���ǲ��Ƴ�
};
