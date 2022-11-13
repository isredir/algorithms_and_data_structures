#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

void DFS(int now, std::vector<std::unordered_set<int>> &g, std::vector<bool> &v) {
    v[now] = true;
    for (size_t neig: g[now]) {
        if (!v[neig]) {
            DFS(neig, g, v);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::unordered_set<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }
    std::vector<bool> visited(n + 1, false);
    DFS(1, graph, visited);
    std::set<int> component;
    for (int i = 1; i < n + 1; ++i) {
        if (visited[i]) {
            component.insert(i);
        }
    }
    std::cout << component.size() << std::endl;
    for (int vertex: component) {
        std::cout << vertex << " ";
    }
    return 0;
}
