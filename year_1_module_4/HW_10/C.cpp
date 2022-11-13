#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int64_t> a(n);
    int64_t maxx = -100000000000000;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        maxx = max(maxx, a[i]);
    }
    int64_t s = 0, maxS = 0;
    int neg = 0;
    for (int i = 0; i < n; ++i) {
        s += a[i];
        maxS = max(maxS, s);
        if (s < 0) {
            ++neg;
            s = 0;
        }
    }
    if (neg == n) {
        cout << maxx;
    } else {
        cout << maxS;
    }
    return 0;
}