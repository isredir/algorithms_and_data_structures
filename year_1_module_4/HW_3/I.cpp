#include <bits/stdc++.h>

using namespace std;

set<pair<int, int>> neighbours(vector<vector<int>> &table, int num) {
    set<pair<int, int>> res;
    int num2 = num - num % 8;
    for (int x = 0; x < 8; ++x) {
        if (num2 + x != num) {
            if (abs(num % 8 - x) != 4) {
                res.insert({num2 + x, 1});
            } else {
                res.insert({num2 + x, 0});
            }
        }
    }
    int num1 = num / 8;
    int m = table.at(0).size() - 2;
    int i = num1 / m + 1;
    int j = num1 % m + 1;
    num2 = (i - 2) * m + (j - 2);
    if (num % 8 == 0 && table[i - 1][j - 1] == 0) {
        res.insert({num2 * 8 + 4, 0});
    }
    num2 = (i - 2) * m + (j - 1);
    if (num % 8 == 1 && table[i - 1][j] == 0) {
        res.insert({num2 * 8 + 5, 0});
    }
    num2 = (i - 2) * m + (j);
    if (num % 8 == 2 && table[i - 1][j + 1] == 0) {
        res.insert({num2 * 8 + 6, 0});
    }
    num2 = (i - 1) * m + (j);
    if (num % 8 == 3 && table[i][j + 1] == 0) {
        res.insert({num2 * 8 + 7, 0});
    }
    num2 = (i) * m + (j);
    if (num % 8 == 4 && table[i + 1][j + 1] == 0) {
        res.insert({num2 * 8 + 0, 0});
    }
    num2 = (i) * m + (j - 1);
    if (num % 8 == 5 && table[i + 1][j] == 0) {
        res.insert({num2 * 8 + 1, 0});
    }
    num2 = (i) * m + (j - 2);
    if (num % 8 == 6 && table[i + 1][j - 1] == 0) {
        res.insert({num2 * 8 + 2, 0});
    }
    num2 = (i - 1) * m + (j - 2);
    if (num % 8 == 7 && table[i][j - 1] == 0) {
        res.insert({num2 * 8 + 3, 0});
    }
    return res;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int>> table = vector<vector<int>>(n + 2, vector<int>(m + 2));
    for (int i = 0; i < n + 2; ++i) {
        for (int j = 0; j < m + 2; ++j) {
            if (i == 0 || j == 0 || i == n + 1 || j == m + 1) {
                table[i][j] = 1;
            } else {
                char c;
                cin >> c;
                if (c == 'X') {
                    table[i][j] = 1;
                } else {
                    table[i][j] = 0;
                }
            }
        }
    }
    int sx, sy, fx, fy;
    cin >> sx >> sy >> fx >> fy;
    --sx;
    --fx;
    sy = n - sy;
    fy = n - fy;
    int finish = fy * m + fx;
    set<pair<int, int>> start_points;
    int start = sy * m + sx;
    for (int x = 0; x < 8; ++x) {
        start_points.insert({start * 8 + x, 1});
    }
    vector<int> dist(n * m * 8 + 1, n * m * 8 + 1);
    vector<int> v(n * m * 8 + 1);
    dist[n * m * 8] = 0;
    v[n * m * 8] = true;
    deque<int> pending;
    pending.push_back(n * m * 8);
    while (!pending.empty()) {
        int now = pending.front();
        pending.pop_front();
        if (now == n * m * 8) {
            for (auto&[to, w]: start_points) {
                v[to] = true;
                if (dist[to] > dist[now] + w) {
                    dist[to] = dist[now] + w;
                    if (w == 0) {
                        pending.push_front(to);
                    } else {
                        pending.push_back(to);
                    }
                }
                if (to / 8 == finish) {
                    cout << dist[to];
                    return 0;
                }
            }
        } else {
            for (auto&[to, w]: neighbours(table, now)) {
                v[to] = true;
                if (dist[to] > dist[now] + w) {
                    dist[to] = dist[now] + w;
                    if (w == 0) {
                        pending.push_front(to);
                    } else {
                        pending.push_back(to);
                    }
                }
                if (to / 8 == finish) {
                    cout << dist[to];
                    return 0;
                }
            }
        }
    }
    int min_path = -1;
    for (int x = 0; x < 8; ++x) {
        if (v[finish * 8 + x]) {
            if (min_path == -1) {
                min_path = dist[finish * 8 + x];
            }
            min_path = min(min_path, dist[finish * 8 + x]);
        }
    }
    cout << min_path;
    return 0;
}
