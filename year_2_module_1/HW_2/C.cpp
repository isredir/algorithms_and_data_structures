#include <bits/stdc++.h>

//#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const int N = (int) 1e6 + 1;

struct Node {
    int suf = -1;
    int go[26];
    int term_link = -1;
    bool term = false;
    int depth = 0;
    Node() {
        memset(go, -1, sizeof(go));
    }
};

Node Nodes[N];

int len = 0;

int q[N];

struct Bor {
    set<char> alphabet;
    Bor() {
        for (char c = 'a'; c <= 'z'; ++c) {
            alphabet.insert(c);
        }
    }

    void add (const string& s) {
        int node = 0;
        for (int i = 0; i < s.size(); node = Nodes[node].go[s[i++] - 'a']) {
            if (Nodes[node].go[s[i] - 'a'] == -1) {
                Nodes[node].go[s[i] - 'a'] = ++len;
                Nodes[len].depth = Nodes[node].depth + 1;
            }
        }
        Nodes[node].term = true;
    }

    void build_automat() {
        int qh = 0, qe = 0;
        for (char c : alphabet) {
            if (Nodes[0].go[c - 'a'] != -1) {
                Nodes[Nodes[0].go[c - 'a']].suf = 0;
                q[qe++] = Nodes[0].go[c - 'a'];
            } else {
                Nodes[0].go[c - 'a'] = 0;
            }
        }
        while (qh < qe) {
            int v = q[qh++];
            int link = Nodes[v].suf;
            Nodes[v].term_link = Nodes[link].term_link;
            if (Nodes[link].term) {
                Nodes[v].term_link = link;
            }
            for (char c : alphabet) {
                if (Nodes[v].go[c - 'a'] != -1) {
                    Nodes[Nodes[v].go[c - 'a']].suf = Nodes[link].go[c - 'a'];
                    q[qe++] = Nodes[v].go[c - 'a'];
                } else {
                    Nodes[v].go[c - 'a'] = Nodes[link].go[c - 'a'];
                }
            }
        }
    }
};

vector<int> g[N];
int p[N], intime[N], outtime[N], d[N];
char text[N];

struct Graph {
    int curtime = 0;

    void set_parent(int u, int v) {
        p[u] = v;
        g[v].push_back(u);
    }

    void dfs(int v) {
        intime[v] = ++curtime;
        for (int i = 0; i < (int) g[v].size(); ++i) {
            d[g[v][i]] = d[v] + 1;
            dfs(g[v][i]);
        }
        outtime[v] = ++curtime;
    }

    bool is_parent(int u, int v) {
        return (intime[u] <= intime[v]) && (outtime[v] <= outtime[u]);
    }

    int get_path(int u, int v) {
        if (is_parent(v, u)) {
            return d[u] - d[v];
        } else {
            return -1;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    Bor bor;
    for (int i = 0; i < n; i++) {
        cin >> text;
        bor.add(text);
    }
    bor.build_automat();
    cin >> text;
    n = strlen(text);
    int j = 0, k = 0;
    Graph graph;
    memset(p, -1, sizeof(p));
    for (int i = 0; i < n; ++i) {
        k = j = Nodes[j].go[text[i] - 'a'];
        if (!Nodes[k].term) {
            k = Nodes[k].term_link;
        }
        while (k != -1) {
            graph.set_parent(i - Nodes[k].depth + 1, i + 1);
            k = Nodes[k].term_link;
        }
    }
    for (int i = n; i >= 0; --i) {
        if (p[i] == -1) graph.dfs(i);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        cout << graph.get_path(u, v) << endl;
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int sum = 0, t, a, b, c, d, e, l, r;
        cin >> t >> a >> b >> c >> d >> e >> l >> r;
        for (int jj = 0; jj < t; ++jj) {
            int ans = graph.get_path(min(l % n, r % n), max(l % n, r % n) + 1);
            if (ans != -1) sum = (sum + ans) % e;
            l = (a * l + b) % e, r = (c * r + d + ans) % e;
        }
        cout << sum << endl;
    }
    return 0;
}