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
        g = vector<set<pair<int, int>>>(n);
        v = vector<bool>(n, false);
        d = vector<int>(n, 100000000);
        p = vector<int>(n);
    }

    vector<set<pair<int, int>>> g;
    vector<bool> v;
    vector<int> d;
    vector<int> p;

    void Dijkstra(int s) {
        d[s] = 0;
        p[s] = -1;
        set<pair<int, int>> q;
        q.insert(make_pair(d[s], s));
        while (!q.empty()) {
            int now = q.begin()->second;
            q.erase(q.begin());
            for (auto [to, len] : g[now]) {
                if (d[now] + len < d[to]) {
                    q.erase(make_pair(d[to], to));
                    d[to] = d[now] + len;
                    p[to] = now;
                    q.insert(make_pair(d[to], to));
                }
            }
        }
    }
};

int main() {
    int n, s, f;
    cin >> n >> s >> f;
    Graph graph(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            int a;
            cin >> a;
            if (a != -1) {
                graph.g[i].insert({j, a});
            }
        }
    }
    graph.Dijkstra(s);
    if (graph.d[f] == 100000000) {
        cout << -1;
    } else {
        vector<int> path;
        for (int i = f; i != -1; i = graph.p[i]) {
            path.push_back(i);
        }
        reverse(path.begin(), path.end());
        for (int i : path) {
            cout << i << " ";
        }
    }
    return 0;
}
