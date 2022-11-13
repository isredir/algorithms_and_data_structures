#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

struct biGraph {
    int n, k;
    vector<vector<int> > g;
    vector<int> mt;
    vector<bool> used;

    biGraph(int nn, int kk) {
        n = nn;
        k = kk;
        g = vector<vector<int>>(n);
        mt = vector<int>(k, -1);
        used = vector<bool>(n, false);
    }

    bool try_kuhn(int v) {
        if (used[v]) {
            return false;
        }
        used[v] = true;
        for (int to: g[v]) {
            if (mt[to] == -1 || try_kuhn(mt[to])) {
                mt[to] = v;
                return true;
            }
        }
        return false;
    }

};

struct Graph {
    int n;
    vector<vector<int> > g;
    vector<bool> used;
    Graph(int nn) {
        n = nn;
        g = vector<vector<int>>(n);
        used = vector<bool>(n, false);
    }

    void dfs(int v) {
        used[v] = true;
        for (int neig: g[v]) {
            if (!used[neig]) {
                dfs(neig);
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int s;
    cin >> s;
    for (int t = 0; t < s; ++t) {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> table(vector<vector<int>>(n, vector<int>(k, 0)));
        biGraph graph(n, k);
        for (int i = 0; i < n; ++i) {
            while (true) {
                int a;
                cin >> a;
                if (a == 0) {
                    break;
                }
                table[i][a - 1] = 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                if (table[i][j] == 0) {
                    graph.g[i].push_back(j);
                }
            }
        }
        vector<bool> used1(n);
        for (int i = 0; i < n; ++i) {
            for (int to: graph.g[i]) {
                if (graph.mt[to] == -1) {
                    graph.mt[to] = i;
                    used1[i] = true;
                    break;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (used1[i]) {
                continue;
            }
            graph.used = vector<bool>(n, false);
            graph.try_kuhn(i);
        }
        int count = 0;
        for (int i = 0; i < k; ++i) {
            if (graph.mt[i] != -1) {
                ++count;
            }
        }
        vector<bool> in_mt(n, false);
        for (int i = 0; i < k; ++i) {
            if (graph.mt[i] != -1) {
                in_mt[graph.mt[i]] = true;
            }
        }
        Graph graph1(n + k);
        for (int i = 0; i < n; ++i) {
            for (int j : graph.g[i]) {
                if (graph.mt[j] == i) {
                    graph1.g[n + j].push_back(i);
                } else {
                    graph1.g[i].push_back(n + j);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (!in_mt[i] && !graph1.used[i]) {
                graph1.dfs(i);
            }
        }
        int countL = 0, countR = 0;
        for (int i = 0; i < n; ++i) {
            if (graph1.used[i]) {
                ++countL;
            }
        }
        for (int i = n; i < n + k; ++i) {
            if (!graph1.used[i]) {
                ++countR;
            }
        }
        cout << countL + countR << endl;
        cout << countL << " " << countR << endl;
        for (int i = 0; i < n; ++i) {
            if (graph1.used[i]) {
                cout << i + 1 << " ";
            }
        } cout << endl;
        for (int i = n; i < n + k; ++i) {
            if (!graph1.used[i]) {
                cout << i - n + 1 << " ";
            }
        } cout << endl;
    }
    return 0;
}

