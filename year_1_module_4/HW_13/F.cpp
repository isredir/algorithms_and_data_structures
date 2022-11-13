#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const int64_t fact[13] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

vector<int> perm_by_num(int64_t n, int64_t num) {
    vector<int> res(n);
    vector<bool> used(n + 1, false);
    for (int i = 0; i < n; ++i) {
        int64_t block = (num - 1) / fact[n - i - 1] + 1;
        int j, pos = 0;
        for (j = 1; j <= n; ++j) {
            if (!used[j]) {
                ++pos;
            }
            if (pos == block) {
                break;
            }
        }
        res[i] = j;
        used[j] = true;
        num = (num - 1) % fact[n - i - 1] + 1;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int64_t n, m;
    cin >> n >> m;
    for (int i : perm_by_num(n, m)) {
        cout << i << " ";
    }
    return 0;
}