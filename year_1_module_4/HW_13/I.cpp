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
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    vector<int> p1 = p;
    int k = 0;
    while (true) {
        bool flag = true;
        for (int i = 1; i < n; ++i) {
            if (p1[i] != p1[i - 1] + 1 || p1[0] != 1) {
                flag = false;
                break;
            }
        }
        if (flag) {
            break;
        }
        ++k;
        vector<int> p2 = p1;
        for (int i = 0; i < n; ++i) {
            p1[i] = p2[p[i] - 1];
        }
    }
    cout << k + 1;
    return 0;
}