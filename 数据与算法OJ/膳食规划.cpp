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
    int count;             // 使用的食物数量
    int prev_state;        // 前一个状态
    int food_index;        // 当前使用的食物索引
} 
DPNode;

int N, M;
unsigned short required_mask = 0;           // 需要的营养物质掩码
unsigned short food_masks[65536];           // 每种食物的营养物质掩码
DPNode dp[1 << MAX_N];                      // 动态规划数组
int queue[1 << MAX_N];                      // 队列用于BFS
int head = 0, tail = 0;                     // 队列头尾指针

int compare_int(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

int main() 
{
    // 读取N和M，以及每种食物的营养物质数量
    std::ios::sync_with_stdio(false);
    int nutrient;
    cin>>N>>M;
    int foodNutrientCounts[M];
    for (int i = 0; i < M; i++) {
        cin>>foodNutrientCounts[i];
    }

    // 读取需要的营养物质列表
    for (int i = 0; i < N; i++) 
	{
        cin>>nutrient;
        required_mask |= (1 << nutrient);
    }

    // 读取每种食物包含的营养物质列表
    for (int i = 0; i < M; i++) {
        unsigned short mask = 0;
        for (int j = 0; j < foodNutrientCounts[i]; j++) {
            cin>>nutrient;
            mask |= (1 << nutrient);
        }
        food_masks[i] = mask;
    }

    // 初始化dp数组
    for (int i = 0; i < (1 << MAX_N); i++) {
        dp[i].count = INF;
        dp[i].prev_state = -1;
        dp[i].food_index = -1;
    }
    dp[0].count = 0;

    // BFS队列初始化
    queue[tail++] = 0;

    // 开始BFS
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
                // 如果食物序号更小，更新为序号更小的那个
                if (dp[new_state].food_index > i) {
                    dp[new_state].prev_state = current_state;
                    dp[new_state].food_index = i;
                }
            }
        }
    }

    // 检查是否有解
    if (dp[required_mask].count == INF) {
        cout<<"-1"<<endl;
        return 0;
    }

    // 还原路径，收集食物序号
    int path[16], path_len = 0;
    int state = required_mask;
    while (state != 0) {
        path[path_len++] = dp[state].food_index;
        state = dp[state].prev_state;
    }

    // 按照食物序号升序排列
    qsort(path, path_len, sizeof(int), compare_int);

    // 输出结果
    for (int i = 0; i < path_len; i++) {
        cout<< path[i];
        if (i != path_len - 1) {
           cout<<" ";
        }
    }
    printf("\n");

    return 0;
}

