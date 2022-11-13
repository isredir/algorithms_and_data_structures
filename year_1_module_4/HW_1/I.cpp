#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <iomanip>

struct point {
    float x;
    float y;
    int num;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<point> points(n);
    for (int i = 0; i < n; ++i) {
        float x, y;
        std::cin >> y >> x;
        points[i] = {x, y, i};
    }
    std::vector<float> distances;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            float d = std::sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x) +
                                (points[i].y - points[j].y) * (points[i].y - points[j].y)) / 2;
            distances.push_back(d);
        }
    }
    float max_d = 0;
    std::vector<int> coloring_res(n);
    std::sort(distances.begin(), distances.end());
    for (float distance: distances) {
        std::vector<std::unordered_set<int>> graph(n);
        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                float d = std::sqrt((points[j].x - points[k].x) * (points[j].x - points[k].x) +
                                    (points[j].y - points[k].y) * (points[j].y - points[k].y)) / 2;
                if (d < distance) {
                    graph[points[j].num].insert(points[k].num);
                    graph[points[k].num].insert(points[j].num);
                }
            }
        }
        std::vector<bool> visited(n);
        std::vector<int> coloring(n);
        for (int i = 0; i < n; ++i) {
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
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            for (int v: graph[i]) {
                if (coloring[v] == coloring[i]) {
                    flag = false;
                }
            }
        }
        if (flag) {
            if (distance > max_d) {
                max_d = distance;
                coloring_res = coloring;
            }
        }
    }
    std::cout << std::fixed << std::setprecision(9) << max_d << std::endl;
    for (int i: coloring_res) {
        std::cout << i << " ";
    }
    return 0;
}
