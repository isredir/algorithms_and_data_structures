#include <iostream>
#include <vector>
#include <unordered_set>


void DFS(int now, std::vector<std::unordered_set<int>> &g, std::vector<int> &v, std::vector<int> &path,
         bool &flag) {
    if (flag) {
        return;
    }
    v[now] = 1;
    for (int to: g[now]) {
        if (v[to] == 0) {
            path[to] = now;
            DFS(to, g, v, path, flag);
        } else if (v[to] == 1 && to != path[now] && !flag) {
            flag = true;
            std::cout << "YES" << std::endl;
            int cycle_st = to;
            int k = now;
            std::vector<int> cycle;
            while (k != cycle_st) {
                cycle.push_back(k);
                k = path[k];
            }
            cycle.push_back(cycle_st);
            if (cycle.empty()) {
                throw std::runtime_error("f");
            }
            std::cout << cycle.size() << std::endl;
            for (int i: cycle) {
                std::cout << i << " ";
            }
        }
    }
    v[now] = 2;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::unordered_set<int>> graph(n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int a;
            std::cin >> a;
            if (a) {
                graph[i + 1].insert(j + 1);
                graph[j + 1].insert(i + 1);
            }
        }
    }
    std::vector<int> visited(n + 1);
    bool flag = false;
    for (int i = 1; i < n + 1; ++i) {
        std::vector<int> path(n + 1);
        if (visited[i] == 0) {
            DFS(i, graph, visited, path, flag);
            if (flag) {
                break;
            }
        }
    }
    if (!flag) {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
