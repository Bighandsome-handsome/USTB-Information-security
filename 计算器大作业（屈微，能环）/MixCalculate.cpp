#include "MixCalculate.h"
using namespace std;
MixCalculate::MixCalculate(string expression)
{
    this->expression = expression; 
}
bool MixCalculate::isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}
int MixCalculate::precedence(char op)
{
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}
int MixCalculate::applyOp(int a, int b, char op)
{
    switch (op) 
    {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': if (b != 0) return a / b;
            else { cerr << "Error: Division by zero" << endl; return 0; }
    }
    return 0;
}
void MixCalculate::getResult()
{
    stack<int> values;
    stack<char> ops;
    for (size_t i = 0; i < expression.length();) 
    {
        // �����ո�  
        if (isspace(expression[i])) 
        {
            ++i;
            continue;
        }
        // �����һ�����֣��������������  
        if (isdigit(expression[i])) 
        {
            int val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = val * 10 + (expression[i] - '0');
                ++i;
            }
            values.push(val);
        }
        // �����һ�������  
        else if (isOperator(expression[i])) 
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i++]);
        }
        // �����һ�������ţ���ѹ��ջ  
        else if (expression[i] == '(') 
        {
            ops.push(expression[i++]);
        }
        // �����һ�������ţ���ִ��ֱ������������  
        else if (expression[i] == ')') 
        {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty()) ops.pop(); // ����������  
            ++i;
        }
        else 
        {
            cerr << "Invalid character: " << expression[i] << endl;
        }
    }

    // ��ʣ��Ĳ���Ӧ�õ�ջ�е�ֵ��  
    while (!ops.empty()) {
        if (values.size() < 2) {
            cerr << "Error: Insufficient values in stack." << endl;
            break; // ���߿����׳��쳣  
        }
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    // ȷ��ջ��ֻ��һ��ֵ  
    if (values.size() == 1) 
    {
        cout << "Result:"<<values.top() << endl; // ע������ʹ���� values.top() ������ values.top  
    }
    else 
    {
        cerr << "Error: Stack should contain exactly one value after calculation." << endl;
    }
}