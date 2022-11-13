#include <bits/stdc++.h>

using namespace std;

struct Graph {
    explicit Graph(int nn) {
        n = nn;
        g = vector<set<pair<int64_t, int64_t>>>(n);
        first = vector<int64_t>(n);
        last = vector<int64_t>(n);
        h = vector<int64_t>(n, 0);
        l = 1;
        timer = 0;
        while ((1 << l) <= n) ++l;
        up = vector<vector<int64_t>>(l + 1, vector<int64_t>(n, 0));
        mn = vector<vector<int64_t>>(l + 1, vector<int64_t>(n, 0));
    }

    int l, n;
    vector<set<pair<int64_t, int64_t>>> g;
    vector<int64_t> first, last, h;
    vector<vector<int64_t>> up;
    vector<vector<int64_t>> mn;
    int timer;

    void DFS(int64_t now, int64_t p = 0) {
        first[now] = ++timer;
        up[0][now] = p;
        for (auto [to, w] : g[now]) {
            if (to != p) {
                mn[0][to] = w;
                h[to] = h[now] + 1;
                DFS(to, now);
            }
        }
        last[now] = ++timer;
    }

    void fill() {
        for (int i = 1; i <= l; ++i) {
            for (int now = 0; now < n; ++now) {
                up[i][now] = up[i - 1][up[i - 1][now]];
                mn[i][now] = min(mn[i - 1][now], mn[i - 1][up[i - 1][now]]);
            }
        }
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

    int64_t get_min(int64_t a, int64_t b) {
        int64_t ans = 10000000000;
        if (h[a] > h[b]) {
            swap(a, b);
        }
        int64_t d = h[b] - h[a];
        while (d > 0) {
            int log = int(log2(d));
            ans = min(ans, mn[log][b]);
            b = up[log][b];
            d -= (1 << log);
        }
        while (a != b) {
            int i = int(log2(h[a]));
            while (i > 0 && up[i][a] == up[i][b]) {
                --i;
            }
            ans = min(ans, min(mn[i][a], mn[i][b]));
            a = up[i][a];
            b = up[i][b];
        }
        return ans;
    }

};

int main() {
    int n;
    cin >> n;
    Graph tree(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        tree.g[i].insert({a - 1, b});
        tree.g[a - 1].insert({i, b});
    }
//    for (int i = 0; i < n; ++i) {
//        cout << i << ": ";
//        for (auto [j, w] : tree.g[i]) {
//            cout << j << " ";
//        }cout << endl;
//    }
    tree.DFS(0);
    tree.fill();
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int64_t a, b;
        cin >> a >> b;
        cout << tree.get_min(a - 1, b - 1) << endl;
    }
    return 0;
}