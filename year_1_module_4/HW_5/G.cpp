#include <bits/stdc++.h>

using namespace std;

static const int INF = 1000000000;

struct Edge {
    int a, b, cost;
};

struct Graph {
    explicit Graph(int nn) {
        d = vector<int>(nn, INF);
        n = nn;
    }

    int n;
    vector<int> d;

    void Ford() {
        d[1] = 0;
        for (;;) {
            bool any = false;
            for (int i = 1; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (d[i] < INF)
                        if (d[j] > d[i] + (179 * i + 719 * j) % 1000 - 500) {
                            d[j] = d[i] + (179 * i + 719 * j) % 1000 - 500;
                            any = true;
                        }
                }
            }
            if (!any) break;
        }
    }
};

int main() {
    int n;
    cin >> n;
    Graph graph(n + 1);
    graph.Ford();
    cout << graph.d[n];
    return 0;
}