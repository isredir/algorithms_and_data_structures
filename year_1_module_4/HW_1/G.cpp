#include <iostream>
#include <vector>
#include <unordered_set>

void DFS(int now, std::vector<std::unordered_set<int>> &g, std::vector<bool> &v, std::vector<int> &tree,
         std::vector<int> &queue) {
    v[now] = true;
    int pos = 0;
    queue[pos] = now;
    int from;
    while (pos >= 0) {
        from = queue[pos];
        queue[pos--] = 0;
        for (int to: g[from]) {
            if (!v[to]) {
                v[to] = true;
                tree[to] = tree[from] + 1;
                queue[++pos] = to;
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
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
    std::vector<int> queue(n + 1);
    std::vector<int> tree(n + 1, 0);
    DFS(1, graph, visited, tree, queue);
    int new_root = 0;
    int max_path = 0;
    for (int i = 1; i < n + 1; ++i) {
        visited[i] = false;
        if (tree[i] > max_path) {
            max_path = tree[i];
            new_root = i;
        }
        tree[i] = 0;
    }
    DFS(new_root, graph, visited, tree, queue);
    max_path = 0;
    for (int num: tree) {
        max_path = std::max(max_path, num);
    }
    std::cout << max_path << std::endl;
    return 0;
}
