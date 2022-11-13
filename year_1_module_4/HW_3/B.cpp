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
    vector<unordered_set<int>> len;
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
    int n;
    cin >> n;
    Graph graph(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            int a;
            cin >> a;
            if (a == 1) {
                graph.g[i].insert(j);
            }
        }
    }
    int start, finish;
    cin >> start >> finish;
    vector<int> path = graph.Path(start, finish);
    if (path[0] == -1) {
        cout << -1;
        return 0;
    }
    if (path.size() == 1) {
        cout << 0;
        return 0;
    }
    cout << path.size() - 1 << endl;
    for (int i : path) {
        cout << i << " ";
    }
    return 0;
}
