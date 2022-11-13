#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<uint64_t> power(n + 1);
    power[1] = 0;
    for (int i = 2; i <= n; ++i) {
        power[i] = power[i / 2] + 1;
    }
    vector<uint64_t> a(n);
    vector<vector<uint64_t>> table(power[n] + 1, vector<uint64_t>(n, 0));
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        table[0][i] = a[i];
    }
    uint64_t t = 1;
    for (int i = 1; i < power[n] + 1; ++i) {
        for (int j = 0; j + t < n; ++j) {
            table[i][j] = min(table[i - 1][j], table[i - 1][j + t]);
        }
        t *= 2;
    }
    int q;
    cin >> q;
    uint64_t s = 0;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        int d = r - l + 1;
        uint64_t x = power[d];
        uint64_t y = 1 << x;
        s += min(table[x][l], table[x][r - y + 1]);
    }
    cout << s;
    return 0;
}