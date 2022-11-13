#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const int64_t fact[13] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

int64_t num_by_obj(vector<int>& a, int n, int m) {
    int64_t res = 0;
    vector<bool> used(n + 1, false);
    int nn = n - 1, mm = m - 1;
    for (int i : a) {
        int count = 0;
        for (int j = 1; j <= n; ++j) {
            if (!used[j]) {
                ++count;
            }
            if (i == j) {
                res += (count - 1) * fact[nn] / fact[nn - mm];
                used[j] = true;
            }
        }
        used[i] = true;
        --nn;
        --mm;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int64_t>> dp (42, vector<int64_t>(10, 0));
    for (int i = 1; i < 42; ++i) {
        dp[i][9] = 1;
        for (int j = 8; j >= 1; --j) {
            dp[i][j] = dp[i][j + 1] + dp[i - 1][j];
        }
    }
    int64_t m = n;
    while (m > 0) {
        int64_t s = 1;
        bool flag = false;
        for (int i = 1; i < 42; ++i) {
            int64_t s_row = 0;
            for (int j = 1; j < 10; ++j) {
                s_row += dp[i][j];
                s += dp[i][j];
                if (s > m) {
                    flag = true;
                    cout << j;
                    m -= s_row;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
    }
    return 0;
}