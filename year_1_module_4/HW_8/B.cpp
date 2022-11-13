#include <bits/stdc++.h>

using namespace std;

struct Node {
    int y, val, size = 1, minn;
    bool rev = false;
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
    node->minn = min(node->val, min(get_min(node->left), get_min(node->right)));
}

void push(Node *node) {
    if (!node || !node->rev) {
        return;
    }
    if (node->left) {
        node->left->rev ^= 1;
    }
    if (node->right) {
        node->right->rev ^= 1;
    }
    swap(node->left, node->right);
    node->rev = false;
}

Node *merge(Node *l, Node *r) {
    push(l);
    push(r);
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }
    if (l->y > r->y) {
        l->right = merge(l->right, r);
        upd(l);
        return l;
    } else {
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

void print_tree(Node *node) {
    if (node == nullptr) { return; }
    print_tree(node->left);
    cout << node->val << "," << node->minn << " ";
    print_tree(node->right);
}

Node *ctrlx(int l, int r) {
    auto p1 = split(root, r);
    auto p2 = split(p1.first, l);
    root = merge(p2.first, p1.second);
    return p2.second;
}

void ctrlv(Node *node, int x) {
    auto p = split(root, x);
    root = merge(p.first, merge(node, p.second));
}

int min_cost(int l, int r) {
    auto p1 = split(root, r);
    auto p2 = split(p1.first, l);
    int res = get_min(p2.second);
    root = merge(p2.first, merge(p2.second, p1.second));
    return res;
}

void reverse(int l, int r) {
    auto p1 = split(root, r);
    auto p2 = split(p1.first, l);
    p2.second->rev ^= 1;
    root = merge(p2.first, merge(p2.second, p1.second));
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        root = merge(root, new Node(a));
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            reverse(b - 1, c);
        } else {
            cout << min_cost(b - 1, c) << endl;
        }
    }
    return 0;
}