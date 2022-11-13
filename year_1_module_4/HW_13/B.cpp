#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

bool next_combination(vector<int>& a, int n, int k) {
    for (int i = k - 1; i >= 0; --i)
        if (a[i] < n - k + i + 1)
        {
            ++a[i];
            for (int j = i + 1; j < k; ++j) {
                a[j] = a[j - 1] + 1;
            }
            return true;
        }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> p(k);
    vector<vector<int>> s;
    for (int i = 0; i < k; ++i) {
        p[i] = i + 1;
    }
    do{
        vector<int> str(n, 0);
        for (int i : p) {
            str[i - 1] = 1;
        }
        s.push_back(str);
    } while (next_combination(p, n, k));
    for (int i = s.size() - 1; i >= 0; --i) {
        for (int j : s[i]) {
            cout << j;
        }
        cout << '\n';
    }
    return 0;
}