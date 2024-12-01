#include "MoreTools.h"
#include"iostream"
#include"algorithm"
using namespace std;
MoreTools::MoreTools(string expression1, string expression2)
{
    this->expression1 = expression1;
    this->expression2 = expression2;
}
int MoreTools::read_str(string str, int* a)
{
    int n = str.length();
    for (int i = 0; i < n; ++i)
    {
        a[i] = str[n - i - 1] - '0';
    }
    return n;
}
void MoreTools::GetLargeMultiply()
{
    int a[maxn2] = { 0 }, b[maxn2] = { 0 }, c[maxn2] = { 0 };
    int n1, n2;
    n1 = read_str(expression1, a);
    n2 = read_str(expression2, b);
    // 卷积操作
    for (int i = 0; i < n1 + n2; ++i) c[i] = 0;
    for (int i = 0; i < n1; ++i)
        for (int j = 0; j < n2; ++j)      c[i + j] += a[i] * b[j];
    // 进位
    for (int i = 0; i < n1 + n2; ++i)
    {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    int n = n1 + n2 - 1;
    for (int i = n-1; i >= 0; i--)
    {
        cout << c[i];
    }
    cout << endl;
}
void MoreTools::GetLargeAdd()
{
    int a[maxn2] = { 0 }, b[maxn2] = { 0 }, c[maxn2] = { 0 };
    int n1, n2;
    n1 = read_str(expression1, a);
    n2 = read_str(expression2, b);
    // 卷积操作
    for (int i = 0; i < n1 + 1; ++i) c[i] = 0;
    for (int i = 0; i < n1; ++i)
     c[i] = a[i] + b[i];
    // 进位
    for (int i = 0; i < n1 + 1 ;++i)
    {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    for (int i = n1-1; i >= 0; i--)
    {
        cout << c[i];
    }
    cout << endl;
}
void MoreTools::GetExpression()
{
    cout << "Large Number Caculator. Please input a integer." << endl;
    cout << "\nEnter number 1: ";
    cin >> expression1;
    cout << "\nEnter number 2: ";
    cin>>expression2;
}
void MoreTools::PrintMenu()
{
    cout << "\n\n\t1. Enter 10 to get Multiply & Add Ansewr.";
    cout << "\n\t2. Enter 0 to return to the main menu.";
}