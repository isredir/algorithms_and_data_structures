#include <bits/stdc++.h>

using namespace std;

struct Node {
    int y, val, size = 1, maxx;
    int num;
    bool rev = false;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int _val, int _num) { val = _val, num = _num, maxx = _val, y = rand(); }
};


struct treap {

    Node *root = nullptr;

    int get_size(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->size;
    }

    int get_max(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->maxx;
    }


    void upd(Node *node) {
        if (node == nullptr) {
            return;
        }
        node->size = 1 + get_size(node->left) + get_size(node->right);
        node->maxx = max(node->val, max(get_max(node->left), get_max(node->right)));
    }

    Node *merge(Node *l, Node *r) {
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
        print_tree(node->right);
        cout << node->num << " ";
        print_tree(node->left);
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

    int max_cost(int l, int r) {
        auto p1 = split(root, r);
        auto p2 = split(p1.first, l);
        int res = get_max(p2.second);
        root = merge(p2.first, merge(p2.second, p1.second));
        return res;
    }

    Node* kth_element(Node* node, int x) {
        if (get_size(node->left) == x) {
            return node;
        } else if (get_size(node->left) < x) {
            return kth_element(node->right, x - get_size(node->left) - 1);
        } else {
            return kth_element(node->left, x);
        }
    }

    void insert(int pos, int val, int num) {
        auto p = split(root, pos);
        Node* node = new Node(val, num);
        root = merge(p.first, merge(node, p.second));
    }

    void erase(int pos) {
        auto p1 = split(root, pos + 1);
        auto p2 = split(p1.first, pos);
        root = merge(p2.first, p1.second);
    }
};



int main() {
    int n;
    cin >> n;
    int a, c;
    treap q;
    for (int i = 0; i < n; ++i) {
        cin >> a >> c;
        int l = 0, r = min(i, c);
        while (l < r) {
            int d = (l + r) / 2;
            if (q.max_cost(l, d + 1) < a) {
                l = d + 1;
            } else {
                r = d;
            }
        }
        q.insert(l, a, i + 1);
    }
    q.print_tree(q.root);
    return 0;
}