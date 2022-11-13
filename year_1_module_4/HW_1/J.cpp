#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> table;
    std::unordered_map<int, std::unordered_set<int>> graph(n * m);
    int num = 0;
    for (int i = 0; i < n; ++i) {
        table.emplace_back();
        for (int j = 0; j < m; ++j) {
            int a;
            std::cin >> a;
            table.back().push_back(a);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i - 1 >= 0 && table[i - 1][j] == table[i][j]) {
                graph[num].insert(num - m);
                graph[num - m].insert(num);
            }
            if (j - 1 >= 0 && table[i][j - 1] == table[i][j]) {
                graph[num].insert(num - 1);
                graph[num - 1].insert(num);
            }
            if (i + 1 < n && table[i + 1][j] == table[i][j]) {
                graph[num].insert(num + m);
                graph[num + m].insert(num);
            }
            if (j + 1 < m && table[i][j + 1] == table[i][j]) {
                graph[num].insert(num + 1);
                graph[num + 1].insert(num);
            }
            ++num;
        }
    }
    std::vector<bool> visited(n * m);
    std::vector<std::set<int>> components;
    for (int i = 0; i < n * m; ++i) {
        if (!visited[i]) {
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
    int count = 0;
    for (const auto &component: components) {
        bool flag = true;
        for (int v: component) {
            if (v / m - 1 >= 0 && table[v / m - 1][v % m] < table[v / m][v % m]) {
                flag = false;
                break;
            }
            if (v / m + 1 < n && table[v / m + 1][v % m] < table[v / m][v % m]) {
                flag = false;
                break;
            }
            if (v % m - 1 >= 0 && table[v / m][v % m - 1] < table[v / m][v % m]) {
                flag = false;
                break;
            }
            if (v % m + 1 < m && table[v / m][v % m + 1] < table[v / m][v % m]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ++count;
        }
    }
    std::cout << count << std::endl;
    return 0;
}
