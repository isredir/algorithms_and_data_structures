#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    unordered_map<int, string> dict;
    for (char i = 32; i < 127; ++i) {
        string s;
        s += i;
        dict[int(i)] = s;
    }
    int dict_len = 127;
    int n;
    cin >> n;
    vector<int> code(n);
    for (int i = 0; i < n; ++i) {
        cin >> code[i];
    }
    string text;
    string s, c;
    string temp = dict[code[0]];
    cout << temp;
    c += temp[0];
    for (int i = 1; i < n; ++i) {
        if (dict.find(code[i]) == dict.end()) {
            s = temp;
            s += c;
        } else {
            s = dict[code[i]];
        }
        cout << s;
        c = s[0];
        temp += c;
        dict_len++;
        dict[dict_len] = temp;
        temp = dict[code[i]];
    }
    cout << text;
}