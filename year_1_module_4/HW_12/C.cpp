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

vector<int64_t> factorise(int64_t a) {
    vector<int64_t> factors;
    for (int i = 2; i * i <= a; ++i) {
        while (a % i == 0) {
            factors.push_back(i);
            a /= i;
        }
    }
    if (a != 1) {
        factors.push_back(a);
    }
    return factors;
}

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}



int main() {
    int64_t a;
    cin >> a;
    for (int i : factorise(a)) {
        cout << i << " ";
    }
    return 0;
}