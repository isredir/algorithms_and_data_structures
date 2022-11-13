#include <bits/stdc++.h>

using namespace std;

const int maxN = 8 * 100000;

int64_t t[maxN];

void build(const vector<int64_t> &a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int d = (tl + tr) / 2;
        build(a, v * 2, tl, d);
        build(a, v * 2 + 1, d + 1, tr);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

int64_t sum(int v, int tl, int tr, int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l == tl && r == tr) {
        return t[v];
    }
    int d = (tl + tr) / 2;
    return sum(v * 2, tl, d, l, min(r, d)) + sum(v * 2 + 1, d + 1, tr, max(l, d + 1), r);
}

void update(int v, int tl, int tr, int pos, int64_t new_val) {
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

int pref(int v, int tl, int tr, int64_t s) {
    if (s > t[v]) {
        return -1;
    }
    if (tl == tr) {
        return tl;
    }
    int d = (tl + tr) / 2;
    if (t[v * 2] >= s) {
        return pref(v * 2, tl, d, s);
    } else {
        return pref(v * 2 + 1, d + 1, tr, s - t[v * 2]);
    }
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
        int x;
        cin >> x;
        if (x == 1) {
            int64_t y;
            cin >> y;
            if (y == 0) {
                cout << 0 << endl;
                continue;
            }
            int pos = pref(1, 0, n - 1, y);
            if (pos == -1) {
                cout << "NONE" << endl;
            } else {
                cout << pos + 1 << endl;
            }
        } else {
            int y;
            int64_t z;
            cin >> y >> z;
            update(1, 0, n - 1, y, z);
        }
    }
    return 0;
}