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
        even = vector<vector<int>>(n, vector<int>(n, 10000000));
        odd = vector<vector<int>>(n, vector<int>(n, 10000000));
        for (int i = 0; i < n; ++i) {
            even[i][i] = 0;
        }
    }

    vector<unordered_set<int>> g;
    vector<bool> v;
    vector<vector<int>> even, odd;

    void BFS(int start) {
        queue<int> q;
        q.push(start);
        v[start] = true;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            v[now] = false;
            for (int to: g[now]) {
                if (even[start][to] > odd[start][now] + 2) {
                    even[start][to] = odd[start][now] + 2;
                    if (!v[to]) {
                        v[to] = true;
                        q.push(to);
                    }
                }
                if (odd[start][to] > even[start][now] + 2) {
                    odd[start][to] = even[start][now] + 2;
                    if (!v[to]) {
                        v[to] = true;
                        q.push(to);
                    }
                }
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n + 1);
    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph.g[a].insert(b);
        graph.g[b].insert(a);
        edges.push_back({a, b});
    }
    int k;
    cin >> k;
    vector<int> robots(k);
    for (int i = 0; i < k; ++i) {
        cin >> robots[i];
    }
    vector<vector<int>> min_even(n + 1), min_odd(n + 1);
    for (int i : robots) {
        graph.BFS(i);
    }
    min_even = graph.even;
    min_odd = graph.odd;
    int ans = 1000000;
    for (Edge edge: edges) {
        int c = 0;
        for (int i : robots) {
            c = max(c, min(min(min_odd[i][edge.a], min_even[i][edge.a]), min(min_odd[i][edge.b], min_even[i][edge.b])) +
                       1);
        }
        ans = min(ans, c);
    }
    for (int i = 1; i < n + 1; ++i) {
        int odd = 0, even = 0;
        for (int j : robots) {
            odd = max(odd, min_odd[j][i]);
            even = max(even, min_even[j][i]);
        }
        ans = min(ans, min(odd, even));
    }
    if (k == 1) {
        cout << 0;
    }
    if (ans < 100000) {
        cout << float(ans) / 2.0;
    } else {
        cout << -1;
    }
    return 0;
}
