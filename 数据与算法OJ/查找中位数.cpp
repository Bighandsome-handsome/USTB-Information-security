#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int readNum() {
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    int v = 0;
    while (ch >= '0' && ch <= '9') {
        v = v * 10 + ch - '0';
        ch = getchar();
    }
    return v;
}
float A[300000] = { 0 };  // �����洢ÿ�μ����������λ��

int main() {
    int n = readNum();  // ��ȡ n
    int m = readNum();  // ��ȡ m

    vector<int> T(n);
    for (int i = 0; i < n; i++) {
        T[i] = readNum();  // ��ȡ���� T
    }

    // ����ѣ��洢��Сһ���Ԫ��
    priority_queue<int> left;
    // С���ѣ��洢�ϴ�һ���Ԫ��
    priority_queue<int, vector<int>, greater<int>> right;

    // ���� [0, b] �����Ԫ��ʱά����ƽ��
    for (int j = 0; j < n; j++) {  // ����ѭ���߽磬����Խ��
        int num = T[j];

        // ������Ԫ��ʱ��ά�������ѵ�ƽ��
        if (left.empty() || num <= left.top()) {
            left.push(num);
        }
        else {
            right.push(num);
        }

        // ��֤�����ѵĴ�С����� 1
        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        }
        else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }

        // ������λ��
        if ((j + 1) % 2 == 1) {  // ��������ʱ����λ���Ǵ���ѵĸ�
            A[j] = left.top();
        }
        else {  // ż������ʱ����λ���������ѵĸ���ƽ��ֵ
            A[j] = (left.top() + right.top()) / 2.0;
        }
    }

    // ����ÿ�β�ѯ
    for (int i = 0; i < m; i++) {
        int b = readNum();  // ��ǰ��ѯ�� b ֵ
        cout << A[b] << endl;  // ע�� b �� 1 ��ʼ����������Ӧ��ȥ 1
    }

    return 0;  // ��������
}
