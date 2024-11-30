#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class UnionFind {
public:
    UnionFind(int n) : parent(n + 1), rank(n + 1) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    bool unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV) {
            return false; // They are already in the same set.
        }
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }

private:
    vector<int> parent, rank;
};

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<Edge> edges;
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.emplace_back(u, v, w);
        }

        // Sort edges by weight
        sort(edges.begin(), edges.end(), compareEdges);

        UnionFind uf(n);
        int mstWeight = 0;
        int count = 0; // Number of edges added to MST

        for (const Edge& edge : edges) {
            if (uf.unionSets(edge.u, edge.v)) {
                mstWeight += edge.weight;
                count++;
                if (count == n - 1) {
                    break; // MST is complete
                }
            }
        }

        if (count == n - 1) {
            cout << mstWeight << endl;
        } else {
            cout << -1 << endl; // Graph is not connected
        }
    }
    return 0;
}
