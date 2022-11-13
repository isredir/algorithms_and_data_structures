#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<uint64_t> a(n);
    vector<uint64_t> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }
    uint64_t q, cur1;
    cin >> q >> cur1;
    uint64_t cur2 = (11173 * cur1 + 1) % 1000000007;
    uint64_t s = 0;
    for (int i = 0; i < q; ++i) {
        uint64_t l = min(cur1 % n, cur2 % n) + 1;
        uint64_t r = max(cur1 % n, cur2 % n) + 1;
        s += (pref[r] - pref[l - 1]);
        s %= 1000000007;
        cur1 = (11173 * cur2 + 1) % 1000000007;
        cur2 = (11173 * cur1 + 1) % 1000000007;
    }
    cout << s % 1000000007;
    return 0;
}