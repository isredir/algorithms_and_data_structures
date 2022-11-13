#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const int INF = (int)(1e9);

struct Edge {
    int v;
    int flow;
    int capacity;

    Edge(int v, int capacity) : v(v), flow(0), capacity(capacity) {}

    int get_capacity() {
        return capacity - flow;
    }
};

struct Graph {
    int n;
    int s, t;
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<int> used;
    int timer = 1;
    Graph(int nn) {
        n = nn;
        g = vector<vector<int>>(n);
        used = vector<int>(n);
    }

    void add_edge(int v, int u, int capacity) {
        g[v].emplace_back(edges.size());
        edges.emplace_back(u, capacity);
        g[u].emplace_back(edges.size());
        edges.emplace_back(v, 0);
    }

    int dfs(int v, int min_capacity) {
        if (v == t) {
            return min_capacity;
        }
        used[v] = timer;
        for (int index : g[v]) {
            if (edges[index].get_capacity() == 0) {
                continue;
            }
            if (used[edges[index].v] == timer) {
                continue;
            }
            int x = dfs(edges[index].v, min(min_capacity, edges[index].get_capacity()));
            if (x) {
                edges[index].flow += x;
                edges[index ^ 1].flow -= x;
                return x;
            }
        }
        return 0;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    graph.s = 0;
    graph.t = n - 1;
    for (int i = 0; i < m; ++i) {
        int v, u, capacity;
        cin >> v >> u >> capacity;
        graph.add_edge(v - 1, u - 1, capacity);
    }
    while (graph.dfs(graph.s, INF)) {
        ++graph.timer;
    }
    int result = 0;
    for (int index : graph.g[graph.s]) {
        result += graph.edges[index].flow;
    }
    cout << result << endl;
    return 0;
}