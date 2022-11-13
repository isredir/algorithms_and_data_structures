#include <bits/stdc++.h>

using namespace std;

struct Node {
    int y, val, size;
    Node* left = nullptr;
    Node* right = nullptr;
};

Node* root = nullptr;

Node* new_node(int val) {
    Node* node = new Node;
    node->y = rand();
    node->size = 1;
    node->val = val;
    node->left = node->right = nullptr;
    return node;
}

int get_size(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->size;
}

void upd_size(Node* node) {
    if (node == nullptr) {
        return;
    }
    node->size = 1 + get_size(node->left) + get_size(node->right);
}

Node* merge(Node* l, Node* r) {
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }
    if (l->y > r->y) {
        l->right = merge(l->right, r);
        upd_size(l);
        return l;
    }
    r->left = merge(l, r->left);
    upd_size(r);
    return r;
}

pair<Node*, Node*> split(Node* node, int x) {
    if (node == nullptr) {
        return {nullptr, nullptr};
    }
    if (get_size(node->left) + 1 <= x) {
        auto p = split(node->right, x - get_size(node->left) - 1);
        node->right = p.first;
        upd_size(node);
        return {node, p.second};
    }
    auto p = split(node->left, x);
    node->left = p.second;
    upd_size(node);
    return {p.first, node};
}

void print_tree(Node *node)
{
    if (node == nullptr) { return; }
    print_tree(node->left);
    cout << node->val << " ";
    print_tree(node->right);
}

void insert(int x) {
    auto p = split(root, x);
    Node* node = new Node;
    root = merge(p.first, merge(node, p.second));
}

Node* ctrlx(int l, int r) {
    auto p1 = split(root, r);
    auto p2 = split(p1.first, l);
    root = merge(p2.first, p1.second);
    return p2.second;
}

void ctrlv(Node* node, int x) {
    auto p = split(root, x);
    root = merge(p.first, merge(node, p.second));
}



int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        root = merge(root, new_node(i));
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        Node* temp = ctrlx(a - 1, b);
        ctrlv(temp, 0);
    }
    print_tree(root);
    return 0;
}