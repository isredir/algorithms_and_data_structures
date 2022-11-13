#include <bits/stdc++.h>

using namespace std;

struct Graph {
    Graph(int n) {
        g = vector<vector<int>>(n);
        v = vector<bool>(n);
    }

    vector<vector<int>> g;
    vector<bool> v;
    vector<int> p;
};

void DFS_plus(int now, Graph &graph) {
    graph.v[now] = true;
    for (int neig: graph.g[now]) {
        if (!graph.v[neig]) {
            DFS_plus(neig, graph);
        }
    }
    graph.p.push_back(now);
}

int main() {
    int n;
    cin >> n;
    Graph graph(n + 1);
    vector<vector<int>> apples(n + 1, vector<int>(4));
    for (int i = 1; i < n + 1; ++i) {
        cin >> apples[i][0] >> apples[i][1] >> apples[i][2] >> apples[i][3];
    }
    for (int i = 1; i < n + 1; ++i) {
        for (int j = i + 1; j < n + 1; ++j) {
            if ((apples[i][0] - apples[j][0]) * (apples[i][0] - apples[j][0]) +
                (apples[i][1] - apples[j][1]) * (apples[i][1] - apples[j][1]) <=
                (apples[i][3] + apples[j][3]) * (apples[i][3] + apples[j][3])) {
                if (apples[i][2] > apples[j][2]) {
                    graph.g[i].push_back(j);
                } else {
                    graph.g[j].push_back(i);
                }
            }
        }
    }
    DFS_plus(1, graph);
    cout << graph.p.size() << endl;
    for (int i = graph.p.size() - 1; i >= 0; --i) {
        cout << graph.p[i] << " ";
    }
    return 0;
}
