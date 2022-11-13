#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const double eps = 1e-4;

struct point {
    double x = 0, y = 0;

    point(double xx, double yy) : x(xx), y(yy) {}

    bool operator==(point B) const {
        return x == B.x && y == B.y;
    }
};

struct line {
    double a = 0, b = 0, c = 0;

    line(point A, point B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = A.y * B.x - B.y * A.x;
    }

    bool is_point_on_line(point A) const {
        return abs(a * A.x + b * A.y + c) == 0;
    }
};

struct seg {
    point b, e;

    seg(point aa, point bb) : b(aa), e(bb) {};
};

struct polygon {
    vector<point> points;

    polygon(const vector<point> &p) : points(p) {};

    double area() {
        double s = 0;
        for (int i = 1; i < points.size(); ++i) {
            s += (points[i - 1].x * points[i].y - points[i].x * points[i - 1].y);
        }
        s += (points[points.size() - 1].x * points[0].y - points[0].x * points[points.size() - 1].y);
        return abs(s) / 2;
    }
};

struct triangle {
    point A, B, C;

    triangle(point AA, point BB, point CC) : A(AA), B(BB), C(CC) {}

    double area() const {
        return abs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    }
};

point intersect(line l1, line l2) {
    double x = (l1.b * l2.c - l1.c * l2.b) / (l1.a * l2.b - l1.b * l2.a);
    double y = (l1.c * l2.a - l1.a * l2.c) / (l1.a * l2.b - l1.b * l2.a);
    return {x, y};
}

bool is_point_on_seg(point A, seg s) {
    if (fabs(s.e.x - s.b.x) < eps) {
        if (fabs(A.x - s.b.x) < eps && A.y > min(s.b.y, s.e.y) - eps && A.y - eps < max(s.b.y, s.e.y)) {
            return true;
        }
    } else {
        if (A.x - s.b.x - eps < max(s.b.x, s.e.x - s.b.x) && A.x - s.b.x > min(s.b.x, s.e.x - s.b.x) - eps &&
            fabs((s.e.x - s.b.x) * (A.y - s.b.y) - (s.e.y - s.b.y) * (A.x - s.b.x)) < eps) {
            return true;
        }
    }
    return false;
}

bool cross(point A, seg s) {
    return (s.b.y < A.y && s.e.y > A.y - eps || s.e.y < A.y && s.b.y > A.y - eps) &&
           (A.y * (s.b.x - s.e.x) + s.b.y * s.e.x - s.b.x * s.e.y) / (s.b.y - s.e.y) < A.x;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, a, b;
    cin >> n >> a >> b;
    point A(a, b);
    vector<point> p;
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        p.emplace_back(x, y);
    }
    if (n == 1) {
        if (A == p[0]) {
            cout << "YES";
        } else {
            cout << "NO";
        }
        return 0;
    }
    if (n == 2) {
        seg s(p[0], p[1]);
        if (is_point_on_seg(A, s)) {
            cout << "YES";
        } else {
            cout << "NO";
        }
        return 0;
    }
    polygon pol(p);
    bool on_side = false;
    int intersections = 0;
    for (int i = 0; i < n - 1; ++i) {
        seg s{p[i], p[i + 1]};
        if (is_point_on_seg(A, s)) {
            on_side = true;
            cout << "YES";
            return 0;
        }
        if (cross(A, s)) {
            ++intersections;
            intersections %= 2;
        }
    }

    seg s{p[n - 1], p[0]};
    if (is_point_on_seg(A, s)) {
        on_side = true;
        cout << "YES";
        return 0;
    }
    if (cross(A, s)) {
        ++intersections;
        intersections %= 2;
    }
    if (intersections % 2 == 0) {
        cout << "NO";
    } else {
        cout << "YES";
    }
    return 0;
}