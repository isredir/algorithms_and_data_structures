#include <bits/stdc++.h>


using namespace std;
const int maxN = 402000;

struct Node {
    int y, val, size = 1, mod = 0;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int _val) { val = _val, y = rand(); }
};

Node *root[2];

int get_size(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->size;
}

void upd(Node *node) {
    if (node == nullptr) {
        return;
    }
    node->size = 1 + get_size(node->left) + get_size(node->right);
}

void push(Node *node) {
    if (!node)
        return;
    if (node->mod) {
        if (node->left) {
            node->left->mod += node->mod;
        }
        if (node->right) {
            node->right->mod += node->mod;
        }
        node->val += node->mod;
        node->mod = 0;
    }
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

bool flag = false;

int less_than(Node *node, int x) {
    int cnt = 0;
    while (node) {
        push(node);
        if (node->val == x) {
            node = node->right;
            continue;
        }
        if (node->val > x) {
            node = node->right;
        } else {
            cnt++;
            if (node->right) {
                cnt += node->right->size;
            }
            node = node->left;
        }
    }
    return cnt;

}


Node *add(Node *t, int len, int x) {
    auto p = split(t, len);
    p.first->mod += x;
    return merge(p.first, p.second);
}

int cur = 0;

Node *insert(Node *node, int x) {
    Node *tree = node;
    int cnt = 0;
    cnt = less_than(node, x);
    cnt = node->size - cnt;
    Node *nd = new Node(x);
    auto p = split(tree, cnt);
    return merge(merge(p.first, nd), p.second);
}

Node *rem(Node *node, int x) {
    Node *tree = node;
    int cnt = 0;
    flag = 0;
    while (node) {
        push(node);
        if (node->val == x) {
            flag = true;
            if (node->left) {
                cnt += node->left->size;
            }
            break;
        }
        if (node->val < x) {
            node = node->left;
        } else {
            cnt++;
            if (node->left) {
                cnt += node->left->size;
            }
            node = node->right;
        }
    }
    if (!flag)
        return tree;
    auto p1 = split(tree, cnt + 1);
    auto p2 = split(p1.first, cnt);
    return merge(p2.first, p1.second);
}

void print_tree(Node *node) {
    if (node == nullptr) { return; }
    push(node);
    print_tree(node->right);
    if (node->val != 0) { cout << node->val << " "; }
    print_tree(node->left);
}


int main() {
    int n, m;
    cin >> n >> m;
    int a[maxN];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    reverse(a, a + n);
    for (int j = maxN; j >= 0; j--) {
        Node *nd = new Node(0);
        root[1] = merge(root[1], nd);
    }
    for (int i = 0; i < n; i++) {
        Node *nd = new Node(a[i]);
        root[cur] = merge(root[cur], nd);
        root[1 - cur] = add(root[1 - cur], a[i], 1);
    }
    for (int j = maxN; j >= 0; j--) {
        Node *nd = new Node(0);
        root[0] = merge(root[0], nd);
    }
    for (int i = 0; i < m; i++) {
        char tp;
        int x;
        cin >> tp;
        if (tp == 'a') {
            cin >> x;
            root[1 - cur] = add(root[1 - cur], x, 1);
            root[cur] = insert(root[cur], x);
        }
        if (tp == 'r') {
            cin >> x;
            root[cur] = rem(root[cur], x);
            if (flag) {
                root[1 - cur] = add(root[1 - cur], x, -1);
            }
        }
        if (tp == 'c') {
            cin >> x;
            cout << less_than(root[cur], x + 1) - less_than(root[cur], x) << endl;
        }
        if (tp == 't') {
            cur = 1 - cur;
        }
    }
    print_tree(root[cur]);

    return 0;
}
