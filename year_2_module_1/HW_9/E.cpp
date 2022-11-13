#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

struct point {
    double x = 0, y = 0;

    point(double xx, double yy) : x(xx), y(yy) {}
};

struct line {
    double a = 0, b = 0, c = 0;

    line(point A, point B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = A.y * B.x - B.y * A.x;
    }

    bool is_point_on_line(point A) const {
        return a * A.x + b * A.y + c == 0;
    }
};

point intersect(line l1, line l2) {
    double x = (l1.b * l2.c - l1.c * l2.b) / (l1.a * l2.b - l1.b * l2.a);
    double y = (l1.c * l2.a - l1.a * l2.c) / (l1.a * l2.b - l1.b * l2.a);
    return point(x, y);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    line l1(point(x1, y1), point(x2, y2));
    cin >> x1 >> y1 >> x2 >> y2;
    line l2(point(x1, y1), point(x2, y2));
    if (l1.a * l2.b == l1.b * l2.a && l1.a * l2.c == l1.c * l2.a && l1.c * l2.b == l1.b * l2.c) {
        cout << 2;
    } else if (l1.a * l2.b == l1.b * l2.a && l1.a * l2.c != l1.c * l2.a && l1.c * l2.b != l1.b * l2.c) {
        cout << 0;
    } else {
        point B = intersect(l1, l2);
        cout << 1 << " " << B.x << " " << B.y;
    }
    return 0;
}