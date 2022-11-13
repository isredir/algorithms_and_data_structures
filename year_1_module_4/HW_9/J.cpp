#include <bits/stdc++.h>

using namespace std;

const int maxN = 8 * 100000;

struct query {
    int l ,r, i;
    bool operator<(const query& other) const {
        return r < other.r;
    }
};

int t[maxN];

const int INF = 1000000000;

void build(const vector<int>& a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    }
    else {
        int d = (tl + tr) / 2;
        build (a, v * 2, tl, d);
        build (a, v * 2 + 1, d + 1, tr);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}



void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int d = (tl + tr) / 2;
        if (pos <= d) {
            update(v * 2, tl, d, pos, new_val);
        } else {
            update(v * 2 + 1, d + 1, tr, pos, new_val);
        }
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

int get_sum(int v, int tl, int tr, int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l == tl && r == tr) {
        return t[v];
    }
    int d = (tl + tr) / 2;
    return get_sum(v * 2, tl, d, l, min(r,d)) + get_sum(v * 2 + 1, d + 1, tr, max(l, d + 1), r);
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> b = a;
    sort(b.begin(), b.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }
    vector<int> next(n, - 1);
    int q;
    cin >> q;
    vector<query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].i = i;
    }
    sort(queries.begin(), queries.end());
    int ind = 0;
    vector<int> ans(q);
    for (int r = 0; r < n; r++) {
        int x = a[r];
        if (next[x] != -1) {
            update(1, 0, n - 1, next[x], 0);
        }
        next[x] = r;
        update(1, 0, n - 1, next[x], 1);
        while (ind < q && queries[ind].r == r) {
            ans[queries[ind].i] = get_sum(1, 0, n - 1, queries[ind].l, queries[ind].r);
            ++ind;
        }
    }
    for (int i : ans) {
        cout << i << '\n';
    }
    return 0;
}