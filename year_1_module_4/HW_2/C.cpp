#include <bits/stdc++.h>

struct Graph {
    explicit Graph(int n) {
        g = std::vector<std::vector<int>>(n);
        v = std::vector<bool>(n, false);
        children = std::vector<int>(n, 0);
        tin = std::vector<int>(n, 0);
        up = std::vector<int>(n, 1000000000);
    }

    std::vector<std::vector<int>> g;
    std::vector<bool> v;
    std::vector<int> children;
    std::vector<int> tin;
    std::vector<int> up;
    std::set<int> res;
    int time = 0;

    void DFS_plus(int now, bool is_root) {
        v[now] = true;
        ++time;
        tin[now] = time;
        for (int neig: g[now]) {
            if (!v[neig]) {
                ++children[now];
                DFS_plus(neig, false);
                up[now] = std::min(up[now], up[neig]);
                if (up[neig] >= tin[now] && !is_root) {
                    res.insert(now);
                }
            } else {
                up[now] = std::min(up[now], tin[neig]);
            }
        }
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph.g[a].push_back(b);
        graph.g[b].push_back(a);
    }
    for (int i = 1; i < n + 1; ++i) {
        if (!graph.v[i]) {
            graph.DFS_plus(i, true);
            if (graph.children[i] >= 2) {
                graph.res.insert(i);
            }
        }
    }
    std::cout << graph.res.size() << std::endl;
    for (int i: graph.res) {
        std::cout << i << std::endl;
    }
    return 0;
}
