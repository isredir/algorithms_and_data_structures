#include <bits/stdc++.h>

//#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const int N = (int) 2010;
int n;

int go[N * N][26];
bool term[N * N], good[N * N];
int depth[N * N], r[N * N], l[N * N];

int len = 1;

int add (const string& s) {
    int node = 0;
    for (int i = 0; i < s.size(); node = go[node][s[i++] - 'a']) {
        if (go[node][s[i] - 'a'] == 0) {
            go[node][s[i] - 'a'] = len++;
        }
    }
    term[node] = true;
    return node;
}

void dfs(int v) {
    if (l[v] == 0) {
        l[v] = n + 1;
    }
    if (term[v]) {
        good[v] = true;
    }
    int count = 0;
    for (char c = 'a'; c <= 'z'; ++c) {
        if (go[v][c - 'a'] != 0) {
            depth[go[v][c - 'a']] = depth[v] + 1;
            dfs(go[v][c - 'a']);
            ++count;
            l[v] = min(l[v], l[go[v][c - 'a']]);
            r[v] = max(r[v], r[go[v][c - 'a']]);
        }
    }
    if (count > 1) {
        good[v] = true;
    }
}

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

int BC[N][N], CA[N][N], h[N][N];

void pairs (int d[N][N], const string& s1, const string& s2) {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p = prefix_function(s2.substr(i, n - i) + '#' + s1);
        for (int j = n - i + 1; j <= 2 * n - i; j++) {
            h[j - n + i - 1][i] = p[j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j >= 0; --j) {
            d[i][j] = h[i][j];
            if (i > 0) {
                d[i][j] = max(d[i][j], d[i - 1][j]);
            }
            if (j < n - 1) {
                d[i][j] = max(d[i][j], d[i][j + 1]);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    cin >> n;
    string A, B, C;
    cin >> A >> B >> C;
    pairs(BC, B, C);
    pairs(CA, C, A);
    for (int i = 0; i < n; ++i) {
        int node = add(A.substr(i, n - i));
        if (l[node] == 0) {
            l[node] = i + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        int node = add(B.substr(i, n - i));
        r[node] = i + 1;
    }
    dfs(0);
    int res = 0;
    for (int i = 1; i < len; ++i) {
        if (good[i] && l[i] != n + 1 && r[i] != 0) {
            l[i]--;
            r[i]--;
            for (int j = 0; j <= n; j++) {
                int max_len = 0;
                if (r[i] != 0) {
                    max_len += BC[r[i]- 1][j];
                }
                if (j != 0) {
                    max_len += CA[j - 1][l[i] + depth[i]];
                }
                res = max(res, depth[i] + max_len);
            }
        }
    }
    for (int j = 0; j <= n; j++) {
        int max_len = BC[n - 1][j];
        if (j != 0) {
            max_len += CA[j - 1][0];
        }
        res = max(res, max_len);
    }

    cout << res << endl;

    return 0;
}