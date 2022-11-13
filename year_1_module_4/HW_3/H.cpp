#include <bits/stdc++.h>

using namespace std;

set<vector<int>> neighbours(const vector<int>& now, int a, int b, int c) {
    set<vector<int>> neig;
    neig.insert({a, now[1], now[2]});
    neig.insert({now[0], b, now[2]});
    neig.insert({now[0], now[1], c});
    neig.insert({0, now[1], now[2]});
    neig.insert({now[0], 0, now[2]});
    neig.insert({now[0], now[1], 0});
    if (now[0] + now[1] <= a) {
        neig.insert({now[0] + now[1], 0, now[2]});
    } else {
        neig.insert({a, now[1] - (a - now[0]), now[2]});
    }
    if (now[0] + now[2] <= a) {
        neig.insert({now[0] + now[2], now[1], 0});
    } else {
        neig.insert({a, now[1], now[2] - (a - now[0])});
    }
    if (now[1] + now[0] <= b) {
        neig.insert({0, now[1] + now[0], now[2]});
    } else {
        neig.insert({now[0] - (b - now[1]), b, now[2]});
    }
    if (now[1] + now[2] <= b) {
        neig.insert({now[0], now[1] + now[2], 0});
    } else {
        neig.insert({now[0], b, now[2] - (b - now[1])});
    }
    if (now[2] + now[0] <= c) {
        neig.insert({0, now[1], now[2] + now[0]});
    } else {
        neig.insert({now[0] - (c - now[2]), now[1], c});
    }
    if (now[2] + now[1] <= c) {
        neig.insert({now[0], 0, now[2] + now[1]});
    } else {
        neig.insert({now[0], now[1] - (c - now[2]), c});
    }
    return neig;
}

int main() {
    int a, b, c, finish;
    cin >> a >> b >> c >> finish;
    map<vector<int>, bool> v;
    map<vector<int>, int> d;
    map<vector<int>, vector<int>> p;
    queue<vector<int>> q;
    q.push({0, 0, 0});
    v[{0, 0, 0}] = true;
    p[{0, 0, 0}] = {-1};
    while (!q.empty()) {
        vector<int> now = q.front();
        q.pop();
        for (const vector<int>& to : neighbours(now, a, b, c)){
            if (!v[to]) {
                v[to] = true;
                q.push(to);
                d[to] = d[now] + 1;
                p[to] = now;
            }
        }
    }
    int min_path = -1;
    for (auto [i, j] : d) {
        if (i[0] == finish || i[1] == finish || i[2] == finish) {
            if (min_path == -1) {
                min_path = d[i];
            }
            min_path = min(min_path, d[i]);
        }
    }
    cout << min_path;
    return 0;
}
