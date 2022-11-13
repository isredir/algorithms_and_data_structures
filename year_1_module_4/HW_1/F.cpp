#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

void DFS(int now, std::vector<std::unordered_set<int>> &g, std::vector<bool> &v, std::vector<int> &tree) {
    v[now] = true;
    for (int neig: g[now]) {
        if (!v[neig]) {
            DFS(neig, g, v, tree);
            tree[now] += tree[neig];
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::unordered_set<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }
    std::vector<bool> visited(n + 1, false);
    std::vector<int> tree(n + 1, 1);
    DFS(1, graph, visited, tree);
    for (int i = 1; i < n + 1; ++i) {
        std::cout << tree[i] << " ";
    }
    return 0;
}
