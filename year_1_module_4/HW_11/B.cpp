#include <bits/stdc++.h>

using namespace std;

struct Graph {
    explicit Graph(int n) {
        g = vector<set<int64_t>>(n);
        first = vector<int64_t>(n);
        last = vector<int64_t>(n);
        l = 1;
        timer = 0;
        while ((1 << l) <= n) ++l;
        up = vector<vector<int64_t>>(l + 1, vector<int64_t>(n, 0));
    }

    int l;
    vector<set<int64_t>> g;
    vector<int64_t> first, last;
    vector<vector<int64_t>> up;
    int timer;

    void DFS(int64_t now, int64_t p = 0) {
        first[now] = ++timer;
        up[0][now] = p;
        for (int i = 1; i <= l; ++i) {
            up[i][now] = up[i - 1][up[i - 1][now]];
        }
        for (int64_t to : g[now]) {
            if (to != p) {
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
    int n, m;
    cin >> n >> m;
    Graph tree(n);
    for (int i = 1; i < n; ++i) {
        int a;
        cin >> a;
        tree.g[i].insert(a);
        tree.g[a].insert(i);
    }
    tree.DFS(0);
    int64_t a1, a2, x, y, z;
    cin >> a1 >> a2;
    cin >> x >> y >> z;
    int64_t s = 0;
    int64_t ans;
    for (int i = 0; i < m; ++i) {
        //cout << a1 << " " << a2 <<endl;
        if (i == 0) {
            ans = tree.LCA(a1, a2);
        } else {
            ans = tree.LCA((a1 + ans) % n, a2);
        }
        s += ans;
        //cout << ans << endl;
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
    }
    cout << s;
    return 0;
}