#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

static char getNot(char c1, char c2) {
    for (char color : "RGB") {
        if (color != c1 && color != c2) {
            return color;
        }
    }
    return '0';
}

struct Vertex;


struct Vertex {
    int index;
    char prevColor;
    char newColor = '0';
    vector<Vertex*> neig;
    bool marked;

    bool trySet(char color) {
//        cout << "start " << color << " " << prevColor << " " << index << endl;
        marked = true;
        if (color == prevColor) {
            return false;
        } else {
            char c = newColor;
            newColor = color;
            bool ok = true;
//            cout << neig.size() << endl;
            for (Vertex* vert : neig) {
//                cout << vert->prevColor << " " << vert->newColor << " " << vert->marked << " " << vert->index << " ";
                if (vert->marked) {
                    if (vert->newColor == color) {
                        ok = false;
                    }
                } else {
                    if (vert->prevColor != color) {
                        if (!vert->trySet(getNot(vert->prevColor, color))) {
                            ok = false;
                        }
                    }
                }
            }
//            cout << endl;
            if (!ok) {
                newColor = c;
            }
//            cout << "end " << newColor << endl;
            return ok;
        }
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<Vertex*> v;
    for (int i = 0; i < n; ++i) {
        auto *vert = new Vertex();
        vert->prevColor = s[i];
        vert->marked = false;
        vert->index = i;
        v.push_back(vert);
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        v[a - 1]->neig.push_back(v[b - 1]);
        v[b - 1]->neig.push_back(v[a - 1]);
    }
//    for (int i = 0; i < n; i++) {
//        for (Vertex* vert : v[i]->neig) {
//            cout << vert->neig.size() << " ";
//        } cout << endl;
//    }cout << endl;
    for (int i = 0; i < n; i++) {
        if (v[i]->newColor != 'R' && v[i]->newColor != 'G' && v[i]->newColor != 'B') {
//            cout << "not ok " << i << endl;
            for (char color: "RGB") {
                for (Vertex* vertex: v) {
                    vertex->marked = false;
                }
                if (v[i]->trySet(color)) {
                    break;
                }
            }
        }
    }
    bool ok = true;
    for (const Vertex* vertex: v) {
        if (vertex->newColor != 'R' && vertex->newColor != 'G' && vertex->newColor != 'B') {
            ok = false;
        }
    }
    if (ok) {
        for (const Vertex* vertex: v) {
            cout << vertex->newColor;
        }
    } else {
        cout << "Impossible";
    }
    return 0;
}