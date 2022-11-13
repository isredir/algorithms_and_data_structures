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

struct polygon {
    vector<point> points;
    polygon(const vector<point>& p) : points(p) {};
    double area() {
        double s = 0;
        for (int i = 1; i < points.size(); ++i) {
            s += (points[i - 1].x * points[i].y - points[i].x * points[i - 1].y);
        }
        s += (points[points.size() - 1].x * points[0].y - points[0].x * points[points.size() - 1].y);
        return abs(s) / 2;
    }
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
    int n;
    cin >> n;
    vector<point> p;
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        p.emplace_back(x, y);
    }
    polygon pol(p);
    cout << fixed << setprecision(5) << pol.area();
    return 0;
}