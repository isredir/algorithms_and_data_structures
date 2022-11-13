#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int a;
    int b;

    bool operator<(const Edge &other) const {
        return (a < other.a) || (a == other.a && b < other.b);
    }
};

static const uint64_t MAX_INT = 300000000000;

struct Graph {
    explicit Graph(int n) {
        g = vector<vector<vector<int>>>(n);
        v = vector<bool>(n, false);
        d = vector<uint64_t>(n, MAX_INT);
        p = vector<int>(n);
    }

    vector<vector<vector<int>>> g;
    vector<bool> v;
    vector<uint64_t> d;
    vector<int> p;

    void Dijkstra(int s, int mas) {
        d = vector<uint64_t>(g.size(), MAX_INT);
        d[s] = 0;
        p[s] = -1;
        set<pair<int, int>> q;
        q.insert(make_pair(d[s], s));
        while (!q.empty()) {
            int now = q.begin()->second;
            q.erase(q.begin());
            for (auto vec : g[now]) {
                if (d[now] + vec[1] < d[vec[0]] && vec[2] >= mas) {
                    q.erase(make_pair(d[vec[0]], vec[0]));
                    d[vec[0]] = d[now] + vec[1];
                    q.insert(make_pair(d[vec[0]], vec[0]));
                }
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        graph.g[a].push_back({b, c, d});
        graph.g[b].push_back({a, c, d});
    }
    int mas = 3000000;
    int l = 0;
    int r = 10000000;
    int d;
    while (l < r) {
        d = (r + l) / 2;
        graph.Dijkstra(1, mas + 100 * d);
        if (graph.d[n] <= 1440) {
            l = d + 1;
        } else {
            r = d;
        }
    }
    if (n == 1) {
        cout << 10000000;
    } else if (l == 0) {
        cout << 0;
    } else {
        cout << l - 1;
    }
    return 0;
}
