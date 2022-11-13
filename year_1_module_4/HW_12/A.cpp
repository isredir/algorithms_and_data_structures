#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

int64_t bin_pow(int64_t a, int64_t n, int64_t p) {
    if (n == 0) {
        return 1;
    }
    if (n % 2 == 1) {
        int64_t b = bin_pow(a, n - 1, p);
        return (a * b) % p;
    }
    int64_t b = bin_pow(a, n / 2, p);
    return (b * b) % p;
}

int main() {
    int64_t n, m, p;
    cin >> n >> m >> p;
    cout << bin_pow(n, m, p) % p << endl;
    return 0;
}