#include <iostream>  
#include <stack>  
#include <sstream>  
#include <cctype>  
  
using namespace std;  
  
// 函数用于检查是否是运算符  
bool isOperator(char c) {  
    return c == '+' || c == '-' || c == '*' || c == '/';  
}  
  
// 函数用于比较运算符的优先级  
int precedence(char op) {  
    if (op == '*' || op == '/') return 2;  
    if (op == '+' || op == '-') return 1;  
    return 0;  
}  
  
// 函数用于应用运算符到两个数上  
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
        // 跳过空格  
        if (isspace(expression[i])) {  
            ++i;  
            continue;  
        }  
  
        // 如果是一个数字，则解析整个数字  
        if (isdigit(expression[i])) {  
            int val = 0;  
            while (i < expression.length() && isdigit(expression[i])) {  
                val = val * 10 + (expression[i] - '0');  
                ++i;  
            }  
            values.push(val);  
        }  
        // 如果是一个运算符  
        else if (isOperator(expression[i])) {  
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {  
                int val2 = values.top(); values.pop();  
                int val1 = values.top(); values.pop();  
                char op = ops.top(); ops.pop();  
                values.push(applyOp(val1, val2, op));  
            }  
            ops.push(expression[i++]);  
        }  
        // 如果是一个左括号，则压入栈  
        else if (expression[i] == '(') {  
            ops.push(expression[i++]);  
        }  
        // 如果是一个右括号，则执行直到遇到左括号  
        else if (expression[i] == ')') {  
            while (!ops.empty() && ops.top() != '(') {  
                int val2 = values.top(); values.pop();  
                int val1 = values.top(); values.pop();  
                char op = ops.top(); ops.pop();  
                values.push(applyOp(val1, val2, op));  
            }  
            if (!ops.empty()) ops.pop(); // 弹出左括号  
            ++i;  
        }  
        else {  
            cerr << "Invalid character: " << expression[i] << endl;  
            return 1;  
        }  
    }  
  
    // 将剩余的操作应用到栈中的值上  
    while (!ops.empty()) {  
        int val2 = values.top(); values.pop();  
        int val1 = values.top(); values.pop();  
        char op = ops.top(); ops.pop();  
        values.push(applyOp(val1, val2, op));  
    }  
  
    // 栈中剩下的就是结果  
    cout << values.top() << endl;  
    return 0;  
}
