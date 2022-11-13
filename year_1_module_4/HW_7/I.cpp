#include <bits/stdc++.h>

using namespace std;

enum COLOR { R, B };

struct RBNode {
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    int x;
    int num;
    COLOR color;

    RBNode(int val, const COLOR& col = R) : left(nullptr), right(nullptr), parent(nullptr), x(val), color(col) {}
};

struct RBTree {
    RBNode *root;
    int count;
    vector<int> seq;

    RBTree() {
        root = nullptr;
        count = 0;
    }

    RBNode *find_node(RBNode *node, int x) {
        if (node == nullptr || x == node->x) {
            return node;
        }
        if (x > node->x) {
            return find_node(node->right, x);
        }
        if (x < node->x) {
            return find_node(node->left, x);
        }
    }

    void rotate_right(RBNode* par) {
        RBNode* l = par->left;
        RBNode* lr = l->right;
        par->left = lr;
        if (lr != nullptr) {
            lr->parent = par;
        }
        l->right = par;
        RBNode* grandpa = par->parent;
        par->parent = l;
        l->parent = grandpa;
        if (grandpa == nullptr) {
            root = l;
        } else if (grandpa->left == par) {
            grandpa->left = l;
        } else {
            grandpa->right = l;
        }
    }

    void rotate_left(RBNode* par) {
        RBNode* r = par->right;
        RBNode* rl = r->left;
        par->right = rl;
        if (rl != nullptr) {
            rl->parent = par;
        }
        r->left = par;
        RBNode* grandpa = par->parent;
        par->parent = r;
        r->parent = grandpa;
        if (grandpa == nullptr) {
            root = r;
        } else if (grandpa->left == par) {
            grandpa->left = r;
        } else {
            grandpa->right = r;
        }
    }

    void add_node(int x) {
        if (root == nullptr) {
            root = new RBNode(x);
            root->color = B;
            ++count;
            return;
        }
        RBNode* cur = root;
        RBNode* par = nullptr;
        while(cur != nullptr) {
            if (x > cur->x) {
                par = cur;
                cur = cur->right;
            } else if (x < cur->x) {
                par = cur;
                cur = cur->left;
            } else {
                return;
            }
        }
        ++count;
        cur = new RBNode(x);
        if (x < par->x) {
            par->left = cur;
        } else {
            par->right = cur;
        }
        cur->parent = par;
        while (cur != root && cur->parent->color == R) {
            RBNode* grandpa = par->parent;
            if (grandpa->left == par) {
                RBNode* uncle = grandpa->right;
                if (uncle != nullptr && uncle->color == R) {
                    par->color = B;
                    uncle->color = B;
                    grandpa->color = R;
                    cur = grandpa;
                    par = cur->parent;
                } else {
                    if (cur == par->right) {
                        rotate_left(par);
                        swap(par, cur);
                    }
                    grandpa->color = R;
                    par->color = B;
                    rotate_right(grandpa);
                }
            } else {
                RBNode* uncle = grandpa->left;
                if (uncle != nullptr && uncle->color == R) {
                    par->color = B;
                    uncle->color = B;
                    grandpa->color = R;
                    cur = grandpa;
                    par = cur->parent;
                } else {
                    if (cur == par->left) {
                        rotate_right(par);
                        swap(par, cur);
                    }
                    grandpa->color = R;
                    par->color = B;
                    rotate_left(grandpa);
                }
            }
        }
        root->color = B;
    }


    void in_order(RBNode* node) {
        if (node != nullptr) {
            in_order(node->left);
            seq.push_back(node->x);
            in_order(node->right);
        }
    }

    bool check_black_len(RBNode* cur, int counter, int k) {
        if (cur == nullptr) {
            if (k != counter) {
                return false;
            }
            return true;
        }
        if (cur->color == B) {
            ++k;
        }
        RBNode* par = cur->parent;
        if (par != nullptr && par->color == R && cur->color == R) {
            return false;
        }
        return check_black_len(cur->left, counter, k) && check_black_len(cur->right, counter, k);
    }

    bool check_rbTree() {
        if (root == nullptr) {
            return true;
        }
        if (root->color == R) {
            return false;
        }
        int black = 0;
        RBNode* cur = root;
        while (cur != nullptr) {
            if (cur->color == B) {
                ++black;
            }
            cur = cur->left;
        }
        return check_black_len(root, black, 0);
    }
};

struct Node {
    int num, key;
    int left, right;
    COLOR color;
};

void build (const vector<Node>& nodes, int i, RBNode* cur) {
    if (i == -1) {
        cur = nullptr;
        return;
    }
    cur->color = nodes[i].color;
    RBNode* left;
    if (nodes[i].left != -1) {
        left = new RBNode(nodes[nodes[i].left].key);
    } else {
        left = new RBNode(-1);
    }
    build(nodes, nodes[i].left, left);
    RBNode* right;
    if (nodes[i].right != -1) {
        right = new RBNode(nodes[nodes[i].right].key);
    } else {
        right = new RBNode(-1);
    }
    build(nodes, nodes[i].right, right);
    if (nodes[i].left != -1) {
        left->parent = cur;
        cur->left = left;
    }
    if (nodes[i].right != -1) {
        right->parent = cur;
        cur->right = right;
    }
}

int main() {
    int n;
    cin >> n;
    if (n == 0) {
        cout << "YES";
        return 0;
    }
    int root;
    cin >> root;
    vector<Node> nodes(n + 1);
    for (int i = 0; i < n; ++i) {
        Node node;
        int num, key;
        cin >> num >> key;
        node.num = num;
        node.key = key;
        string left, right, color;
        cin >> left >> right >> color;
        if (left == "null") {
            node.left = -1;
        } else {
            node.left = stoi(left);
        }
        if (right == "null") {
            node.right = -1;
        } else {
            node.right = stoi(right);
        }
        if (color == "B") {
            node.color = B;
        } else {
            node.color = R;
        }
        nodes[node.num] = node;
    }
    RBTree rbTree;
    RBNode* tree_root = new RBNode(nodes[root].key);
    build(nodes, root, tree_root);
    rbTree.root = tree_root;
    rbTree.in_order(rbTree.root);
    for (int i = 1; i < n; ++i) {
        if (rbTree.seq[i] <= rbTree.seq[i - 1]) {
            cout << "NO";
            return 0;
        }
    }
    if (rbTree.check_rbTree()) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
