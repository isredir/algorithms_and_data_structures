#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const int64_t fact[13] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

int64_t num_by_obj(vector<int> &a, int n, int m) {
    int64_t res = 0;
    vector<bool> used(n + 1, false);
    int nn = n - 1, mm = m - 1;
    for (int i: a) {
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

vector<vector<int64_t>> all_sets(int n) {
    if (n >= 15) {
        n -= 2;
    }
    vector<vector<int64_t>> v(1 << (n));
    for (int i = 0; i < (1 << (n)); ++i) {
        int m = i;
        int k = 0;
        string str;
        while (m > 0) {
            str = to_string((m % 2)) + str;
            m /= 2;
            ++k;
        }
        while (str.size() < n) {
            str = "0" + str;
        }
        for (int j = 0; j < str.size(); ++j) {
            if (str[j] == '1') {
                v[i].push_back(j + 1);
            }
        }
//        for (long long j : v[i]) {
//            cout << j << " ";
//        }cout << endl;
    }
    return v;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    int64_t max_s = 0;
    vector<int> max_col(n, 1);
    for (const auto& v : all_sets(n)) {
        vector<int> col(n, 1);
        for (int64_t i : v) {
            col[i - 1] = 2;
        }
        int64_t s = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (col[i] != col[j]) {
                    s += g[i][j];
                }
            }
        }
        if (s > max_s) {
            max_s = s;
            max_col = col;
        }
    }
    cout << max_s << endl;
    for (int i = 0; i < n; ++i) {
        cout << max_col[i] << " ";
    }

//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            cout << g[i][j] << " ";
//        }cout << endl;
//    }

    return 0;
}