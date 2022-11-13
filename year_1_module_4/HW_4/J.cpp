#include <bits/stdc++.h>

using namespace std;

static const uint64_t MAX_INT = 30000000;

struct Graph {
    explicit Graph(int n) {
        g = vector<vector<int>>(n, vector<int>(n, 0));
        d = vector<int>(n, MAX_INT);
        p = vector<int>(n);
    }

    vector<vector<int>> g;
    vector<int> d;
    vector<int> p;

    void Dijkstra(int s) {
        d = vector<int>(g.size(), MAX_INT);
        d[s] = 0;
        p[s] = -1;
        priority_queue<pair<int, int>> q;
        q.push(make_pair(0, s));
        while (!q.empty()) {
            int now = q.top().second;
            int cur_d = -q.top().first;
            q.pop();
            if (cur_d > d[now]) continue;
            for (int to = 1; to < g[now].size(); ++to) {
                if (to == now) {
                    continue;
                }
                int len = g[now][to];
                if (d[now] + len < d[to]) {
                    d[to] = d[now] + len;
                    p[to] = now;
                    q.push(make_pair(-d[to], to));
                }
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    vector<string> words(n + 1);
    vector<pair<string, int>> words_sorted(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        string word;
        cin >> word;
        words[i] = word;
        words_sorted[i] = make_pair(word, i);
    }
    int k;
    cin >> k;
    vector<int> seq(k + 1);
    seq[0] = 1;
    for (int i = 1; i < k + 1; ++i) {
        cin >> seq[i];
    }
    sort(words_sorted.begin(), words_sorted.end());
    vector<vector<int>> common(n + 1, vector<int>(n + 1));
    vector<int> c(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        int x = words_sorted[i].second;
        int y = words_sorted[i % n + 1].second;
        c[x] = 0;
        while (c[x] < words[x].size() && words[x][c[x]] == words[y][c[x]]) {
            ++c[x];
        }
    }
    for (int i = 2; i < n + 1; ++i) {
        int x = words_sorted[i].second;
        int y = 1000000000;
        int j = i;
        while (true) {
            --j;
            if (j == 0) {
                break;
            }
            int t = words_sorted[j].second;
            if (y > c[t]) {
                y = c[t];
            }
            if (y == 0) {
                break;
            }
            common[t][x] = y;
            common[x][t] = y;
        }
    }
    Graph graph(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        int t = 0, j = i;
        do {
            --j;
            if (j == 0) {
                j = n;
            }
            if (t < common[i][j]) {
                t = common[i][j];
            }
            if (t == words[i].size()) {
                graph.g[j][i] = 1000000000;
            } else {
                graph.g[j][i] = t + 2;
            }
        } while (i != j);
    }
    for (int i = 1; i < n + 1; ++i) {
        graph.g[i][i % n + 1] = 1;
        graph.g[i][(i - 2 + n) % n + 1] = 1;
    }
    for (int i = 0; i < k; ++i) {
        graph.Dijkstra(seq[i]);
        cout << graph.d[seq[i + 1]] << endl;
        vector<int> path;
        for (int j = seq[i + 1]; j != -1; j = graph.p[j]) {
            path.push_back(j);
        }
        reverse(path.begin(), path.end());
        for (int j = 0; j < path.size() - 1; ++j) {
            if (path[j + 1] == path[j] - 1 || (path[j] == 1 && path[j + 1] == n)) {
                cout << "up"  << endl;
            } else if (path[j + 1] == path[j] + 1 || (path[j] == n && path[j + 1] == 1)) {
                cout << "down"  << endl;
            } else {
                cout << "Alt"  << endl;
                for (int t = 0; t < graph.g[path[j]][path[j + 1]] - 1; ++t) {
                    cout << words[path[j + 1]][t] << endl;
                }
            }
        }
    }
    return 0;
}