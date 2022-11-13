#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int a;
    int b;

    bool operator<(const Edge &other) const {
        return (a < other.a) || (a == other.a && b < other.b);
    }
};


struct Graph {
    explicit Graph(int n) {
        g = vector<unordered_set<int>>(n);
        v = vector<bool>(n, false);
        d = vector<int>(n);
        p = vector<int>(n);
    }

    vector<unordered_set<int>> g;
    vector<bool> v;
    vector<int> d, p;

    void BFS(int start) {
        queue<int> q;
        q.push(start);
        v[start] = true;
        p[start] = -1;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int to: g[now]) {
                if (!v[to]) {
                    v[to] = true;
                    q.push(to);
                    d[to] = d[now] + 1;
                    p[to] = now;
                }
            }
        }
    }

    vector<int> Path(int start, int finish) {
        BFS(start);
        if (!v[finish]) {
            return {-1};
        }
        vector<int> path;
        for (int i = finish; i != -1; i = p[i]) {
            path.push_back(i);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph graph(n + 1);
    Graph graph2(n + 1);
    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph.g[a].insert(b);
        graph.g[b].insert(a);
        graph2.g[a].insert(b);
        graph2.g[b].insert(a);
        edges.push_back({a, b});
    }
    int start, finish;
    cin >> start >> finish;
    graph.BFS(start);
    vector<int> from_st = graph.d;
    graph2.BFS(finish);
    vector<int> from_fin = graph2.d;
    int num = 0;
    for (Edge edge: edges) {
        if (from_st[edge.a] + from_fin[edge.b] == from_st[finish] - 1 ||
            from_st[edge.b] + from_fin[edge.a] == from_st[finish] - 1) {
            ++num;
        }
    }
    cout << m - num;
    return 0;
}
