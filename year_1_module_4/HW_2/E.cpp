#include <bits/stdc++.h>

struct Edge {
    int a;
    int b;
    bool operator<(const Edge &other) const {
        return (a < other.a) || (a == other.a && b < other.b);
    }
};

struct Graph {
    explicit Graph(int n) {
        g = std::vector<std::vector<int>>(n);
        g_set = std::vector<std::set<int>>(n);
        v = std::vector<bool>(n, false);
    }

    std::vector<std::vector<int>> g;
    std::vector<std::set<int>> g_set;
    std::vector<bool> v;
    std::vector<int> p;
    int num;

    void DFS(int now, int from, Graph &graph2, Graph &graph3) {
        v[now] = true;
        for (int neig: g[now]) {
            if (!v[neig]) {
                DFS(neig, now, graph2, graph3);
                graph2.g_set[neig].insert(now);
                graph3.g_set[now].insert(neig);
            } else if (neig != from) {
                if (neig > num) {
                    graph2.g_set[now].insert(neig);
                    graph3.g_set[neig].insert(now);
                } else {
                    graph2.g_set[neig].insert(now);
                    graph3.g_set[now].insert(neig);
                }
            }
        }
        p.push_back(now);
    }
    void DFS_plus(int now) {
        v[now] = true;
        for (int neig: g_set[now]) {
            if (!v[neig]) {
                DFS_plus(neig);
            }
        }
        p.push_back(now);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph graph(n + m + 1);
    graph.num = n + 1;
    Graph graph2(n + m + 1);
    Graph graph3(n + m + 1);
    std::vector<Edge> edges(m + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph.g[a].push_back(n + 1 + i);
        graph.g[n + 1 + i].push_back(a);
        graph.g[b].push_back(n + 1 + i);
        graph.g[n + 1 + i].push_back(b);
        edges[i + 1] = {a, b};
    }
    for (int i = 0; i < n + m + 1; ++i) {
        if (!graph.v[i]) {
            graph.DFS(1, -1, graph2, graph3);
        }
    }
    Graph graph4(n + 1), graph5(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        for (int j : graph2.g_set[i]) {
            if (j > n) {
                graph4.g_set[i].insert(*graph2.g_set[j].begin());
            } else {
                graph4.g_set[i].insert(j);
            }
        }
    }
    for (int i = 1; i < n + 1; ++i) {
        for (int j : graph3.g_set[i]) {
            if (j > n) {
                graph5.g_set[i].insert(*graph3.g_set[j].begin());
            } else {
                graph5.g_set[i].insert(j);
            }
        }
    }
    for (int i = 1; i < n + 1; ++i) {
        if (!graph4.v[i]) {
            graph4.DFS_plus(i);
        }
    }
    std::vector<int> c(n + 1);
    int count = 1;
    for (int j = graph4.p.size() - 1; j >= 0; --j) {
        int i = graph4.p[j];
        if (!graph5.v[i]) {
            c[i] = count;
            graph5.v[i] = true;
            std::vector<int> queue = {i};
            while (!queue.empty()) {
                int v = queue.back();
                queue.pop_back();
                for (int to: graph5.g_set[v]) {
                    if (!graph5.v[to]) {
                        c[to] = count;
                        graph5.v[to] = true;
                        queue.push_back(to);
                    }
                }
            }
            ++count;
        }
    }
    if (count - 1 > 1) {
        std::cout << 0 << std::endl;
        return 0;
    }
    for (int i = n + 1; i < n + m + 1; ++i) {
        if (*graph2.g_set[i].begin() == edges[i - n].a) {
            std::cout << edges[i - n].b << " " << edges[i - n].a << std::endl;
        } else {
            std::cout << edges[i - n].a << " " << edges[i - n].b << std::endl;
        }
    }
    return 0;
}
