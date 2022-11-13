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
        time = 0;
    }

    vector<vector<vector<int>>> g;
    vector<bool> v;
    vector<uint64_t> d;
    vector<int> p;
    int time;

    void Dijkstra(int s) {
        d = vector<uint64_t>(g.size(), MAX_INT);
        d[s] = time;
        p[s] = -1;
        set<pair<int, int>> q;
        q.insert(make_pair(d[s], s));
        while (!q.empty()) {
            int now = q.begin()->second;
            q.erase(q.begin());
            for (auto vec : g[now]) {
                int t = 0;
                while (t < d[now]) {
                    t += vec[1];
                }
                if (t + vec[2] <= d[vec[0]]) {
                    q.erase(make_pair(d[vec[0]], vec[0]));
                    d[vec[0]] = t + vec[2];
                    q.insert(make_pair(d[vec[0]], vec[0]));
                }
            }
        }
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    Graph graph(n + 1);
    for (int i = 0; i < k; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        graph.g[a].push_back({b, c, d});
    }
    int m;
    cin >> m;
    vector<int> p(m);
    for (int i = 0; i < m; ++i) {
        cin >> p[i];
    }
    for (int i = 0; i < m - 1; ++i) {
        graph.Dijkstra(p[i]);
        if (graph.d[p[i + 1]] == MAX_INT) {
            cout << -1;
            return 0;
        } else {
            graph.time = graph.d[p[i + 1]];
        }
    }
    cout << graph.time;
    return 0;
}
