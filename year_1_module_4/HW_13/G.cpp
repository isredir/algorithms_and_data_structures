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
    int n, m;
    cin >> n >> m;
    vector<int> p(m);
    for (int i = 0; i < m; ++i) {
        cin >> p[i];
    }
    cout << num_by_obj(p, n, m) + 1;
    return 0;
}