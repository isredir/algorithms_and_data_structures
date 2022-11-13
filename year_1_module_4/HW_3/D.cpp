#include <bits/stdc++.h>
using namespace std;

struct Graph {
    explicit Graph(int n) {
        g = vector<unordered_set<int>>(n);
        v = vector<bool>(n, false);
        d = vector<int>(n);
        p = vector<int>(n);
    }

    struct Edge {
        int a;
        int b;
        bool operator<(const Edge &other) const {
            return (a < other.a) || (a == other.a && b < other.b);
        }
    };

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
            for (int to : g[now]) {
                if (!v[to]) {
                    v[to] = true;
                    q.push(to);
                    d[to] = d[now] + 1;
                    p[to] = now;
                }
            }
        }
    }
};

int main() {
    int n, m, s, t, q;
    cin >> n >> m >> s >> t >> q;
    Graph graph(n * m);
    vector<vector<int>> vec = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (auto v : vec) {
                if (i + v[1] >= 0 && i + v[1] < n && j + v[0] >= 0 && j + v[0] < m) {
                    graph.g[i * m + j].insert((i + v[1]) * m + (j + v[0]));
                    graph.g[(i + v[1]) * m + (j + v[0])].insert(i * m + j);
                }
            }
        }
    }
    vector<int> fleas(q);
    for (int i = 0; i < q; ++i) {
        int y, x;
        cin >> y >> x;
        fleas[i] = (y - 1) * m + x - 1;
    }
    graph.BFS((s - 1) * m + t - 1);
    int sum = 0;
    bool flag = true;
    for (int i : fleas) {
        if (!graph.v[i]) {
            flag = false;
        }
        sum += graph.d[i];
    }
    if (q == 0) {
        cout << 0;
        return 0;
    }
    if (flag) {
        cout << sum;
    } else {
        cout << -1;
    }
    return 0;
}
