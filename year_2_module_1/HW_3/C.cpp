#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    unordered_map<string, int> dict;
    for (char i = 32; i < 127; ++i) {
        string s;
        s += i;
        dict[s] = int(i);
    }
    int dict_len = 127;
    string text;
    getline(cin, text);
    text += " ";
    string temp;
    vector<int> code;
    for (int i = 0; i < text.size(); ++i) {
        string prev = temp;
        temp += text[i];
        if (dict.find(temp) == dict.end()) {
            code.push_back(dict[prev]);
            ++dict_len;
            dict[temp] = dict_len;
            temp = "";
            temp += text[i];
        }
    }
    cout << code.size() << endl;
    for (int i : code) {
        cout << i << " ";
    }
}