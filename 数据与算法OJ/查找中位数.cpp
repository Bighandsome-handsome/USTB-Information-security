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
float A[300000] = { 0 };  // 用来存储每次计算出来的中位数

int main() {
    int n = readNum();  // 读取 n
    int m = readNum();  // 读取 m

    vector<int> T(n);
    for (int i = 0; i < n; i++) {
        T[i] = readNum();  // 读取序列 T
    }

    // 大根堆，存储较小一半的元素
    priority_queue<int> left;
    // 小根堆，存储较大一半的元素
    priority_queue<int, vector<int>, greater<int>> right;

    // 插入 [0, b] 区间的元素时维护堆平衡
    for (int j = 0; j < n; j++) {  // 修正循环边界，避免越界
        int num = T[j];

        // 插入新元素时，维护两个堆的平衡
        if (left.empty() || num <= left.top()) {
            left.push(num);
        }
        else {
            right.push(num);
        }

        // 保证两个堆的大小差不超过 1
        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        }
        else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }

        // 计算中位数
        if ((j + 1) % 2 == 1) {  // 奇数个数时，中位数是大根堆的根
            A[j] = left.top();
        }
        else {  // 偶数个数时，中位数是两个堆的根的平均值
            A[j] = (left.top() + right.top()) / 2.0;
        }
    }

    // 处理每次查询
    for (int i = 0; i < m; i++) {
        int b = readNum();  // 当前查询的 b 值
        cout << A[b] << endl;  // 注意 b 从 1 开始索引，所以应减去 1
    }

    return 0;  // 正常返回
}
