#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

struct Graph {
    int n, k;
    vector<vector<int> > g;
    vector<int> mt;
    vector<bool> used;

    Graph(int nn, int kk) {
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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    string name;
    cin >> name;
    int k = name.size();
    if (n < k) {
        cout << "NO";
        return 0;
    }
    Graph graph(n, k);
    vector<string> cubes(n);
    for (int i = 0; i < n; ++i) {
        cin >> cubes[i];
        for (char c : cubes[i]) {
            for (int j = 0; j < k; ++j) {
                if (name[j] == c) {
                    graph.g[i].push_back(j);
                }
            }
        }
    }
    vector<bool> used1(n);
    for (int i = 0; i < n; ++i) {
        for (int to : graph.g[i]) {
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
    if (count < k) {
        cout << "NO";
        return 0;
    } else {
        cout << "YES" << endl;
    }
    for (int i = 0; i < k; ++i) {
        if (graph.mt[i] != -1) {
            cout << graph.mt[i] + 1 << " ";
        }
    }
    return 0;
}

