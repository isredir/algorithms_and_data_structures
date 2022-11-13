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
        g = vector<set<pair<int, int>>>(n);
        v = vector<bool>(n, false);
        d = vector<uint64_t>(n, MAX_INT);
        p = vector<int>(n);
    }

    vector<set<pair<int, int>>> g;
    vector<bool> v;
    vector<uint64_t> d;
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
    int n, m;
    cin >> n >> m;
    Graph graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        graph.g[a].insert({b, l});
        graph.g[b].insert({a, l});
    }
    int s, f;
    cin >> s >> f;
    graph.Dijkstra(s);
    if (graph.d[f] == MAX_INT) {
        cout << -1;
    } else {
        cout << graph.d[f] << endl;
        vector<int> path;
        for (int i = f; i != -1; i = graph.p[i]) {
            path.push_back(i);
        }
        cout << path.size() << endl;
        reverse(path.begin(), path.end());
        for (int i : path) {
            cout << i << " ";
        }
    }

    return 0;
}
