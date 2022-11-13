#include <iostream>
#include <vector>
#include <unordered_set>

void DFS(int now, std::vector<std::unordered_set<int>> &g, std::vector<int> &v, std::vector<int> &t, bool &flag) {
    if (!flag) { return; }
    v[now] = 1;
    for (int neig: g[now]) {
        if (v[neig] == 1) {
            flag = false;
            return;
        }
        if (v[neig] == 0) {
            DFS(neig, g, v, t, flag);
        }
    }
    v[now] = 2;
    t.push_back(now);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::unordered_set<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].insert(b);
    }
    std::vector<int> visited(n + 1, 0);
    std::vector<int> top_sort;
    bool flag = true;
    for (int i = 1; i < n + 1; ++i) {
        if (visited[i] == 0 && flag) {
            DFS(i, graph, visited, top_sort, flag);
        }
    }
    if (!flag) {
        std::cout << -1;
        return 0;
    }
    for (int i = n - 1; i >= 0; --i) {
        std::cout << top_sort[i] << " ";
    }
    return 0;
}
