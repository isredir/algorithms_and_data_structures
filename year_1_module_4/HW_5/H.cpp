#include <bits/stdc++.h>

using namespace std;

static const int INF = 1000000000;

struct Edge {
    int a, a_time, b, b_time;
};

struct Graph {
    explicit Graph(int nn) {
        d = vector<int>(nn, 0);
        v = vector<bool>(nn, false);
        n = nn;
    }

    int n;
    vector<int> d;
    vector<bool> v;

    void Ford(const vector<Edge> &edges, int start) {
        d[start] = 0;
        v[start] = true;
        for (;;) {
            bool any = false;
            for (auto &edge: edges) {
                if ((v[edge.a] && d[edge.a] <= edge.a_time) && !(v[edge.b] && d[edge.b] <= edge.b_time)) {
                    v[edge.b] = true;
                    d[edge.b] = edge.b_time;
                    any = true;
                }
            }
            if (!any) break;
        }
    }

};

int main() {
    int n, s, f, k;
    cin >> n >> s >> f >> k;
    Graph graph(n + 1);
    vector<Edge> edges;
    for (int i = 0; i < k; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        edges.push_back({a, b, c, d});
    }
    graph.Ford(edges, s);
    cout << graph.d[f];
    return 0;
}