#include <bits/stdc++.h>

using namespace std;

static const uint64_t MAX_INT = 30000000;

struct Graph {
    explicit Graph(int n) {
        g = vector<vector<int>>(n, vector<int>(n, 0));
        g_set = vector<set<pair<int, int>>>(n);
        v = vector<bool>(n, false);
        d = vector<double>(n, MAX_INT);
        p = vector<int>(n);
    }

    vector<vector<int>> g;
    vector<set<pair<int, int>>> g_set;
    vector<bool> v;
    vector<double> d;
    vector<int> p;
    bool flag = false;

    void DijkstraTree(int s) {
        d = vector<double>(g.size(), MAX_INT);
        d[s] = 0;
        p[s] = -1;
        priority_queue<pair<int, int>> q;
        q.push(make_pair(0, s));
        while (!q.empty()) {
            int now = q.top().second;
            int cur_d = -q.top().first;
            q.pop();
            if (cur_d > d[now]) continue;
            for (auto[to, len]: g_set[now]) {
                if (d[now] + len < d[to]) {
                    d[to] = d[now] + len;
                    p[to] = now;
                    q.push(make_pair(-d[to], to));
                }
            }
        }
    }

    void Dijkstra(int s, vector<pair<int, int>> &taxi) {
        d = vector<double>(g.size(), MAX_INT);
        d[s] = 0;
        p[s] = -1;
        priority_queue<pair<int, int>> q;
        q.push(make_pair(0, s));
        while (!q.empty()) {
            int now = q.top().second;
            int cur_d = -q.top().first;
            q.pop();
            if (cur_d > d[now]) continue;
            for (int to = 1; to < g[now].size(); ++to) {
                if (to == now) {
                    continue;
                }
                int len = g[now][to];
                if (d[now] + double(len) / double(taxi[to].second) + double(taxi[to].first) < d[to]) {
                    d[to] = d[now] + double(len) / double(taxi[to].second) + double(taxi[to].first);
                    p[to] = now;
                    q.push(make_pair(-d[to], to));
                }
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    Graph tree(n + 1);
    vector<pair<int, int>> taxi(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        int s, t;
        cin >> s >> t;
        taxi[i] = {s, t};
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        tree.g_set[a].insert({b, c});
        tree.g_set[b].insert({a, c});
    }
    Graph graph(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        tree.DijkstraTree(i);
        for (int j = i + 1; j < n + 1; ++j) {
            graph.g[i][j] = tree.d[j];
            graph.g[j][i] = tree.d[j];
        }
    }
    graph.Dijkstra(1, taxi);
    double max_path = 0;
    int max_v = 0;
    for (int i = 1; i < n + 1; ++i) {
        if (graph.d[i] > max_path) {
            max_path = graph.d[i];
            max_v = i;
        }
    }
    cout << fixed << setprecision(10) << max_path << endl;
    vector<int> path;
    for (int i = max_v; i != -1; i = graph.p[i]) {
        path.push_back(i);
    }
    for (int i: path) {
        cout << i << " ";
    }
    return 0;
}
