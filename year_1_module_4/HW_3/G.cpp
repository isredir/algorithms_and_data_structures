#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int a;
    int b;

    bool operator<(const Edge &other) const {
        return (a < other.a) || (a == other.a && b < other.b);
    }
};


struct Graph {
    explicit Graph(int n) {
        g = vector<unordered_set<int>>(n);
        v = vector<bool>(n, false);
        d = vector<int>(n);
        p = vector<int>(n);
    }

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
            for (int to: g[now]) {
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
    int n, m;
    std::cin >> n >> m;
    Graph graph(n * m);
    vector<vector<int>> table = vector<vector<int>>(n + 2, vector<int>(m + 2));
    vector<int> holes;
    for (int i = 0; i < n + 2; ++i) {
        for (int j = 0; j < m + 2; ++j) {
            if (i == 0 || j == 0 || i == n + 1 || j == m + 1) {
                table[i][j] = 1;
            } else {
                cin >> table[i][j];
                if (table[i][j] == 2) {
                    holes.push_back((i - 1) * m + (j - 1));
                }
            }
        }
    }
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            if (table[i][j] != 0) {
                continue;
            }
            int x = 0;
            while (table[i - x][j] == 0) {
                ++x;
            }
            if (table[i - x][j] == 1 && (i - 1) * m + (j - 1) != ((i - 1) - x + 1) * m + (j - 1)) {
                graph.g[(i - 1) * m + (j - 1)].insert(((i - 1) - x + 1) * m + (j - 1));
            }
            if (table[i - x][j] == 2 && (i - 1) * m + (j - 1) != ((i - 1) - x) * m + (j - 1)) {
                graph.g[(i - 1) * m + (j - 1)].insert(((i - 1) - x) * m + (j - 1));
            }

            x = 0;
            while (table[i + x][j] == 0) {
                ++x;
            }
            if (table[i + x][j] == 1 && (i - 1) * m + (j - 1) != ((i - 1) + x - 1) * m + (j - 1)) {
                graph.g[(i - 1) * m + (j - 1)].insert(((i - 1) + x - 1) * m + (j - 1));
            }
            if (table[i + x][j] == 2 && (i - 1) * m + (j - 1) != ((i - 1) + x) * m + (j - 1)) {
                graph.g[(i - 1) * m + (j - 1)].insert(((i - 1) + x) * m + (j - 1));
            }

            x = 0;
            while (table[i][j - x] == 0) {
                ++x;
            }
            if (table[i][j - x] == 1 && (i - 1) * m + (j - 1) != (i - 1) * m + (j - 1) - x + 1) {
                graph.g[(i - 1) * m + (j - 1)].insert((i - 1) * m + (j - 1) - x + 1);
            }
            if (table[i][j - x] == 2 && (i - 1) * m + (j - 1) != (i - 1) * m + (j - 1) - x) {
                graph.g[(i - 1) * m + (j - 1)].insert((i - 1) * m + (j - 1) - x);
            }

            x = 0;
            while (table[i][j + x] == 0) {
                ++x;
            }
            if (table[i][j + x] == 1 && (i - 1) * m + (j - 1) != (i - 1) * m + (j - 1) + x - 1) {
                graph.g[(i - 1) * m + (j - 1)].insert((i - 1) * m + (j - 1) + x - 1);
            }
            if (table[i][j + x] == 2 && (i - 1) * m + (j - 1) != (i - 1) * m + (j - 1) + x) {
                graph.g[(i - 1) * m + (j - 1)].insert((i - 1) * m + (j - 1) + x);
            }
        }
    }
    graph.BFS(0);
    int min_path = 10000000;
    for (int i : holes) {
        if (graph.v[i]) {
            min_path = min(min_path, graph.d[i]);
        }
    }
    cout << min_path;
    return 0;
}
