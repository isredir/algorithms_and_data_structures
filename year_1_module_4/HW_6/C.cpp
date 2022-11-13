#include <bits/stdc++.h>

using namespace std;

static const int INF = 1000000000;

struct Edge {
    int a, b, cost;
    bool operator<(Edge const& other) const {
        return cost < other.cost;
    }
};

struct Graph {
    explicit Graph(int nn) {
        d = vector<int>(nn, INF);
        g = vector<int>(nn);
        parent = vector<int>(nn);
        rank = vector<int>(nn);
        n = nn;
    }

    int n;
    vector<int> d;
    vector<int> g;
    vector<Edge> edges, base_tree;
    vector<int> parent, rank;

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }

    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b]) {
                swap(a, b);
            }
            parent[b] = a;
            if (rank[a] == rank[b]) {
                rank[a]++;
            }
        }
    }

    void Kruscal() {
        int cost = 0;
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++)
            make_set(i);

        sort(edges.begin(), edges.end());

        for (Edge e : edges) {
            if (find_set(e.a) != find_set(e.b)) {
                cost += e.cost;
                base_tree.push_back(e);
                union_sets(e.a, e.b);
            }
        }
    }

};

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n * m);
    vector<pair<int, int>> p(n * m);
    map<pair<int, int>, int> num;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            num[{i, j}] = i * m + j;
            p[i * m + j] = {i, j};
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int a;
            cin >> a;
            if (a == 0) {
                if (i < n - 1) {
                    graph.edges.push_back({num[{i, j}], num[{i + 1, j}], 1});
                    graph.edges.push_back({num[{i + 1, j}], num[{i, j}], 1});
                }
                if (j < m - 1) {
                    graph.edges.push_back({num[{i, j}], num[{i, j + 1}], 2});
                    graph.edges.push_back({num[{i, j + 1}], num[{i, j}], 2});
                }
            } else if (a == 1) {
                if (i < n - 1) {
                    graph.edges.push_back({num[{i, j}], num[{i + 1, j}], 0});
                    graph.edges.push_back({num[{i + 1, j}], num[{i, j}], 0});
                }
                if (j < m - 1) {
                    graph.edges.push_back({num[{i, j}], num[{i, j + 1}], 2});
                    graph.edges.push_back({num[{i, j + 1}], num[{i, j}], 2});
                }
            } else if (a == 2) {
                if (i < n - 1) {
                    graph.edges.push_back({num[{i, j}], num[{i + 1, j}], 1});
                    graph.edges.push_back({num[{i + 1, j}], num[{i, j}], 1});
                }
                if (j < m - 1) {
                    graph.edges.push_back({num[{i, j}], num[{i, j + 1}], 0});
                    graph.edges.push_back({num[{i, j + 1}], num[{i, j}], 0});
                }
            } else if (a == 3) {
                if (i < n - 1) {
                    graph.edges.push_back({num[{i, j}], num[{i + 1, j}], 0});
                    graph.edges.push_back({num[{i + 1, j}], num[{i, j}], 0});
                }
                if (j < m - 1) {
                    graph.edges.push_back({num[{i, j}], num[{i, j + 1}], 0});
                    graph.edges.push_back({num[{i, j + 1}], num[{i, j}], 0});
                }
            }
        }
    }/*
    for (Edge e : graph.edges) {
        cout << e.a << " " << e.b << " " << e.cost << endl;
    }*/
    graph.Kruscal();
    double weight = 0;
    vector<Edge> res;
    for (Edge e : graph.base_tree) {
        weight += e.cost;
        if (e.cost != 0) {
            res.push_back(e);
        }
    }
    cout << res.size() << " " << weight << endl;
    for (Edge e : res) {
        if (e.cost == 1) {
            if (p[e.a].first < p[e.b].first) {
                cout << p[e.a].first + 1 << " " << p[e.a].second + 1 << " " << e.cost << endl;
            } else {
                cout << p[e.b].first + 1 << " " << p[e.b].second + 1 << " " << e.cost << endl;
            }
        }
        if (e.cost == 2) {
            if (p[e.a].second < p[e.b].second) {
                cout << p[e.a].first + 1 << " " << p[e.a].second + 1 << " " << e.cost << endl;
            } else {
                cout << p[e.b].first + 1 << " " << p[e.b].second + 1 << " " << e.cost << endl;
            }
        }
    }
    return 0;
}