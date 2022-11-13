#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

struct point {
    double x = 0, y = 0;
};

struct line {
    double a = 0, b = 0, c = 0;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    point A, B;
    cin >> A.x >> A.y >> B.x >> B.y;
    line l;
    l.a = B.y - A.y;
    l.b = A.x - B.x;
    l.c = A.y * B.x - B.y * A.x;
    cout << l.a << " " << l.b << " " << l.c;
    return 0;
}