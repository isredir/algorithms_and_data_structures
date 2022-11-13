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
        for (int i = 1; i < n; i++)
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
    cin >> n;
    Graph graph(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        int y, x;
        cin >> y >> x;
        graph.g[i] = y * 1000 + x;
    }
    cin >> m;
    set<pair<int, int>> used;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        used.insert({a, b});
        used.insert({b, a});
    }
    for (int i = 1; i < n + 1; ++i) {
        for (int j = i + 1; j < n + 1; ++j) {
            int x1 = graph.g[i] % 1000;
            int y1 = graph.g[i] / 1000;
            int x2 = graph.g[j] % 1000;
            int y2 = graph.g[j] / 1000;
            if (used.find({i, j}) == used.end()) {
                graph.edges.push_back({i, j, (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1)});
                graph.edges.push_back({j, i, (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1)});
            } else {
                graph.edges.push_back({i, j, 0});
                graph.edges.push_back({j, i, 0});
            }
        }
    }
    graph.Kruscal();
    double weight = 0;
    for (Edge e : graph.base_tree) {
        weight += sqrt(double(e.cost));
    }
    cout << fixed << setprecision(5) << weight;
    return 0;
}