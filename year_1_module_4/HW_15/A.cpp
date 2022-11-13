#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

int n, m;
vector<vector<int>> g, h;
vector<set<int>> g_set;
vector<int> p;

bool cmp(int a, int b) {
    return g[a].size() < g[b].size() || (g[a].size() == g[b].size() && a < b);
}

struct triangle {
    int a, b, c;

    bool operator<(const triangle &other) const {
        return (a < other.a) || (a == other.a && b < other.b) || (a == other.a && b == other.b && c < other.c);
    }

    bool operator==(const triangle &other) const {
        return (a == other.a && b == other.b && c == other.c) || (a == other.b && b == other.c && c == other.a) ||
               (a == other.c && b == other.a && c == other.b);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    cin >> n >> m;
    g = vector<vector<int>>(n);
    h = vector<vector<int>>(n);
    g_set = vector<set<int>>(n);
    p = vector<int>(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int v = 0; v < n; ++v) {
        for (int u : g[v]) {
            if (cmp(u, v)) {
                h[u].push_back(v);
            }
        }
    }
    int ans = 0;
    set<triangle> triangles;
    vector<int> cnt(n, false);
    for (int v : p) {
        for (int w: h[v]) {
            cnt[w]++;
        }
        for (int u: h[v]) {
            for (int w: h[u]) {
                ans += cnt[w];
            }
        }
        for (int w: h[v]) {
            cnt[w]--;
        }
    }
    cout << ans;

}