#include <bits/stdc++.h>

struct Graph {
    explicit Graph(int n) {
        g = std::vector<std::vector<int>>(n);
        v = std::vector<bool>(n, false);
        children = std::vector<int>(n, 0);
        neighbours = std::vector<int>(n, 0);
        tin = std::vector<int>(n, 0);
        up = std::vector<int>(n, 1000000000);
        tree = std::vector<int>(n + 1, 1);
    }

    std::vector<std::vector<int>> g;
    std::vector<bool> v;
    std::vector<int> children;
    std::vector<int> neighbours;
    std::vector<int> tin;
    std::vector<int> up;
    std::set<int> res;
    int time = 0;
    std::vector<int> tree;

    void DFS(int now) {
        v[now] = true;
        for (int neig: g[now]) {
            if (!v[neig]) {
                DFS(neig);
                tree[now] += tree[neig];
            }
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    Graph graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph.g[a].push_back(b);
        graph.g[b].push_back(a);
    }
    graph.DFS(1);
    for (int i = 1; i < n + 1; ++i) {
        std::set<int> s;
        for (int neig : graph.g[i]) {
            if (graph.tree[neig] > graph.tree[i]) {
                s.insert(n - graph.tree[i]);
            } else {
                s.insert(graph.tree[neig]);
            }
        }
        if (graph.g[i].size() > 1 && s.size() == 1) {
            std::cout << i << std::endl;
            return 0;
        }
    }
    std::cout << -1 << std::endl;
    return 0;
}