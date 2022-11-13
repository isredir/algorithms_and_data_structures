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

vector<int> divisors(int n) {
    vector<int> d;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            d.push_back(i);
            d.push_back(n / i);
        }
    }
    return d;
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
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int64_t n;
    cin >> n;
    vector<int> arr(2 * n);
    set<int> sorted;
    for (int i = 0; i < 2 * n; ++i) {
        cin >> arr[i];
        sorted.insert(arr[i]);
    }
    if (n == 1) {
        cout << arr[0] << " " << 0;
        return 0;
    }
    if (sorted.size() == 1) {
        cout << arr[0] << " " << 0;
        return 0;
    }
    while (true) {
        int i = rand() % (2 * n - 1);
        int j = rand() % (2 * n - 2);
        if (i == j) {
            ++j;
        }
        int a = min(arr[i], arr[j]), b = max(arr[i], arr[j]);
        int d = b - a;
        for (int div: divisors(d)) {
            int count = 1;
            int aa = a;
            while (sorted.find(aa + div) != sorted.end()) {
                aa += div;
                ++count;
            }
            aa = a;
            while (sorted.find(aa - div) != sorted.end()) {
                aa -= div;
                ++count;
            }
            if (count >= n) {
                cout << aa << " " << div;
                return 0;
            }
        }
    }
    return 0;
}