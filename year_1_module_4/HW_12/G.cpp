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
    int64_t n;
    cin >> n;
    map<int64_t, int64_t> p = factorise(n);
    int64_t pr = 1;
    for (auto [i, d] : p) {
        pr *= i;
    }
    for (int i = 1; i <= 40; ++i) {
        map<int64_t, int64_t> pi = factorise(i);
        bool flag = true;
        for (auto [j, d] : p) {
            if ((pi[j] + 1) * i * pr < d) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << pr * i;
            return 0;
        }
    }
    return 0;
}