#include <bits/stdc++.h>

using namespace std;

const int maxN = 8 * 100000;

struct node {
    int64_t sum, add;
};

node t[maxN];

const int INF = 1000000000;

void build(const vector<int64_t>& a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v].sum = a[tl];
        t[v].add = 0;
    }
    else {
        int d = (tl + tr) / 2;
        build (a, v * 2, tl, d);
        build (a, v * 2 + 1, d + 1, tr);
        t[v].sum = t[v * 2].sum + t[v * 2 + 1].sum;
        t[v].add = 0;
    }
}

void push(int v, int tl, int tr) {
    if (t[v].add != 0) {
        int d = (tl + tr) / 2;
        t[v * 2].add += t[v].add;
        t[v * 2].sum += (d - tl + 1) * t[v].add;
        t[v * 2 + 1].add += t[v].add;
        t[v * 2 + 1].sum += (tr - d) * t[v].add;
        t[v].add = 0;
    }
}

void update(int v, int tl, int tr, int l, int r, int64_t new_val) {
    if (l > r) {
        return;
    }
    if (tl == l && tr == r) {
        t[v].add += new_val;
        t[v].sum += (r - l + 1) * new_val;
        return;
    }
    int d = (tl + tr) / 2;
    push(v, tl, tr);
    update(v * 2, tl, d, l, min(r,d), new_val);
    update(v * 2 + 1, d + 1, tr, max(l, d + 1), r, new_val);
    t[v].sum = t[v * 2].sum + t[v * 2 + 1].sum;
}

int64_t get_sum(int v, int tl, int tr, int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l == tl && r == tr) {
        return t[v].sum;
    }
    int d = (tl + tr) / 2;
    push(v, tl, tr);
    return get_sum(v * 2, tl, d, l, min(r,d)) + get_sum(v * 2 + 1, d + 1, tr, max(l, d + 1), r);
}

int main() {
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build(a, 1, 0, n - 1);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int b;
        cin >> b;
        if (b == 1) {
            int l, r;
            cin >> l >> r;
            cout << get_sum(1, 0, n - 1, l, r) << endl;
        } else {
            int l, r;
            int64_t x;
            cin >> l >> r >> x;
            update(1, 0, n - 1, l, r, x);
        }
    }
    return 0;
}