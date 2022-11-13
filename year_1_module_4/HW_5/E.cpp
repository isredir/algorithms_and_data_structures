#include <bits/stdc++.h>

using namespace std;

static const int INF = 50000001;

struct Graph {
    explicit Graph(int nn) {
        g = vector<vector<int>>(nn, vector<int>(nn, 0));
        d = vector<vector<int>>(nn, vector<int>(nn, INF));
        p = vector<int>(nn);
        n = nn;
    }

    vector<vector<int>> g;
    vector<vector<int>> d;
    int n;
    vector<int> p;

    void Floyd() {
        for (int k = 0; k < n; ++k) {
            for (int from = 0; from < n; ++from) {
                for (int to = 0; to < n; ++to) {
                    g[from][to] = min(g[from][to], g[from][k] + g[k][to]);
                }
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    Graph graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph.g[i][j];
            if (graph.g[i][j] == 0) {
                graph.g[i][j] = INF;
            }
        }
    }
    graph.Floyd();
    int max_path = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph.g[i][j] < INF && i != j) {
                max_path = max(max_path, graph.g[i][j]);
            }
        }
    }
    cout << max_path;
    return 0;
}