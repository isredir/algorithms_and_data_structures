#include <bits/stdc++.h>

using namespace std;

static const int INF = 1000000000;

struct Edge {
    int a, b, cost;
};

struct Graph {
    explicit Graph(int nn) {
        d = vector<int>(nn, INF);
        p = vector<int>(nn, -1);
        n = nn;
    }

    int n;
    vector<int> d, p;
    vector<Edge> edges;

    void Ford() {
        d[0] = 0;
        int x;
        for (int i = 0; i < n; ++i) {
            x = -1;
            for (auto & edge : edges) {
                if (d[edge.a] < INF) {
                    if (d[edge.b] > d[edge.a] + edge.cost) {
                        d[edge.b] = max(-INF, d[edge.a] + edge.cost);
                        p[edge.b] = edge.a;
                        x = edge.b;
                    }
                }
            }
        }

        if (x == -1)
            cout << "NO";
        else {
            int y = x;
            for (int i = 0; i < n; ++i)
                y = p[y];

            vector<int> path;
            for (int cur = y;; cur = p[cur]) {
                path.push_back(cur);
                if (cur == y && path.size() > 1) break;
            }
            reverse(path.begin(), path.end());

            cout << "YES" << endl << path.size() << endl;
            for (int i : path)
                cout << i + 1 << ' ';
        }
    }
};

int main() {
    int n;
    cin >> n;
    Graph graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int a;
            cin >> a;
            if (a < 100000) {
                graph.edges.push_back({i, j, a});
            }
        }
    }
    graph.Ford();
    return 0;
}