#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#define MAX_N (16)
#define MAX_M (1 << MAX_N) // 2^16 = 65536
#define INF (1 << 30)
using namespace std;
typedef struct 
{
    int count;             // ʹ�õ�ʳ������
    int prev_state;        // ǰһ��״̬
    int food_index;        // ��ǰʹ�õ�ʳ������
} 
DPNode;

int N, M;
unsigned short required_mask = 0;           // ��Ҫ��Ӫ����������
unsigned short food_masks[65536];           // ÿ��ʳ���Ӫ����������
DPNode dp[1 << MAX_N];                      // ��̬�滮����
int queue[1 << MAX_N];                      // ��������BFS
int head = 0, tail = 0;                     // ����ͷβָ��

int compare_int(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

int main() 
{
    // ��ȡN��M���Լ�ÿ��ʳ���Ӫ����������
    std::ios::sync_with_stdio(false);
    int nutrient;
    cin>>N>>M;
    int foodNutrientCounts[M];
    for (int i = 0; i < M; i++) {
        cin>>foodNutrientCounts[i];
    }

    // ��ȡ��Ҫ��Ӫ�������б�
    for (int i = 0; i < N; i++) 
	{
        cin>>nutrient;
        required_mask |= (1 << nutrient);
    }

    // ��ȡÿ��ʳ�������Ӫ�������б�
    for (int i = 0; i < M; i++) {
        unsigned short mask = 0;
        for (int j = 0; j < foodNutrientCounts[i]; j++) {
            cin>>nutrient;
            mask |= (1 << nutrient);
        }
        food_masks[i] = mask;
    }

    // ��ʼ��dp����
    for (int i = 0; i < (1 << MAX_N); i++) {
        dp[i].count = INF;
        dp[i].prev_state = -1;
        dp[i].food_index = -1;
    }
    dp[0].count = 0;

    // BFS���г�ʼ��
    queue[tail++] = 0;

    // ��ʼBFS
    while (head < tail) {
        int current_state = queue[head++];
        if (current_state == required_mask) {
            break;
        }
        for (int i = 0; i < M; i++) {
            unsigned short new_state = current_state | (food_masks[i] & required_mask);
            if (dp[new_state].count > dp[current_state].count + 1) {
                dp[new_state].count = dp[current_state].count + 1;
                dp[new_state].prev_state = current_state;
                dp[new_state].food_index = i;
                queue[tail++] = new_state;
            } else if (dp[new_state].count == dp[current_state].count + 1) {
                // ���ʳ����Ÿ�С������Ϊ��Ÿ�С���Ǹ�
                if (dp[new_state].food_index > i) {
                    dp[new_state].prev_state = current_state;
                    dp[new_state].food_index = i;
                }
            }
        }
    }

    // ����Ƿ��н�
    if (dp[required_mask].count == INF) {
        cout<<"-1"<<endl;
        return 0;
    }

    // ��ԭ·�����ռ�ʳ�����
    int path[16], path_len = 0;
    int state = required_mask;
    while (state != 0) {
        path[path_len++] = dp[state].food_index;
        state = dp[state].prev_state;
    }

    // ����ʳ�������������
    qsort(path, path_len, sizeof(int), compare_int);

    // ������
    for (int i = 0; i < path_len; i++) {
        cout<< path[i];
        if (i != path_len - 1) {
           cout<<" ";
        }
    }
    printf("\n");

    return 0;
}

