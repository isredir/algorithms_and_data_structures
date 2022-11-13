#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>

void DFS(int now, std::unordered_map<int, std::unordered_set<int>> &g, std::vector<bool> &v) {
    v[now] = true;
    for (int neig: g[now]) {
        if (!v[neig]) {
            DFS(neig, g, v);
        }
    }
}


int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<char>> table;
    std::unordered_map<int, std::unordered_set<int>> graph(n * n);
    int num = 0;
    for (int i = 0; i < n; ++i) {
        table.emplace_back();
        for (int j = 0; j < n; ++j) {
            char a;
            std::cin >> a;
            table.back().push_back(a);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (table[i][j] == '.') {
                if (i - 1 >= 0 && table[i - 1][j] == '.') {
                    graph[num - n].insert(num);
                    graph[num].insert(num - n);
                }
                if (j - 1 >= 0 && table[i][j - 1] == '.') {
                    graph[num - 1].insert(num);
                    graph[num].insert(num - 1);
                }
                if (i + 1 < n && table[i + 1][j] == '.') {
                    graph[num + n].insert(num);
                    graph[num].insert(num + n);
                }
                if (j + 1 < n && table[i][j + 1] == '.') {
                    graph[num + 1].insert(num);
                    graph[num].insert(num + 1);
                }
            }
            ++num;
        }
    }
    int x, y;
    std::cin >> y >> x;
    if (graph[(y - 1) * n + x - 1].empty()) {
        std::cout << 1;
        return 0;
    }
    std::vector<bool> visited(n * n, false);
    DFS((y - 1) * n + x - 1, graph, visited);
    std::set<int> component;
    for (int i = 0; i < n * n; ++i) {
        if (visited[i]) {
            component.insert(i);
        }
    }
    std::cout << component.size() << std::endl;
    return 0;
}
