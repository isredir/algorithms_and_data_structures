#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

struct Node {
    string str;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
};

int count_leaves = 0;

void in_order_count(Node* node) {
    if (node != nullptr) {
        in_order_count(node->left);
        if (node->right == nullptr && node->left == nullptr) {
            ++count_leaves;
        }
        in_order_count(node->right);
    }
}

void in_order(Node* node) {
    if (node != nullptr) {
        in_order(node->left);
        if (node->right == nullptr && node->left == nullptr) {
            cout << node->str << endl;
        }
        in_order(node->right);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        count_leaves = 0;
        string s;
        cin >> s;
        Node* root = new Node();
        Node* cur = root;
        for (char c : s) {
            if (c == 'D') {
                Node* child = new Node();
                cur->left = child;
                child->str = cur->str + '0';
                child->parent = cur;
                cur = child;
            } else {
                Node* prev = cur;
                cur = cur->parent;
                while (prev == cur->right && cur != root) {
                    prev = cur;
                    cur = cur->parent;
                }
                Node* child = new Node();
                cur->right = child;
                child->str = cur->str + '1';
                child->parent = cur;
                cur = child;
            }
        }
        in_order_count(root);
        cout << count_leaves << endl;
        in_order(root);
    }
}