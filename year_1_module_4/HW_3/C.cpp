#include <bits/stdc++.h>
using namespace std;

struct Graph {
    explicit Graph(int n) {
        g = vector<unordered_set<int>>(n);
        v = vector<bool>(n, false);
        d = vector<int>(n);
        p = vector<int>(n);
    }

    struct Edge {
        int a;
        int b;
        bool operator<(const Edge &other) const {
            return (a < other.a) || (a == other.a && b < other.b);
        }
    };

    vector<unordered_set<int>> g;
    vector<bool> v;
    vector<int> d, p;

    void BFS(int start) {
        queue<int> q;
        q.push(start);
        v[start] = true;
        p[start] = -1;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int to : g[now]) {
                if (!v[to]) {
                    v[to] = true;
                    q.push(to);
                    d[to] = d[now] + 1;
                    p[to] = now;
                }
            }
        }
    }

    vector<int> Path(int start, int finish) {
        BFS(start);
        if (!v[finish]) {
            return {-1};
        }
        vector<int> path;
        for (int i = finish; i != -1; i = p[i]) {
            path.push_back(i);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    int n;
    cin >> n;
    vector<vector<vector<int>>> cave = vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(n)));
    map<vector<int>, int> vertexes;
    vector<int> upper;
    int num = 0;
    int start;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                char c;
                cin >> c;
                if (c == '#') {
                    cave[i][j][k] = 0;
                } else {
                    cave[i][j][k] = 1;
                    vertexes[{i, j, k}] = num;
                    if (i == 0) {
                        upper.push_back(num);
                    }
                    ++num;
                }
                if (c == 'S') {
                    start = vertexes[{i, j, k}];
                }
            }
        }
    }
    Graph graph(num);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (cave[i][j][k] == 0) {
                    continue;
                }
                vector<vector<int>> vec = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
                for (auto v : vec) {
                    if (v[2] != 0 && i + v[2] >= 0 && i + v[2] < n && cave[i + v[2]][j][k] == 1) {
                        graph.g[vertexes[{i + v[2], j, k}]].insert(vertexes[{i, j, k}]);
                        graph.g[vertexes[{i, j, k}]].insert(vertexes[{i + v[2], j, k}]);
                    }
                    if (v[0] != 0 && j + v[0] >= 0 && j + v[0] < n && cave[i][j + v[0]][k] == 1) {
                        graph.g[vertexes[{i, j + v[0], k}]].insert(vertexes[{i, j, k}]);
                        graph.g[vertexes[{i, j, k}]].insert(vertexes[{i, j + v[0], k}]);
                    }
                    if (v[1] != 0 && k + v[1] >= 0 && k + v[1] < n && cave[i][j][k + v[1]] == 1) {
                        graph.g[vertexes[{i, j, k + v[1]}]].insert(vertexes[{i, j, k}]);
                        graph.g[vertexes[{i, j, k}]].insert(vertexes[{i, j, k + v[1]}]);
                    }
                }
            }
        }
    }
    graph.BFS(start);
    int min_path = 10000000;
    for (int i : upper) {
        if (graph.v[i]) {
            min_path = min(min_path, graph.d[i]);
        }
    }
    cout << min_path;
    return 0;
}
