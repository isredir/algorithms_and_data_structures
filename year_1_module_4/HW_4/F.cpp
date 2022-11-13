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
        g = vector<set<vector<int>>>(n);
        v = vector<bool>(n, false);
        d = vector<uint64_t>(n, MAX_INT);
        p = vector<int>(n);
    }

    vector<set<vector<int>>> g;
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
            for (auto vec : g[now]) {
                if (vec[0] >= d[now] && vec[2] <= d[vec[1]]) {
                    q.erase(make_pair(d[vec[1]], vec[1]));
                    d[vec[1]] = vec[2];
                    q.insert(make_pair(d[vec[1]], vec[1]));
                }
            }
        }
    }
};

int main() {
    int n, s, f, r;
    cin >> n >> s >> f >> r;
    Graph graph(n + 1);
    for (int i = 0; i < r; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        graph.g[a].insert({b, c, d});
    }
    graph.Dijkstra(s);
    if (graph.d[f] == MAX_INT) {
        cout << -1;
    } else {
        cout << graph.d[f];
    }
    return 0;
}
