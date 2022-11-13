#include <bits/stdc++.h>

struct Graph {
    Graph(int n) {
        g = std::vector<std::vector<int>>(n);
        v = std::vector<bool>(n);
    }

    std::vector<std::vector<int>> g;
    std::vector<bool> v;
    std::vector<int> p;
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
        }
    }
    graph.p.push_back(now);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph graph(n + 1);
    Graph graph2(n + 1);
    std::vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph.g[a].push_back(b);
        graph2.g[b].push_back(a);
        edges.push_back({a, b});
    }
    for (int i = 1; i < n + 1; ++i) {
        if (!graph.v[i]) {
            DFS_plus(i, graph);
        }
    }
    std::vector<int> c(n + 1);
    int count = 1;
    for (int j = n - 1; j >= 0; --j) {
        int i = graph.p[j];
        if (!graph2.v[i]) {
            c[i] = count;
            graph2.v[i] = true;
            std::vector<int> queue = {i};
            while (!queue.empty()) {
                int v = queue.back();
                queue.pop_back();
                for (int to: graph2.g[v]) {
                    if (!graph2.v[to]) {
                        c[to] = count;
                        graph2.v[to] = true;
                        queue.push_back(to);
                    }
                }
            }
            ++count;
        }
    }
    std::cout << count - 1 << std::endl;
    for (int i = 1; i < n + 1; ++i) {
        std::cout << c[i] << " ";
    } std::cout << std::endl;
    return 0;
}
