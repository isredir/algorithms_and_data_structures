#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

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

map<int64_t, int64_t> factorise(int64_t a) {
    map<int64_t, int64_t> factors;
    for (int i = 2; i * i <= a; ++i) {
        while (a % i == 0) {
            ++factors[i];
            a /= i;
        }
    }
    if (a != 1) {
        ++factors[a];
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
    int64_t n, m;
    cin >> n >> m;
    auto p = factorise(m);
    int64_t count = 1000000000000000;
    for (auto [i, d] : p) {
        int64_t s = 0;
        for (int64_t j = i; j <= n; j *= i) {
            s += n / j;
        }
        count = min(count, s / d);
    }
    cout << count;
    return 0;
}