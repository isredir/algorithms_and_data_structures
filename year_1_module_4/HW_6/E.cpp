#include <bits/stdc++.h>

using namespace std;

static const int INF = 1000000000;

struct Edge {
    int a, b, cost, num, type = 0;
    bool operator<(Edge const& other) const {
        return cost < other.cost;
    }
};

struct Graph {
    explicit Graph(int nn) {
        parent = vector<int>(nn);
        rank = vector<int>(nn);
        n = nn;
    }

    int n;
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
        base_tree.clear();
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
        graph.edges.push_back({a, b, c, i});
        graph.edges.push_back({b, a, c, i});
    }
    int p5, q5, p6, q6;
    cin >> p5 >> q5 >> p6 >> q6;
    int min_type = 5, max_type = 6;
    if (p5 > p6) {
        swap(p5, p6);
        swap(q5, q6);
        swap(min_type, max_type);
    }
    graph.Kruscal();
    if (graph.base_tree.size() != n - 1) {
        cout << "Impossible";
        return 0;
    }
    int s = 0;
    for (Edge &e : graph.base_tree) {
        s += e.cost;
    }
    if (s > q5 + q6) {
        cout << "Impossible";
        return 0;
    }
    vector<int> arr(q5 + 1, 0);
    arr[0] = 1;
    int maxWeight = 0;
    for (Edge &e : graph.base_tree) {
        int i = e.cost;
        for (int j = q5; j >= 0; --j) {
            if (j - i < 0) {
                break;
            }
            if (arr[j - i] != 0) {
                if (arr[j] == 0) {
                    arr[j] = i;
                }
                maxWeight = max(maxWeight, j);
            }
        }
    }
    for (int i = maxWeight; i >= 0; i -= arr[i]) {
        for (Edge &e : graph.base_tree) {
            if (e.cost == arr[i] && e.type == 0) {
                e.type = min_type;
                break;
            }
        }
    }
    if (s - maxWeight > q6) {
        cout << "Impossible";
        return 0;
    }
    cout << maxWeight * p5 + (s - maxWeight) * p6 << endl;
    int summ = 0;
    for (Edge &e : graph.base_tree) {
        if (e.type == min_type) {
            summ += e.cost * p5;
            cout << e.num + 1 << " " << e.type << endl;
        } else {
            summ += e.cost * p6;
            cout << e.num + 1 << " " << max_type << endl;
        }
    }
    if (summ != maxWeight * p5 + (s - maxWeight) * p6) {
        throw;
    }
    return 0;
}