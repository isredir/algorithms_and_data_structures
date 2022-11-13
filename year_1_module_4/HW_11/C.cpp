#include <bits/stdc++.h>

using namespace std;

struct Graph {
    explicit Graph(int n) {
        g = vector<set<int64_t>>(n);
        first = vector<int64_t>(n);
        last = vector<int64_t>(n);
        h = vector<int64_t>(n, 0);
        ver = vector<vector<int64_t>>(n);
        v = vector<bool>(n, false);
        timer = 0;
    }

    vector<set<int64_t>> g;
    vector<int64_t> first, last, h;
    vector<bool> v;
    int timer;
    vector<vector<int64_t>> ver;

    void DFS(int64_t now) {
        first[now] = ++timer;
        ver[h[now]].push_back(first[now]);
        v[now] = true;
        for (int64_t to: g[now]) {
            if (!v[to]) {
                h[to] = h[now] + 1;
                DFS(to);
            }
        }
        last[now] = ++timer;
    }

};

int main() {
    int n;
    cin >> n;
    Graph tree(n + 1);
    int root;
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        if (a == -1) {
            root = i;
        } else {
            tree.g[i].insert(a);
            tree.g[a].insert(i);
        }
    }
    tree.DFS(root);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int v, k;
        cin >> v >> k;
        if (tree.h[v] + k >= n) {
            cout << 0 << endl;
        }
        else {
            cout << upper_bound(tree.ver[tree.h[v] + k].begin(), tree.ver[tree.h[v] + k].end(), tree.last[v]) -
                    lower_bound(tree.ver[tree.h[v] + k].begin(), tree.ver[tree.h[v] + k].end(), tree.first[v]) << endl;
        }
    }
    return 0;
}