#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const int INF = (int)(1e9);

struct Edge {
    int v;
    int flow;
    int capacity;

    Edge(int v, int capacity) : v(v), flow(0), capacity(capacity) {}

    int get_capacity() {
        return capacity - flow;
    }
};

struct Graph {
    int n;
    int s, t;
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<int> used;
    vector<int> path;
    int timer = 1;
    Graph(int nn) {
        n = nn;
        g = vector<vector<int>>(n);
        used = vector<int>(n);
    }

    void add_edge(int v, int u, int capacity) {
        g[v].emplace_back(edges.size());
        edges.emplace_back(u, capacity);
        g[u].emplace_back(edges.size());
        edges.emplace_back(v, 0);
    }

    int dfs(int v, int min_capacity) {
        if (v == t) {
            return min_capacity;
        }
        used[v] = timer;
        for (int index : g[v]) {
            if (edges[index].get_capacity() == 0) {
                continue;
            }
            if (used[edges[index].v] == timer) {
                continue;
            }
            int x = dfs(edges[index].v, min(min_capacity, edges[index].get_capacity()));
            if (x) {
                edges[index].flow += x;
                edges[index ^ 1].flow -= x;
                return x;
            }
        }
        return 0;
    }

    void dfs2(int u) {
        path.push_back(u);
        if (u == t) {
            return;
        }
        for (int id : g[u]) {
            int v = edges[id].v;
            if (used[id] == 0 && edges[id].flow > 0) {
                used[id] = 1;
                dfs2(v);
                break;
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> cards(676);
    vector<string> list(n);
    vector<int> pairs(676, 0);
    vector<int> letters(26, 0);
    for (int i = 0; i < n; ++i) {
        string card;
        cin >> card;
        list[i] = card;
        ++pairs[(card[0] - 'a') * 26 + (card[1] - 'a')];
        cards[(card[0] - 'a') * 26 + (card[1] - 'a')].push_back(i);
    }
    string text;
    cin >> text;
    for (char i : text) {
        ++letters[i - 'a'];
    }
    Graph graph(26 * 26 + 26 + 2);
    int m = 0;
    for (int i = 0; i < 676; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (i / 26 == j || i % 26 == j) {
                graph.add_edge(i, 676 + j, pairs[i]);
            }
        }
    }
//    for (auto e : graph.edges) {
//        cout << e.v - 676 << " " << e.capacity << endl;
//    }
    graph.s = graph.n - 2;
    graph.t = graph.n - 1;
    for (int i = 0; i < 676; ++i) {
        ++m;
        graph.add_edge(graph.s, i, pairs[i]);
    }
    for (int i = 0; i < 26; ++i) {
        ++m;
        graph.add_edge(676 + i, graph.t, letters[i]);
    }
    while (graph.dfs(graph.s, INF)) {
        ++graph.timer;
    }
    int result = 0;
    for (int index : graph.g[graph.s]) {
        result += graph.edges[index].flow;
    }
    //cout << result << endl;
    if (result < text.size()) {
        cout << "IMPOSSIBLE";
        return 0;
    }
    for (int i = 0; i < text.size(); ++i) {
        for (int ind: graph.g[676 + text[i] - 'a']) {
            if (graph.edges[ind].v < 676 && graph.edges[ind].flow < 0) {
                //cout << graph.edges[ind].v << " " << graph.edges[ind].capacity << " " << graph.edges[ind].flow << ", ";
                if (graph.edges[ind].v % 26 == text[i] - 'a') {
                    cout << '-';
                }
                cout << cards[graph.edges[ind].v].back() + 1 << " ";
                cards[graph.edges[ind].v].pop_back();
                ++graph.edges[ind].flow;
                break;
            }
        } //cout << endl;
    }
    return 0;
}