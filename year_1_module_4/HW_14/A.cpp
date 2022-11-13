#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    if (n == 1) {
        cout << 0;
        return 0;
    }
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    int64_t min_sum = 1000000000000000;
    do{
        int64_t s = 0;
        bool flag = true;
        if (g[p[0]][p[n - 1]] != 0) {
            s += g[p[0]][p[n - 1]];
        } else {
            continue;
        }
        for (int i = 1; i < n; ++i) {
            if (g[p[i]][p[i - 1]] != 0) {
                s += g[p[i]][p[i - 1]];
            } else {
                flag = false;
                break;
            }
        }
        if (flag) {
            min_sum = min(min_sum, s);
        }
    } while (next_permutation(p.begin(), p.end()));
    if (min_sum == 1000000000000000) {
        cout << -1;
    } else {
        cout << min_sum;
    }
    return 0;
}