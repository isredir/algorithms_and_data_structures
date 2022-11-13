#include <bits/stdc++.h>

using namespace std;

const int maxN = 3 * 100000;

multiset<int> t[maxN];

const int INF = 1000000000;

void build(const vector<int> &a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = {a[tl]};
    } else {
        int d = (tl + tr) / 2;
        build(a, v * 2, tl, d);
        build(a, v * 2 + 1, d + 1, tr);
        merge(t[v * 2].begin(), t[v * 2].end(), t[v * 2 + 1].begin(), t[v * 2 + 1].end(), inserter(t[v], t[v].begin()));
    }
}

int lower_bound(int v, int tl, int tr, int l, int r, int x) {
    if (l > r) {
        return INF;
    }
    if (l == tl && tr == r) {
        auto pos = t[v].upper_bound(x);
        if (pos != t[v].end()) {
            return *pos;
        }
        return INF;
    }
    int tm = (tl + tr) / 2;
    return min(lower_bound(v * 2, tl, tm, l, min(r, tm), x), lower_bound(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x));
}

void update(vector<int> &a, int v, int tl, int tr, int pos, int new_val) {
    t[v].erase(t[v].find(a[pos]));
    t[v].insert(new_val);
    if (tl != tr) {
        int d = (tl + tr) / 2;
        if (pos <= d) {
            update(a, v * 2, tl, d, pos, new_val);
        }
        else {
            update(a, v * 2 + 1, d + 1, tr, pos, new_val);
        }
    } else {
        a[pos] = new_val;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
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
            int l, r, x;
            cin >> l >> r >> x;
            int pos = lower_bound(1, 0, n - 1, l, r, x);
            if (pos == INF) {
                cout << "NONE" << endl;
            } else {
                cout << pos << endl;
            }
        } else {
            int j, x;
            cin >> j >> x;
            update(a, 1, 0, n - 1, j, x);
        }
    }
    return 0;
}