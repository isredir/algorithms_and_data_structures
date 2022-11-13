#include <bits/stdc++.h>

struct Graph {
    Graph(int n) {
        g = std::vector<std::vector<int>>(n);
        v = std::vector<bool>(n);
        time = std::vector<int>(n);
        p = std::vector<uint64_t>(n);
    }

    std::vector<std::vector<int>> g;
    std::vector<bool> v;
    std::vector<uint64_t> p;
    std::vector<int> path;
    std::vector<int> time;
};

struct Edge {
    int a;
    int b;
};

void DFS_plus(int now, Graph &graph) {
    graph.v[now] = true;
    for (int neig: graph.g[now]) {
        if (!graph.v[neig]) {
            DFS_plus(neig, graph);
            graph.p[now] += graph.p[neig];
        }
    }
    graph.path.push_back(now);
}

int main() {
    int n;
    std::cin >> n;
    Graph graph(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        std::cin >> graph.time[i];
        graph.p[i] = graph.time[i];
    }
    for (int i = 1; i < n + 1; ++i) {
        int k;
        std::cin >> k;
        for (int j = 0; j < k; ++j) {
            int b;
            std::cin >> b;
            graph.g[i].push_back(b);
        }
    }
    DFS_plus(1, graph);
    std::cout << graph.p[1] << " " << graph.path.size() << std::endl;
    for (int i : graph.path) {
        std::cout << i << " ";
    }
    return 0;
}
