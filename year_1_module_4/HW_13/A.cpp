#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < int(pow(2, n)); ++i) {
        int m = i;
        int k = 0;
        string str;
        while (m > 0) {
            str = to_string((m % 2)) + str;
            m /= 2;
            ++k;
        }
        while (str.size() < n) {
            str = "0" + str;
        }
        cout << str << '\n';
    }

    return 0;
}