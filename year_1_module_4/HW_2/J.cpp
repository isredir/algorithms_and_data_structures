#include <bits/stdc++.h>

struct Graph {
    explicit Graph(int n) {
        g = std::vector<std::vector<int>>(n);
        g_set = std::vector<std::unordered_set<int>>(n);
        v = std::vector<bool>(n, false);
        children = std::vector<int>(n, 0);
        tin = std::vector<int>(n, 0);
        up = std::vector<int>(n, 1000000000);
    }

    struct Edge {
        int a;
        int b;
        bool operator<(const Edge &other) const {
            return (a < other.a) || (a == other.a && b < other.b);
        }
    };

    std::vector<std::vector<int>> g;
    std::vector<std::unordered_set<int>> g_set;
    std::vector<bool> v;
    std::vector<int> children;
    std::vector<int> tin;
    std::vector<int> up;
    std::set<int> res;
    std::map<Edge, int> edges;
    std::vector<int> path;
    int time = 0;
    int maxColor = 0;

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

    void DFS(int now, int finish) {
        v[now] = true;
        path.push_back(now);
        for (int neig: g_set[now]) {
            if (!v[neig]) {
                DFS(neig, finish);
            }
        }
        if (path.back() != finish) {
            path.pop_back();
        }
    }

    void paint(int now, int color, int from) {
        v[now] = true;
        for (int to : g[now]) {
            if (to == from) {
                continue;
            }
            if (!v[to]) {
                if (up[to] >= tin[now]) {
                    int newColor = ++maxColor;
                    edges[{to, now}] = newColor;
                    edges[{now, to}] = newColor;
                    paint(to, newColor, now);
                }
                else {
                    edges[{to, now}] = color;
                    edges[{now, to}] = color;
                    paint(to, color, now);
                }
            }
            else if (tin[to] < tin[now]) {
                edges[{to, now}] = color;
                edges[{now, to}] = color;
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
        graph.edges[{a, b}] = 0;
        graph.edges[{b, a}] = 0;
    }
    int start, finish;
    std::cin >> start >> finish;
    for (int i = 1; i < n + 1; ++i) {
        if (!graph.v[i]) {
            graph.DFS_plus(i, true);
            if (graph.children[i] >= 2) {
                graph.res.insert(i);
            }
        }
    }
    graph.v = std::vector<bool>(n + 1, false);
    for (int i = 1; i < n + 1; ++i) {
        if (!graph.v[i]) {
            graph.paint(i, graph.maxColor, -1);
        }
    }
    Graph graph2(graph.maxColor + 1);
    for (int v : graph.res) {
        for (int i = 0; i < graph.g[v].size(); ++i) {
            for (int j = i + 1; j < graph.g[v].size(); ++j) {
                if (graph.edges[{v, graph.g[v][i]}] != graph.edges[{v, graph.g[v][j]}]) {
                    graph2.g_set[graph.edges[{v, graph.g[v][i]}]].insert(graph.edges[{v, graph.g[v][j]}]);
                    graph2.g_set[graph.edges[{v, graph.g[v][j]}]].insert(graph.edges[{v, graph.g[v][i]}]);
                    graph2.edges[{graph.edges[{v, graph.g[v][i]}], graph.edges[{v, graph.g[v][j]}]}] = v;
                    graph2.edges[{graph.edges[{v, graph.g[v][j]}], graph.edges[{v, graph.g[v][i]}]}] = v;
                }
            }
        }
    }
    std::unordered_set<int> s;
    for (int i : graph.g[start]) {
        s.insert(graph.edges[{start, i}]);
    }
    for (int i : graph.g[finish]) {
        if(s.find(graph.edges[{finish, i}]) != s.end()) {
            std::cout << 0;
            return 0;
        }
    }
    graph2.DFS(graph.edges[{start, graph.g[start][0]}], graph.edges[{finish, graph.g[finish][0]}]);
    std::set<int> ans;
    for (int i = 1; i < graph2.path.size(); ++i) {
        int v = graph2.edges[{graph2.path[i], graph2.path[i - 1]}];
        if (v != start && v != finish) {
            ans.insert(graph2.edges[{graph2.path[i], graph2.path[i - 1]}]);
        }
    }
    std::cout << ans.size() << std::endl;
    for (int i : ans) {
        std::cout << i << std::endl;
    }
    return 0;
}
