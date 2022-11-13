#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;


bool check(const string& str) {
    stack<char> s;
    for (char i : str) {
        if (i == ')') {
            if (!s.empty() && s.top() == '(') {
                s.pop();
            } else {
                return false;
            }
        } else if (i == ']') {
            if (!s.empty() && s.top() == '[') {
                s.pop();
            } else {
                return false;
            }
        } else {
            s.push(i);
        }
    }
    if (s.empty()) {
        return true;
    }
    return false;
}


void generate(int n, const string& s, int op_br_round, int cl_br_round, int op_br_sq, int cl_br_sq) {
    if (op_br_round + cl_br_round + op_br_sq + cl_br_sq == n && check(s)) {
        cout << s << endl;
    }
    if (op_br_round + op_br_sq < n / 2) {
        generate(n, s + '(', op_br_round + 1, cl_br_round, op_br_sq, cl_br_sq);
    }
    if (op_br_sq + op_br_round < n / 2) {
        generate(n, s + '[', op_br_round, cl_br_round, op_br_sq + 1, cl_br_sq);
    }
    if (op_br_round - cl_br_round > 0) {
        generate(n, s + ')', op_br_round, cl_br_round + 1, op_br_sq, cl_br_sq);
    }
    if (op_br_sq - cl_br_sq > 0) {
        generate(n, s + ']', op_br_round, cl_br_round, op_br_sq, cl_br_sq + 1);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    if (n % 2 != 0) {
        return 0;
    }
    generate(n, "", 0, 0, 0, 0);
    return 0;
}