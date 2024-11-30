#include <iostream>  
#include <vector>  
#include <unordered_map>  
  
using namespace std;  
  
int main() {  
    int N;  
    cin >> N;  // 使用 cin 读取 N  
    vector<int> chopsticks(2*N-2);  // 定义并初始化 chopsticks 数组  
    for (int i = 0; i < 2*N-2; ++i) {  
        cin >> chopsticks[i];  // 使用 cin 读取每个筷子的长度  
    }  
  
    unordered_map<int, int> countMap;  
    for (int length : chopsticks) {  
        ++countMap[length];  // 统计每个长度的筷子数量  
    }  
  
   int lostLength1 = -1, lostLength2 = -1;  
    for (auto& entry : countMap) {  
        if (entry.second % 2 != 0) {  // 找到数量为奇数的筷子长度  
            if (lostLength1 == -1) {  
                lostLength1 = entry.first;  
            } else {  
                lostLength2 = entry.first;  
                break;  // 只需要找到两个即可  
            }  
        }  
    }  
  
    // 输出结果，确保 lostLength1 小于 lostLength2  
    if (lostLength2 > lostLength1) {  
        printf("%d %d\n",lostLength1,lostLength2);  
    } else {  
       printf("%d %d\n",lostLength2,lostLength1); 
    }  
    return 0;  
}
