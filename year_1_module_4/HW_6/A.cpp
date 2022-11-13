#include <bits/stdc++.h>

using namespace std;

static const int INF = 1000000000;

struct Edge {
    int a, b, cost;
    bool operator<(Edge const& other) {
        return cost < other.cost;
    }
};

struct Graph {
    explicit Graph(int nn) {
        d = vector<int>(nn, INF);
        parent = vector<int>(nn);
        rank = vector<int>(nn);
        n = nn;
    }

    int n;
    vector<int> d;
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
    cin >> n >> m;
    Graph graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.edges.push_back({a, b, c});
        graph.edges.push_back({b, a, c});
    }
    graph.Kruscal();
    int weight = 0;
    for (Edge e : graph.base_tree) {
        weight += e.cost;
    }
    cout << weight;
    return 0;
}