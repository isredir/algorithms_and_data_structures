#include <bits/stdc++.h>

using namespace std;

struct Graph {
    explicit Graph(int n) {
        g = vector<set<int>>(n);
        v = vector<bool>(n, false);
    }

    vector<set<int>> g;
    vector<bool> v;
    vector<int> order;

    void DFS(int now) {
        order.push_back(now);
        v[now] = true;
        for (int neig: g[now]) {
            if (!v[neig]) {
                DFS(neig);
                order.push_back(now);
            }
        }
    }

};

int main() {
    int n;
    cin >> n;
    Graph tree(n + 1);
    int root;
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        if (a != 0) {
            tree.g[i].insert(a);
            tree.g[a].insert(i);
        } else {
            root = i;
        }
    }
    tree.DFS(root);
    vector<int> first(n + 1, 0);
    vector<int> last(n + 1, 0);
    for (int i = 0; i < tree.order.size(); ++i) {
        if (first[tree.order[i]] == 0) {
            first[tree.order[i]] = i;
        }
    }
    first[root] = 0;
    for (int i = tree.order.size() - 1; i >= 0; --i) {
        if (last[tree.order[i]] == 0) {
            last[tree.order[i]] = i;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        if (first[a] <= first[b] && last[b] <= last[a]) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
    return 0;
}