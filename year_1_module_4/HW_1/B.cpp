#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

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
    int count = 0;
    std::vector<std::set<int>> components;
    for (int i = 1; i < n + 1; ++i) {
        if (!visited[i]) {
            ++count;
            components.emplace_back();
            components.back().insert(i);
            visited[i] = true;
            std::vector<int> queue = {i};
            while (!queue.empty()) {
                int v = queue.back();
                queue.pop_back();
                for (int to: graph[v]) {
                    if (!visited[to]) {
                        components.back().insert(to);
                        visited[to] = true;
                        queue.push_back(to);
                    }
                }
            }
        }
    }
    std::cout << components.size() << std::endl;
    for (const auto &component: components) {
        std::cout << component.size() << std::endl;
        for (int v: component) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
