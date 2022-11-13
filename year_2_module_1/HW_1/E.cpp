#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

vector<int64_t> prefix_function(string s) {
    vector<int64_t> p(s.size());
    for (int i = 1; i < s.size(); ++i) {
        int64_t j = p[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = p[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        p[i] = j;
    }
    return p;
}

vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int64_t n, a, k;
    cin >> n >> a >> k;
    string s;
    cin >> s;

    s += "#";
    vector<int64_t> pi = prefix_function(s);
    vector<vector<int64_t>> aut(n, vector<int64_t>(a));
    for (int i = 0; i < n; ++i) {
        for (char c = 'a'; c < 'a' + a; ++c) {
            if (i > 0 && c != s[i]) {
                aut[i][c - 'a'] = aut[pi[i - 1]][c - 'a'];
            } else {
                aut[i][c - 'a'] = i + (c == s[i]);
            }
        }
    }
    int64_t maxx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < a; ++j) {
            maxx = max(maxx, i - aut[i][j]);
        }
    }
    int64_t ans = n + k * maxx;
    cout << ans;
    return 0;
}