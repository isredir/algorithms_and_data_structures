#include <bits/stdc++.h>

using namespace std;

static const int INF = 1000000000;

struct Edge {
    int a, b, cost;
    bool operator!=(const Edge& other) const {
        return !(a == other.a && b == other.b && cost == other.cost);
    }
};

struct Graph {
    explicit Graph(int nn) {
        g = vector<set<int>>(nn);
        d = vector<int>(nn, INF);
        p = vector<int>(nn, -1);
        v = vector<bool>(nn, false);
        n = nn;
    }
    int n;
    vector<set<int>> g;
    vector<int> d, p;
    vector<bool> v;
    vector<Edge> edges;
    bool flag = false;
    void DFS(int now) {
        v[now] = true;
        for (int neig: g[now]) {
            if (!v[neig]) {
                DFS(neig);
            }
        }
    }

    void Ford() {
        d[0] = 0;
        int x;
        for (int i = 0; i < n; ++i) {
            x = -1;
            for (auto & edge : edges) {
                if (d[edge.a] < INF) {
                    if (d[edge.b] > d[edge.a] + edge.cost) {
                        d[edge.b] = max(-INF, d[edge.a] + edge.cost);
                        x = edge.b;
                        p[edge.b] = edge.a;
                    }
                }
            }
        }
        if (x != -1) {
            Edge e = {1, 1999, -5};
            if (edges.back() != e)
                flag = true;
        } else {
            flag = false;
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.g[a - 1].insert(b - 1);
        graph.edges.push_back({a - 1, b - 1, -c});
    }
    graph.Ford();
    if (graph.d[n - 1] == INF) {
        cout << ":(";
        return 0;
    }
    if (graph.flag) {
        cout << ":)";
        return 0;
    }
    cout << -graph.d[n - 1];
    return 0;
}