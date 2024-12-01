#include <iostream>  
#include <stack>  
#include <sstream>  
#include <cctype>  
  
using namespace std;  
  
// �������ڼ���Ƿ��������  
bool isOperator(char c) {  
    return c == '+' || c == '-' || c == '*' || c == '/';  
}  
  
// �������ڱȽ�����������ȼ�  
int precedence(char op) {  
    if (op == '*' || op == '/') return 2;  
    if (op == '+' || op == '-') return 1;  
    return 0;  
}  
  
// ��������Ӧ�����������������  
int applyOp(int a, int b, char op) {  
    switch (op) {  
        case '+': return a + b;  
        case '-': return a - b;  
        case '*': return a * b;  
        case '/': if (b != 0) return a / b;  
                  else { cerr << "Error: Division by zero" << endl; return 0; }  
    }  
    return 0;  
}  
  
int main() {  
    string expression;  
    getline(cin, expression);  
      
    stack<int> values;  
    stack<char> ops;  
      
    for (size_t i = 0; i < expression.length();) {  
        // �����ո�  
        if (isspace(expression[i])) {  
            ++i;  
            continue;  
        }  
  
        // �����һ�����֣��������������  
        if (isdigit(expression[i])) {  
            int val = 0;  
            while (i < expression.length() && isdigit(expression[i])) {  
                val = val * 10 + (expression[i] - '0');  
                ++i;  
            }  
            values.push(val);  
        }  
        // �����һ�������  
        else if (isOperator(expression[i])) {  
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {  
                int val2 = values.top(); values.pop();  
                int val1 = values.top(); values.pop();  
                char op = ops.top(); ops.pop();  
                values.push(applyOp(val1, val2, op));  
            }  
            ops.push(expression[i++]);  
        }  
        // �����һ�������ţ���ѹ��ջ  
        else if (expression[i] == '(') {  
            ops.push(expression[i++]);  
        }  
        // �����һ�������ţ���ִ��ֱ������������  
        else if (expression[i] == ')') {  
            while (!ops.empty() && ops.top() != '(') {  
                int val2 = values.top(); values.pop();  
                int val1 = values.top(); values.pop();  
                char op = ops.top(); ops.pop();  
                values.push(applyOp(val1, val2, op));  
            }  
            if (!ops.empty()) ops.pop(); // ����������  
            ++i;  
        }  
        else {  
            cerr << "Invalid character: " << expression[i] << endl;  
            return 1;  
        }  
    }  
  
    // ��ʣ��Ĳ���Ӧ�õ�ջ�е�ֵ��  
    while (!ops.empty()) {  
        int val2 = values.top(); values.pop();  
        int val1 = values.top(); values.pop();  
        char op = ops.top(); ops.pop();  
        values.push(applyOp(val1, val2, op));  
    }  
  
    // ջ��ʣ�µľ��ǽ��  
    cout << values.top() << endl;  
    return 0;  
}
