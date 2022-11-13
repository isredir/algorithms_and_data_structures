#include <bits/stdc++.h>

using namespace std;

struct Node {
    int y, val = 0, size = 1, minn = 100000000;
    bool rev = false;
    int add = 0;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int _val) { val = _val, minn = _val, y = rand(); }
};


Node *root = nullptr;

int get_size(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->size;
}

int get_val(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->val;
}

int get_min(Node *node) {
    if (node == nullptr) {
        return 1000000000;
    }
    return node->minn;
}


void upd(Node *node) {
    if (node == nullptr) {
        return;
    }
    node->size = 1 + get_size(node->left) + get_size(node->right);
    node->minn = min(get_val(node), min(get_min(node->left), get_min(node->right)));
}

void push(Node *node) {
    if (!node) {
        return;
    }
    node->val += node->add;
    if (node->left) {
        node->left->add += node->add;
    }
    if (node->right) {
        node->right->add += node->add;
    }
    node->minn = min(get_val(node), min(get_min(node->left), get_min(node->right)));
    node->add = 0;
}

Node *merge(Node *l, Node *r) {
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }
    if (l->y > r->y) {
        push(l);
        l->right = merge(l->right, r);
        upd(l);
        return l;
    } else {
        push(r);
        r->left = merge(l, r->left);
        upd(r);
        return r;
    }
}

pair<Node *, Node *> split(Node *node, int x) {
    if (node == nullptr) {
        return {nullptr, nullptr};
    }
    push(node);
    if (get_size(node->left) + 1 <= x) {
        auto p = split(node->right, x - get_size(node->left) - 1);
        node->right = p.first;
        upd(node);
        return {node, p.second};
    } else {
        auto p = split(node->left, x);
        node->left = p.second;
        upd(node);
        return {p.first, node};
    }
}

pair<Node *, Node *> split2(Node *node, int x) {
    if (node == nullptr) {
        return {nullptr, nullptr};
    }
    push(node);
    push(node->right);
    push(node->left);
    if (node->val <= x) {
        auto p = split2(node->right, x);
        node->right = p.first;
        upd(node);
        return {node, p.second};
    } else {
        auto p = split2(node->left, x);
        node->left = p.second;
        upd(node);
        return {p.first, node};
    }
}

int min_cost(int l, int r) {
    auto p1 = split(root, r);
    auto p2 = split(p1.first, l);
    int res = get_min(p2.second);
    root = merge(p2.first, merge(p2.second, p1.second));
    return res;
}

void add_cost(int l, int r, int x) {
    auto p1 = split(root, r);
    auto p2 = split(p1.first, l);
    if (p2.second) p2.second->add += x;
    root = merge(p2.first, merge(p2.second, p1.second));
}

void solve() {
    root = nullptr;
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        res += a[i];
        if (a[i] > m) {
            cout << 0 << endl;
            return;
        }
    }
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
        if (b[i] > n) {
            cout << 0 << endl;
            return;
        }
        res -= b[i];
    }
    if (res != 0) {
        cout << 0 << endl;
        return;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) {
        root = merge(root, new Node(a[i]));
    }
    for (int i = 0; i < m; ++i) {
        if (b[i] == 0) {
            continue;
        }
        add_cost(n - b[i], n, -1);
        int minn = min_cost(n - b[i], n);
        if (minn < 0) {
            cout << 0 << endl;
            return;
        }
        auto p1 = split(root, n - b[i]);
        auto p2 = split2(p1.second, minn);
        auto p3 = split2(p1.first, minn - 1);
        root = merge(merge(p3.first, p2.first), merge(p3.second, p2.second));
    }
    cout << 1 << endl;
}

int main() {
    int c;
    cin >> c;
    for (int j = 0; j < c; ++j) {
        solve();
    }
    return 0;
}