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
    for (int i = 0; i < k; ++i) {
        p[i] = i + 1;
    }
    do{
        for (int i : p) {
            cout << i << " ";
        }cout << '\n';
    } while (next_combination(p, n, k));
    return 0;
}