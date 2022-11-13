#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

struct Graph {
    explicit Graph(int n) {
        g = vector<set<pair<int64_t, int64_t>>>(n);
        first = vector<int64_t>(n);
        last = vector<int64_t>(n);
        sum = vector<int64_t>(n, 0);
        h = vector<int64_t>(n, 0);
        l = 1;
        timer = 0;
        while ((1 << l) <= n) ++l;
        up = vector<vector<int64_t>>(l + 1, vector<int64_t>(n, 0));
    }

    int l;
    vector<set<pair<int64_t, int64_t>>> g;
    vector<int64_t> first, last, sum, h;
    vector<vector<int64_t>> up;
    int timer;

    void DFS(int64_t now, int64_t p = 0) {
        first[now] = ++timer;
        up[0][now] = p;
        for (int i = 1; i <= l; ++i) {
            up[i][now] = up[i - 1][up[i - 1][now]];
        }
        for (auto [to, w] : g[now]) {
            if (to != p) {
                h[to] = h[now] + 1;
                sum[to] = sum[now] + w;
                DFS(to, now);
            }
        }
        last[now] = ++timer;
    }

    bool Parent(int64_t a, int64_t b) {
        return first[a] <= first[b] && last[a] >= last[b];
    }

    int64_t LCA(int64_t a, int64_t b) {
        if (Parent(a, b)) {
            return a;
        }
        if (Parent(b, a)) {
            return b;
        }
        for (int i = l; i >= 0; --i) {
            if (!Parent(up[i][a], b)) {
                a = up[i][a];
            }
        }
        return up[0][a];
    }

};

int main() {
    int n;
    cin >> n;
    Graph tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        tree.g[a - 1].insert({b - 1, 1});
        tree.g[b - 1].insert({a - 1, -1});
    }
    tree.DFS(0);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        int64_t c = tree.LCA(a, b);
        if (tree.sum[a] - tree.sum[c] == tree.h[c] - tree.h[a] && tree.sum[b] - tree.sum[c] == tree.h[b] - tree.h[c]) {
            cout << "Yes" << '\n';
        } else {
            cout << "No" << '\n';
        }
    }
    return 0;
}