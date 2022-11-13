#include <bits/stdc++.h>

using namespace std;

struct Fenvick {
    int n;
    vector<vector<int>> table;

    Fenvick(int nn) {
        n = nn;
        table = vector<vector<int>>(n, vector<int>(n, 0));
    }

    int sum(int x, int y) {
        int result = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
                result += table[i][j];
            }
        }
        return result;
    }

    void inc(int x, int y, int delta) {
        for (int i = x; i < n; i = (i | (i + 1))) {
            for (int j = y; j < n; j = (j | (j + 1))) {
                table[i][j] += delta;
            }
        }
    }

    int sum_on_reg(int l, int b, int r, int t) {
        return sum(r, t) - sum(l - 1, t) - sum(r, b - 1) + sum(l - 1, b - 1);
    }

};

int main() {
    int command, s;
    cin >> command >> s;
    Fenvick F(s);
    while (true) {
        cin >> command;
        if (command == 1) {
            int x, y, a;
            cin >> x >> y >> a;
            F.inc(x, y, a);
        }
        if (command == 2) {
            int l, b, r, t;
            cin >> l >> b >> r >> t;
            cout << F.sum_on_reg(l, b, r, t) << "\n";
        }
        if (command == 3) {
            break;
        }
    }
    return 0;
}