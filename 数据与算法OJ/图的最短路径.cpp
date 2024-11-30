#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

void bfs(int start, const vector<vector<Edge>>& graph, vector<int>& distances) {
    queue<int> q;
    q.push(start);
    distances[start] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (const auto& edge : graph[node]) {
            int nextNode = edge.to;
            int weight = edge.weight;

            if (distances[nextNode] > distances[node] + weight) {
                distances[nextNode] = distances[node] + weight;
                q.push(nextNode);
            }
        }
    }
}

int main() {
	std::ios::sync_with_stdio(false);
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<Edge>> graph(n + 1);
    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    for (int i = 0; i < q; ++i) {
        int start, end;
        cin >> start >> end;

        vector<int> distances(n + 1, INF);
        bfs(start, graph, distances);

        cout << distances[end] << endl;
    }

    return 0;
}
