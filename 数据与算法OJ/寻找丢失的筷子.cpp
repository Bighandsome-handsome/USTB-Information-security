#include <iostream>  
#include <vector>  
#include <unordered_map>  
  
using namespace std;  
  
int main() {  
    int N;  
    cin >> N;  // ʹ�� cin ��ȡ N  
    vector<int> chopsticks(2*N-2);  // ���岢��ʼ�� chopsticks ����  
    for (int i = 0; i < 2*N-2; ++i) {  
        cin >> chopsticks[i];  // ʹ�� cin ��ȡÿ�����ӵĳ���  
    }  
  
    unordered_map<int, int> countMap;  
    for (int length : chopsticks) {  
        ++countMap[length];  // ͳ��ÿ�����ȵĿ�������  
    }  
  
   int lostLength1 = -1, lostLength2 = -1;  
    for (auto& entry : countMap) {  
        if (entry.second % 2 != 0) {  // �ҵ�����Ϊ�����Ŀ��ӳ���  
            if (lostLength1 == -1) {  
                lostLength1 = entry.first;  
            } else {  
                lostLength2 = entry.first;  
                break;  // ֻ��Ҫ�ҵ���������  
            }  
        }  
    }  
  
    // ��������ȷ�� lostLength1 С�� lostLength2  
    if (lostLength2 > lostLength1) {  
        printf("%d %d\n",lostLength1,lostLength2);  
    } else {  
       printf("%d %d\n",lostLength2,lostLength1); 
    }  
    return 0;  
}
