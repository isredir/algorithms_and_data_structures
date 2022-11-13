#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x;
    Node *left, *right, *parent;

    Node(int val) {
        left = nullptr;
        right = nullptr;
        x = val;
    }
};

struct Tree {
    Node *root;

    Tree() {
        root = nullptr;
    }

    Node *find_node(Node *node, int x) {
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

    void add_node(int x) {
        Node *node = new Node(x);
        node->parent = nullptr;
        node->right = nullptr;
        node->left = nullptr;
        Node *ptr = root;
        Node *ptr1 = nullptr;
        while (ptr != nullptr) {
            ptr1 = ptr;
            if (x < ptr->x) {
                ptr = ptr->left;
            } else {
                ptr = ptr->right;
            }
        }
        node->parent = ptr1;
        if (ptr1 == nullptr) {
            root = node;
        } else {
            if (x < ptr1->x) {
                ptr1->left = node;
            } else {
                ptr1->right = node;
            }
        }
    }

    int get_height(Node* node) {
        if (node == nullptr) {
            return 0;
        } else {
            return max(get_height(node->right), get_height(node->left)) + 1;
        }
    }

    Node* find_max(Node* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    void in_order(Node* node) {
        if (node != nullptr) {
            in_order(node->left);
            cout << node->x << endl;
            in_order(node->right);
        }
    }

    void print_leaves(Node* node) {
        if (node != nullptr) {
            print_leaves(node->left);
            if (node->right == nullptr && node->left == nullptr) {
                cout << node->x << endl;
            }
            print_leaves(node->right);
        }
    }
};

int main() {
    Tree tree{};
    while(true) {
        int a;
        cin >> a;
        if (a == 0) {
            break;
        }
        if (tree.find_node(tree.root, a) == nullptr) {
            tree.add_node(a);
        }
    }
    tree.print_leaves(tree.root);

    return 0;
}
