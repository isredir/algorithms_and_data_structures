#include <bits/stdc++.h>

using namespace std;

struct Node {
    int y, val, size = 1;
    int64_t summ;
    bool rev = false;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int _val) { val = _val, summ = _val, y = rand(); }
};

struct treap {

    Node *root = nullptr;

    int get_size(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->size;
    }

    int64_t get_summ(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->summ;
    }


    void upd(Node *node) {
        if (node == nullptr) {
            return;
        }
        node->size = 1 + get_size(node->left) + get_size(node->right);
        node->summ = node->val + get_summ(node->left) + get_summ(node->right);
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

    int64_t summ_cost(int l, int r) {
        auto p1 = split(root, r);
        auto p2 = split(p1.first, l);
        int64_t res = get_summ(p2.second);
        root = merge(p2.first, merge(p2.second, p1.second));
        return res;
    }

    void reverse(int l, int r) {
        auto p1 = split(root, r);
        auto p2 = split(p1.first, l);
        p2.second->rev ^= 1;
        root = merge(p2.first, merge(p2.second, p1.second));
    }
};

void print_tree(Node *node) {
    if (node == nullptr) { return; }
    print_tree(node->left);
    cout << node->val << " ";
    print_tree(node->right);
}

int main() {
    int count = 1;
    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        }
        cout << "Swapper " << count << ":" << endl;
        ++count;
        treap even, odd;
        for (int i = 1; i <= n; ++i) {
            int a;
            cin >> a;
            if (i % 2 == 0) {
                even.root = even.merge(even.root, new Node(a));
            } else {
                odd.root = odd.merge(odd.root, new Node(a));
            }
        }
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            --b;
            --c;
            int l_odd = (b + 1) / 2, r_odd = c / 2;
            int l_even = b / 2, r_even = (c + 1) / 2 - 1;
            if (a == 2) {
                int64_t s = even.summ_cost(l_even, r_even + 1) + odd.summ_cost(l_odd, r_odd + 1);
                cout << s << endl;
            } else {
                Node *t_even = even.ctrlx(l_even, r_even + 1);
                Node *t_odd = odd.ctrlx(l_odd, r_odd + 1);
                even.ctrlv(t_odd, l_even);
                odd.ctrlv(t_even, l_odd);
            }
        }
        cout << endl;
    }
    return 0;
}