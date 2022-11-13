#include <bits/stdc++.h>

using namespace std;

static const int INF = -1000000000;

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
                    if (d[from][k] > INF && d[k][to] > INF && d[from][k] + d[k][to] > d[from][to])
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
    int n, m, k;
    cin >> n >> m >> k;
    Graph graph(n + 1);
    map<pair<int, int>, int> edges;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.g[a][b] = c;
        edges[{a, b}] = i + 1;
    }
    vector<int> seq(k);
    for (int i = 0; i < k; ++i) {
        cin >> seq[i];
    }
    graph.Floyd();
    for (int i = 0; i < k; ++i) {
        if (graph.d[seq[i]][seq[i]] > 0) {
            cout << "infinitely kind";
            return 0;
        }
    }
    vector<int> res;
    for (int s = 0; s < k - 1; ++s) {
        int j = seq[s + 1], i = seq[s];
        vector<int> path;
        while (j != i) {
            int t = j;
            j = graph.p[i][j];
            path.push_back(edges[{j, t}]);
        }
        reverse(path.begin(), path.end());
        for (int l : path) {
            if (l == 0) {
                cout << "infinitely kind";
                return 0;
            }
            res.push_back(l);
        }
    }
    cout << res.size() << endl;
    for (int i : res) {
        cout << i << " ";
    }




    return 0;
}