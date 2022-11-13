#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

struct Node {
    map<char, Node*> trie;
    Node* suf = nullptr;
    map<char, Node*> go;
    Node* parent = nullptr;
    char chr;
    bool term = false;
    bool sub_term = false;
    int depth = 0;
    int visited = -1;
};


struct Bor {
    Node* root;
    set<char> alphabet = {'0', '1'};
    Bor(const vector<string>& patterns) {
        root = new Node();
        for (const string& s : patterns) {
            Node* node = root;
            for (char c : s) {
                if (node->trie.find(c)!= node->trie.end()) {
                    node = node->trie[c];
                } else {
                    Node* v = new Node();
                    v->parent = node;
                    v->chr = c;
                    v->depth = node->depth + 1;
                    node->trie[c] = v;
                    node = v;
                }
            }
            node->term = true;
            node->sub_term = true;
        }
        queue<Node*> q;
        root->suf = suf(root);
        if (root->suf->sub_term) {
            root->sub_term = true;
        }
        for (char sym : alphabet) {
            root->go[sym] = go(root, sym);
        }
        q.push(root);
        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();
            for (auto [c, node]: cur->trie) {
                node->suf = suf(node);
                if (node->suf->sub_term) {
                    node->sub_term = true;
                }
                for (char sym : alphabet) {
                    node->go[sym] = go(node, sym);
                }
                q.push(node);
            }
        }
    }

    Node* go(Node* node, char c) {
        if (node->trie.find(c) != node->trie.end()) {
            return node->trie[c];
        } else if (node == root) {
            return root;
        } else {
            return go(node->suf, c);
        }
    }

    Node* suf(Node* node) {
        if (node->depth <= 1) {
            return root;
        }
        else {
            return go(node->parent->suf, node->chr);
        }
    }

    void dfs(Node* node) {
        if (node->visited == 1) {
            return;
        }
        node->visited = 0;
        for (auto [c, v] : node->go) {
            if (!v->sub_term) {
                if (v->visited == 0) {
                    cout << "TAK";
                    exit(0);
                }
                dfs(v);
            }
        }
        node->visited = 1;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int k;
    cin >> k;
    vector<string> patterns(k);
    for (int i = 0; i < k; i++) {
        cin >> patterns[i];
    }
    Bor bor(patterns);
    bor.dfs(bor.root);
    cout << "NIE";
    return 0;
}