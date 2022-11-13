#include <bits/stdc++.h>

using namespace std;

const int maxN = 8 * 100000;

const int64_t INF = 10000000000;

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


int find_kth(int v, int tl, int tr, int k) {
    if (k > t[v]) {
        return -1;
    }
    if (tl == tr) {
        return tl;
    }
    int d = (tl + tr) / 2;
    if (t[v * 2] >= k) {
        return find_kth(v * 2, tl, d, k);
    } else {
        return find_kth(v * 2 + 1, d + 1, tr, k - t[v * 2]);
    }
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


int main() {
    int n;
    cin >> n;
    vector<int64_t> a(n);
    vector<int64_t> b(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a[i] = 1 - abs(x) % 2;
        b[i] = x;
    }
    build(a, 1, 0, n - 1);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y, z, w;
        cin >> x;
        if (x == 1) {
            cin >> y >> z >> w;
            int l = 1, r = n;
            int pos1, pos2;
            while (l < r) {
                int d = (l + r) / 2;
                int pos = find_kth(1, 0, n - 1, d);
                if (pos == -1 || pos >= y) {
                    r = d;
                } else {
                    l = d + 1;
                }
            }
            pos1 = l - 1;
            pos2 = find_kth(1, 0, n - 1, pos1 + w);
            if (pos2 == -1 || pos2 > z) {
                cout << "NONE" << endl;
            } else {
                cout << b[pos2] << endl;
            }
        } else {
            cin >> y >> z;
            b[y] = z;
            z = 1 - abs(z) % 2;
            update(1, 0, n - 1, y, z);
        }
    }
    return 0;
}