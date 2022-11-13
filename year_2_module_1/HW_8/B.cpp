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
    vector<bool> visited;
    vector<int> path;
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

    void dfs2(int u) {
        path.push_back(u);
        if (u == t) {
            return;
        }
        for (int id : g[u]) {
            int v = edges[id].v;
            if (!visited[id] && edges[id].flow == 1) {
                visited[id] = true;
                dfs2(v);
                break;
            }
        }
    }

    void printPath() {
        dfs2(s);

        for (int i : path) {
            cout << i + 1 << " ";
        }
        cout << endl;

        path.clear();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Graph graph(n);
    graph.s = s - 1;
    graph.t = t - 1;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        graph.add_edge(v - 1, u - 1, 1);
    }
    while (graph.dfs(graph.s, INF)) {
        ++graph.timer;

    }
    int result = 0;
    for (int index : graph.g[graph.s]) {
        result += graph.edges[index].flow;
    }
    if (result < 2) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        graph.visited = vector<bool>(2 * m, false);
        graph.printPath();
        graph.printPath();
    }
    return 0;
}