#include <bits/stdc++.h>

using namespace std;

enum COLOR { R, B };

struct RBNode {
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    int x;
    COLOR color;

    RBNode(int val, const COLOR& col = R) : left(nullptr), right(nullptr), parent(nullptr), x(val), color(col) {}
};

struct RBTree {
    RBNode *root;
    int count;

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
            cout << node->x << " ";
            if (node->left == nullptr) {
                cout << "null ";
            } else {
                cout << node->left->x << " ";
            }
            if (node->right == nullptr) {
                cout << "null ";
            } else {
                cout << node->right->x << " ";
            }
            if (node->color == B) {
                cout << "B" << endl;
            } else {
                cout << "R" << endl;
            }
            in_order(node->right);
        }
    }
};

int main() {
    int n;
    cin >> n;
    RBTree rbTree;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        //cout << a << " " << b << endl;
        if (a == 0) {
            rbTree.add_node(b);
        } else {
            if (rbTree.find_node(rbTree.root, b)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
        /*cout << "in_order: ";
        rbTree.in_order(rbTree.root);*/
    }
    cout << rbTree.count << endl;
    rbTree.in_order(rbTree.root);
    return 0;
}
