#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

vector<int> prefix_function(string s) {
    vector<int> p(s.size());
    for (int i = 1; i < s.size(); ++i) {
        int j = p[i - 1];
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
    string a, b, s;
    cin >> a >> b;
    if (a.size() > b.size()) {
        cout << 0;
        return 0;
    }
    set<int> pos;
    s = a + b;
    vector<int> z1 = z_function(s);
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    s = a + b;
    vector<int> z2 = z_function(s);
    reverse(z2.begin(), z2.end());
    set<int> nums;
    for (int i = 0; i <= b.size() - a.size(); ++i) {
        if (z1[a.size() + i] + z2[a.size() + i - 1] >= a.size() - 1) {
            nums.insert(i + 1);
        }
    }
    cout << nums.size() << endl;
    for (int i : nums) {
        cout << i << " ";
    }
    return 0;
}