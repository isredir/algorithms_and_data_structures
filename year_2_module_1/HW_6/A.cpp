#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

struct Snowman {
    int64_t mass = 0;
    int parent;
    Snowman(int m, int p) : mass(m), parent(p) {}
};



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Snowman> v = {Snowman(0, 0)};
    int64_t s = 0;
    for (int i = 1; i <= n; ++i) {
        int64_t t, m;
        cin >> t >> m;
        if (m != 0) {
            v.emplace_back(v[t].mass + m, t);
        } else {
            v.emplace_back(v[v[t].parent]);
        }
        s += v[i].mass;
    }
    cout << s;
    return 0;
}