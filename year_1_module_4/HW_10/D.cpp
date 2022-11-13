#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a;
    cin >> n >> m >> a;
    vector<uint64_t> power(n + 1);
    power[1] = 0;
    for (int i = 2; i <= n; ++i) {
        power[i] = power[i / 2] + 1;
    }
    vector<vector<uint64_t>> table(power[n] + 1, vector<uint64_t>(n, 0));
    for (int i = 0; i < n; ++i) {
        table[0][i] = a;
        a = (23 * a + 21563) % 16714589;
    }
    uint64_t t = 1;
    for (int i = 1; i < power[n] + 1; ++i) {
        for (int j = 0; j + t < n; ++j) {
            table[i][j] = min(table[i - 1][j], table[i - 1][j + t]);
        }
        t *= 2;
    }
    uint64_t u, v, ans;
    cin >> u >> v;
    for (int i = 0; i < m; ++i) {
        uint64_t l = min(u, v) - 1, r = max(u, v) - 1;
        uint64_t d = r - l + 1;
        uint64_t x = power[d];
        uint64_t y = 1 << x;
        ans = min(table[x][l], table[x][r - y + 1]);
        if (i < m - 1) {
            u = ((17 * u + 751 + ans + 2 * (i + 1)) % n) + 1;
            v = ((13 * v + 593 + ans + 5 * (i + 1)) % n) + 1;
        }
    }
    cout << u << " " << v << " " << ans;
    return 0;
}