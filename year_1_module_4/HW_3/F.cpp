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
    try {
        int n, m;
        std::cin >> n >> m;
        Graph graph(m + 1);
        vector<unordered_set<int>> lines = vector<unordered_set<int>>(n + 1);
        vector<Edge> edges;
        for (int i = 0; i < m; ++i) {
            int k;
            cin >> k;
            for (int j = 0; j < k; ++j) {
                int a;
                cin >> a;
                lines[a].insert(i);
            }
        }
        int start, finish;
        cin >> start >> finish;
        for (int i = 1; i < n + 1; ++i) {
            for (int x: lines[i]) {
                for (int y: lines[i]) {
                    if (x != y) {
                        graph.g[x].insert(y);
                        graph.g[y].insert(x);
                    }
                }
            }
        }
        for (int i: lines[start]) {
            graph.g[m].insert(i);
            graph.g[i].insert(m);
        }
        graph.BFS(m);
        int min_path = 1000000;
        bool flag = false;
        for (int i: lines[finish]) {
            if (graph.v[i]) {
                flag = true;
                min_path = min(min_path, graph.d[i]);
            }
        }
        if (flag) {
            cout << min_path - 1;
        } else {
            cout << -1;
        }
    } catch (const std::exception& e) {
        cout << -1;
    }
    return 0;
}
