#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const double eps = 1e-4;

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
        return abs(a * A.x + b * A.y + c) <= eps;
    }
};

struct seg {
    point b, e;
    seg(point aa, point bb) : b(aa), e(bb) {};
};

point intersect(line l1, line l2) {
    double x = (l1.b * l2.c - l1.c * l2.b) / (l1.a * l2.b - l1.b * l2.a);
    double y = (l1.c * l2.a - l1.a * l2.c) / (l1.a * l2.b - l1.b * l2.a);
    return {x, y};
}

bool is_point_on_seg(point A, seg s) {
    line l(s.b, s.e);
    if (!l.is_point_on_line(A)) {
        return false;
    }
    if (A.x >= min(s.b.x, s.e.x) && A.x <= max(s.b.x, s.e.x) && A.y >= min(s.b.y, s.e.y) && A.y <= max(s.b.y, s.e.y)) {
        return true;
    } else {
        return false;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    seg s1(point(x1, y1), point(x2, y2));
    line l1(point(x1, y1), point(x2, y2));
    cin >> x1 >> y1 >> x2 >> y2;
    seg s2(point(x1, y1), point(x2, y2));
    line l2(point(x1, y1), point(x2, y2));
    if (is_point_on_seg(s1.e, s2) || is_point_on_seg(s2.b, s1) || is_point_on_seg(s2.e, s1) || is_point_on_seg(s1.b, s2)) {
        cout << "YES";
        return 0;
    }
    if (l1.a * l2.b == l1.b * l2.a && l1.a * l2.c == l1.c * l2.a && l1.c * l2.b == l1.b * l2.c) {
        if (is_point_on_seg(s1.e, s2) || is_point_on_seg(s2.b, s1) || is_point_on_seg(s2.e, s1) || is_point_on_seg(s1.b, s2)) {
            cout << "YES";
        } else {
            cout << "NO";
        }
    } else if (l1.a * l2.b == l1.b * l2.a && l1.a * l2.c != l1.c * l2.a && l1.c * l2.b != l1.b * l2.c) {
        cout << "NO";
    } else {
        point B = intersect(l1, l2);
        if (is_point_on_seg(B, s1) && is_point_on_seg(B, s2)) {
            cout << "YES";
        } else {
            cout << "NO";
        }
    }
    return 0;
}