#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    string code;
    cin >> code;
    vector<int> hamming(code.size(), -1);
    set<int> pows;
    for (int i = 1; i <= hamming.size(); i *= 2) {
        pows.insert(i - 1);
        hamming[i - 1] = 0;
    }
    for (int i = 0; i < hamming.size(); ++i) {
        if (hamming[i] == -1) {
            hamming[i] = code[i] - '0';
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
    int sum = 0;
    bool mistake = false;
    for (int i = 1; i <= hamming.size(); i *= 2) {
        if (hamming[i - 1] != code[i - 1] - '0') {
            mistake = true;
            sum += i;
        }
    }
    if (mistake) {
        code[sum - 1] = '1' + '0' - code[sum - 1];
    }
    for (int i = 0; i < code.size(); ++i) {
        if (pows.find(i) == pows.end()) {
            cout << code[i];
        }
    }
    return 0;
}