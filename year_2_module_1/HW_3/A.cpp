#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    string code;
    cin >> code;
    int log = 0;
    int d = 1;
    set<int> pows;
    int n = code.size();
    while (d <= n) {
        pows.insert(d);
        d *= 2;
        ++log;
        ++n;
    }
    vector<int> hamming(code.size() + log, 0);
    int pos = 0;
    for (int i = 0; i < hamming.size(); ++i) {
        if (pows.find(i + 1) != pows.end()) {
            continue;
        } else {
            hamming[i] = code[pos] - '0';
            ++pos;
        }
    }
    for (int i = 1; i <= hamming.size(); i *= 2) {
        int s = 0;
        for (int j = i - 1; j < hamming.size(); j += i * 2) {
            for (int k = 0; k < i && j + k < hamming.size(); ++k) {
                s += hamming[j + k];
                s %= 2;
            }
        }
        hamming[i - 1] = s;
    }
    for (int i : hamming) {
        cout << i;
    }
    return 0;
}