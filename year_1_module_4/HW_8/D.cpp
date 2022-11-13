#include <bits/stdc++.h>

using namespace std;

struct Node {
    int64_t y, val, size = 1;
    int64_t summ;
    bool rev = false;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int64_t _val) { val = _val, summ = _val, y = rand(); }
};

struct treap {

    Node *root = nullptr;

    int64_t get_size(Node *node) {
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
        node->summ = node->val * node->val + get_summ(node->left) + get_summ(node->right);
    }

    void print_tree(Node *node) {
        if (node == nullptr) { return; }
        print_tree(node->left);
        cout << node->val << " ";
        print_tree(node->right);
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

    pair<Node *, Node *> split(Node *node, int64_t x) {
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

    Node* kth_element(Node* node, int64_t x) {
        if (get_size(node->left) == x) {
            return node;
        } else if (get_size(node->left) < x) {
            return kth_element(node->right, x - get_size(node->left) - 1);
        } else {
            return kth_element(node->left, x);
        }
    }

    void insert(int pos, int64_t val) {
        auto p = split(root, pos);
        Node* node = new Node(val);
        root = merge(p.first, merge(node, p.second));
    }

    void erase(int pos) {
        auto p1 = split(root, pos + 1);
        auto p2 = split(p1.first, pos);
        root = merge(p2.first, p1.second);
    }

    int64_t summ_cost(int l, int r) {
        auto p1 = split(root, r);
        auto p2 = split(p1.first, l);
        int64_t res = get_summ(p2.second);
        root = merge(p2.first, merge(p2.second, p1.second));
        return res;
    }
};



int main() {
    int n, p;
    cin >> n >> p;
    int64_t ans = 0;
    int64_t size = n;
    treap factories;
    for (int i = 0; i < n; ++i) {
        int64_t a;
        cin >> a;
        factories.root = factories.merge(factories.root, new Node(a));
        ans += a * a;
    }
    cout << ans << endl;
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        --b;
        if (a == 1) {
            Node* t = factories.kth_element(factories.root, b);
            ans -= t->val * t->val;
            if (b == 0) {
                Node* t1 = factories.kth_element(factories.root, 1);
                ans -= t1->val * t1->val;
                t1->val += t->val;
                ans += t1->val * t1->val;
            } else if (b == size - 1) {
                Node* t2 = factories.kth_element(factories.root, size - 2);
                ans -= t2->val * t2->val;
                t2->val += t->val;
                ans += t2->val * t2->val;
            } else {
                Node* t1 = factories.kth_element(factories.root, b - 1);
                Node* t2 = factories.kth_element(factories.root, b + 1);
                ans -= t1->val * t1->val;
                ans -= t2->val * t2->val;
                if (t->val % 2 == 0) {
                    t1->val += t->val / 2;
                    t2->val += t->val / 2;
                } else {
                    t1->val += t->val / 2;
                    t2->val += t->val / 2 + 1;
                }
                ans += t1->val * t1->val;
                ans += t2->val * t2->val;
            }
            --size;
            factories.erase(b);
        } else {
            ++size;
            int64_t t = factories.kth_element(factories.root, b)->val;
            ans -= t * t;
            factories.erase(b);
            if (t % 2 == 0) {
                factories.insert(b, t / 2);
                factories.insert(b + 1, t / 2);
                ans += (t / 2) * (t / 2) + (t / 2) * (t / 2);
            } else {
                factories.insert(b, t / 2);
                factories.insert(b + 1, t / 2 + 1);
                ans += (t / 2) * (t / 2) + (t / 2 + 1) * (t / 2 + 1);
            }
        }
        cout << ans << endl;
    }
    return 0;
}