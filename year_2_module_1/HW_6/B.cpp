#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const int MAX = 1'000'000'000;

struct Node {
    Node *r;
    Node *l;
    int sum;

    explicit Node(int x) : r(nullptr), l(nullptr), sum(x) {}

    Node(Node *ll, Node *rr) : l(ll), r(rr), sum(0) {
        if (l != nullptr) {
            sum += l->sum;
        }
        if (r != nullptr) {
            sum += r->sum;
        }
    }
};

Node *buildTree(int l, int r) {
    if (l == r) {
        return new Node(0);
    }
    int d = (l + r) / 2;
    return new Node(buildTree(l, d), buildTree(d + 1, r));
}

Node *update(Node *root, int l, int r, int pos, int x) {
    if (pos < l || r < pos) {
        return root;
    }
    if (l == r) {
        return new Node(x);
    }
    int d = (l + r) / 2;
    return new Node(update(root->l, l, d, pos, x), update(root->r, d + 1, r, pos, x));
}

int k;

int get_sum(Node *node, int l, int r) {
    if (k == 0) {
        return l - 1;
    }
    if (node == nullptr) {
        return MAX / 2;
    }
    if (node->sum < k || l == r) {
        k -= node->sum;
        return r;
    }
    int d = (l + r) / 2;
    int ans = get_sum(node->l, l, d);
    if (k > 0) {
        ans = get_sum(node->r, d + 1, r);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    Node *root = buildTree(0, n - 1);
    vector<int> next(n + 1), last(m + 1, n);
    for (int i = n - 1; i >= 0; --i) {
        int c = a[i];
        next[i] = last[c];
        last[c] = i;
    }
    vector<Node *> roots(n);
    for (int i = n - 1; i >= 0; --i) {
        root = update(root, 0, n - 1, next[i], 0);
        root = update(root, 0, n - 1, i, 1);
        roots[i] = root;
    }
    int q, p = 0;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        int l = (x + p) % n;
        k = (y + p) % m + 1;
        p = get_sum(roots[l], 0, n - 1) + 1;
        if (k > 0 || p >= MAX / 2) {
            p = 0;
        }
        cout << p << endl;
    }
    return 0;
}