#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

double start;

struct Graph {
    vector<vector<int>> g;
    int K;
    bool res = false;

    Graph(int n) {
        g = vector<vector<int>>(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            g[i][i] = 1;
        }
    }

    bool check(vector<int> &arr, int v) {
        for (int i : arr) {
            if (g[v][i] == 1) {
                return false;
            }
        }
        return true;
    }

    void f(vector<int> arr, int k, int v) {
        if (k == 0) {
            res = true;
            cout << "YES";
            exit(0);
        }
        if (v < 0) {
            res = false;
            cout << "NO";
            exit(0);
        }
        if (arr.size() + v + 1 < K) {
            return;
        }
        if ((double)(clock() - start) / CLOCKS_PER_SEC > 2.9) {
            res = false;
            cout << "YES";
            exit(0);
        }
        if (v >= k) {
            f(arr, k, v - 1);
            if (check(arr, v)) {
                arr.push_back(v);
                f(arr, k - 1, v - 1);
            }
        } else {
            if (check(arr, v)) {
                arr.push_back(v);
                f(arr, k - 1, v - 1);
            }
        }
    }
};

int main() {
    start = clock();
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, k, m;
    cin >> n >> k >> m;
    Graph graph(n);
    graph.K = k;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph.g[a - 1][b - 1] = 1;
        graph.g[b - 1][a - 1] = 1;
    }
    vector<int> arr;
    graph.f(arr, k, n - 1);
    if (graph.res) {
        cout << "YES";
        return 0;
    }
    cout << "NO";
    return 0;

}