#include <iostream>
#include <vector>
#include <unordered_set>

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
    std::vector<bool> visited(n + 1);
    std::vector<int> coloring(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        if (!visited[i]) {
            visited[i] = true;
            coloring[i] = 1;
            std::vector<int> queue = {i};
            while (!queue.empty()) {
                int v = queue.back();
                queue.pop_back();
                for (int to: graph[v]) {
                    if (!visited[to]) {
                        coloring[to] = 3 - coloring[v];
                        visited[to] = true;
                        queue.push_back(to);
                    }
                }
            }
        }
    }
    for (int i = 1; i < n + 1; ++i) {
        for (int v: graph[i]) {
            if (coloring[v] == coloring[i]) {
                std::cout << "NO" << std::endl;
                return 0;
            }
        }
    }
    std::cout << "YES" << std::endl;
    return 0;
}
