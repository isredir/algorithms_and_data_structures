#include <bits/stdc++.h>
using namespace std;

struct Graph {
    Graph(int n) {
        g = vector<vector<int>>(n);
        v = vector<bool>(n);
        inDegree = vector<int>(n);
    }

    vector<vector<int>> g;
    vector<bool> v;
    vector<int> top_sort;
    vector<int> path;
    vector<int> inDegree;
};

struct Edge {
    int a;
    int b;
};

int main() {
    int n;
    cin >> n;
    Graph graph(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int b;
            cin >> b;
            graph.g[i].push_back(b);
            ++graph.inDegree[b];
        }
    }
    set<int, greater<int> > q;
    for (int i = 1; i < n + 1; ++i) {
        if (graph.inDegree[i] == 0) q.insert(i);
    }
    while (!q.empty()) {
        int v = *q.begin();
        q.erase(q.begin());
        graph.top_sort.push_back(v);
        for (int to : graph.g[v]){
            --graph.inDegree[to];
            if (graph.inDegree[to] == 0) {
                q.insert(to);
            }
        }
    }
    for (int i = graph.top_sort.size() - 1; i >= 0; --i) {
        cout << graph.top_sort[i] << " ";
    }
    return 0;
}
