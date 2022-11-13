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

vector<bool> compute_primes(int64_t n) {
    vector<bool> primes(n + 1, true);
    primes[0] = primes[1] = false;
    for (int64_t i = 2; i * i <= n; ++i) {
        if (primes[i]) {
            if (i * i <= n) {
                for (int64_t j = i * i; j <= n; j += i) {
                    primes[j] = false;
                }
            }
        }
    }
    return primes;
}

int main() {
    int64_t m, n;
    cin >> m >> n;
    int64_t count = 0;
    vector<bool> p = compute_primes(n);
    for (int64_t i = 0; i <= n; ++i) {
        if (i >= m && p[i]) {
            ++count;
            cout << i << '\n';
        }
    }
    if (count == 0) {
        cout << "Absent" << '\n';
    }
    return 0;
}