#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

void f(const string& str, int n, int k, int ones) {
    if (str.size() == n) {
        if (ones == k) {
            cout << str << '\n';
        }
        return;
    }
    if (ones > k) {
        return;
    }
    f(str + '0', n, k, ones);
    f(str + '1', n, k, ones + 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
    }
    do{
        for (int i : p) {
            cout << i;
        }cout << endl;
    } while (next_permutation(p.begin(), p.end()));
    return 0;
}