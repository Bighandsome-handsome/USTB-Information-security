1. 整数练习
【问题描述】
输入一个字符串格式的无符号整数X，以及一个整数n。n表示后续操作的次数。
接下来n行，每行包含一个标识符O，以及一个字符串格式的无符号整数Y。
如果O=0，表示X与Y之间进行加法运算，结果保存在X中。
如果O=1，表示X与Y之间进行减法运算，用X与Y之间较大的数减去较小的数，结果保存在X中。 
【输入形式】
第一行输入一个字符串格式的无符号整数X，以及一个整数n。
接下来n行，每行包含一个标识符O，以及一个字符串格式的无符号整数Y。
【输出形式】
输出n行，每行输出运算结束后的整数。
【测试输入1】
12345 3
0 123
0 12345
0 10000
【测试输出1】
12468
24813
34813
【测试输入2】
12345 3
1 123
1 10000
1 0
【测试输出2】
12222
2222
2222
【测试输入3】
12345 3
1 123
1 10000
1 1234
【测试输出3】
12222
2222
988
【测试输入4】
12345 5
1 12300
1 12468
0 10000
1 0
0 0
【测试输出4】
45
12423
22423
22423
22423
【测试输入5】
12345 5
1 12300
1 45
1 0
0 0
0 10000
【测试输出5】
45
0
0
0
10000
【评分标准】
5个测试用例，每个1分。
【程序说明】
现提供友人A实现的C++代码，请在此基础上，修改代码，
使得修改后的程序可以完成上述题目的功能。
#include <iostream>
#include <string>
using namespace std;
bool strLarge(string str, string opstr){
    if (str.length() - opstr.length() > 0)
        return true;
    if (str.length() - opstr.length() < 0)
        return false;
    for (int i = 0; i < str.length(); ++i)
        if (str[i] > opstr[i])
            return true;
        else if (str[i] < opstr[i])
            return false;
    //return true when equal
    return true;
}
string reverse(string str){
    string ans = "";
    for (int i = 0; i < str.length(); ++i)
        ans.push_back(str[str.length() - 1 - i]);
    return ans;
}
string strSub(string str, string opstr){
    string ans = "";
    int i = 1;
    while (str.length()-i>=0 && opstr.length()-i>=0){
        int temp = str[str.length()-i] - opstr[opstr.length()-i];
        ans.push_back(temp+'0');
        i++;
    }
    while (str.length()-i>=0){
        int temp = str[str.length()-i] - '0';
        ans.push_back(temp+'0');
        i++;
    }
    while (ans.back() == '0')
        ans.pop_back();
    return reverse(ans);
}
string strAdd(string str, string opstr){
   string ans = "";
   int i = 1;
    int temp = 0;
    while (str.length()-i>=0 && opstr.length()-i>=0){
        temp += (str[str.length()-i]-'0') + (opstr[opstr.length()-i]-'0');
        ans.push_back(temp%10 + '0');
        temp /= 10;
        i++;
    }
    while (str.length()-i>=0){
        temp += (str[str.length()-i]-'0');
        ans.push_back(temp%10 + '0');
        temp /= 10;
        i++;
    }
    while (opstr.length()-i>=0){
        temp += (opstr[opstr.length()-i]-'0');
        ans.push_back(temp%10 + '0');
        temp /= 10;
        i++;
    }
    if (temp)
        ans.push_back(temp + '0');
    return reverse(ans);
}
int main()
{
    int num;
    string str;
    cin >> str;
   cin >> num;
    for (int i = 0; i < num; ++i){
        int op;
       string opstr;
        cin >> op >> opstr;
        if (op == 0)
            str = strAdd(str, opstr);
        else if (strLarge(str, opstr))
            str = strSub(str, opstr);
        else
            str = strSub(opstr, str);
        cout << str << endl;
    }
}

2. 浮点数练习
【问题描述】填写合适的表达式，使得每个测试用例对应的函数返回值为True。
【输入形式】输入测试用例编号1-5。该部分的代码已经给出，不需要学生完成。
【输出形式】如果测试通过输出"Pass."，未通过则输出"No Pass."。
【样例输入】1
【样例输出】Pass.
【样例说明】无
【评分标准】每个测试用例1分。

【提示】
下列关于数据表示的规定可能有助于你解决问题：
对于浮点数(float, double)类型，在做加法运算时，计算结果会进行舍入。
对于浮点数(float, double)类型，其最大的正数是+inf，+inf与除-inf和NaN以外的其他浮点数进行加法运算，结果为+inf。
对于浮点数(float, double)类型，NaN是Not a Number的缩写，表示计算结果未知的情况。NaN与任何浮点数（包括NaN本身）不可比，即任何NaN相关的比较(>,>=,==,<=,<)结果都是False。
对于浮点数，+0与-0相等。
C/C++中，常量整数默认是signed int类型，小数默认是double类型。
浮点数(float, double)转换为整型(int)，只保留整数部分。