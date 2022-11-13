#include <bits/stdc++.h>

using namespace std;

static const int INF = 10000000;

struct Graph {
    explicit Graph(int nn) {
        g = vector<vector<int>>(nn, vector<int>(nn, INF));
        d = vector<vector<int>>(nn, vector<int>(nn, INF));
        p = vector<vector<int>>(nn, vector<int>(nn, -1));
        for (int from = 1; from < nn; ++from) {
            for (int to = 1; to < nn; ++to) {
                p[from][to] = from;
            }
        }
        n = nn;
    }

    vector<vector<int>> g;
    vector<vector<int>> d;
    int n;
    vector<vector<int>> p;

    void Floyd() {
        d = g;
        for (int k = 1; k < n; ++k) {
            for (int from = 1; from < n; ++from) {
                for (int to = 1; to < n; ++to) {
                    if (d[from][k] < INF && d[k][to] < INF && d[from][k] + d[k][to] < d[from][to])
                    {
                        d[from][to] = d[from][k] + d[k][to];
                        p[from][to] = p[k][to];
                    }
                }
            }
        }
    }
};

int main() {
    int n, m, s, f;
    cin >> n >> m >> s >> f;
    Graph graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.g[a][b] = c;
        graph.g[b][a] = c;
    }
    double probability = 1;
    graph.Floyd();
    vector <int> path;
    int j = f, i = s;
    while (j != i)
    {
        int k = j;
        j = graph.p[i][j];
        probability *= (1.0 - double(graph.g[j][k]) / 100.0);
    }
    cout << 1.0 - probability;

    return 0;
}