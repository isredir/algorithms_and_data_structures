#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

const double eps = 1e-4;

struct point {
    double x = 0, y = 0;

    string code = "";

    point(double xx, double yy) : x(xx), y(yy) {}

    bool operator==(point B) const {
        return x == B.x && y == B.y;
    }

    bool operator <(point B) const {
        return x < B.x || (x == B.x && y < B.y);
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

    double len() {
        return sqrt((b.x - e.x) * (b.x - e.x) + (b.y - e.y) * (b.y - e.y));
    }
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

    double perimeter() {
        double p = 0;
        for (int i = 1; i < points.size(); ++i) {
            seg s(points[i - 1], points[i]);
            p += s.len();
        }
        seg s(points[points.size() - 1], points[0]);
        p += s.len();
        return p;
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

bool under_seg(point A, seg s) {
    return A.x * (s.b.y - s.e.y) + s.b.x * (s.e.y - A.y) + s.e.x * (A.y - s.b.y) < 0;
}

bool above_seg(point A, seg s) {
    return A.x * (s.b.y - s.e.y) + s.b.x * (s.e.y - A.y) + s.e.x * (A.y - s.b.y) > 0;
}

polygon convex_hull(vector<point> p) {
    if (p.size() == 1) return {{p[0]}};
    sort(p.begin(), p.end());
    point p1 = p[0], p2 = p.back();
    vector<point> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < p.size(); ++i) {
        if (i == p.size() - 1 || under_seg(p1, {p[i], p2})) {
            while (up.size() >= 2 && !under_seg(up[up.size() - 2], {up[up.size() - 1], p[i]})) {
                up.pop_back();
            }
            up.push_back(p[i]);
        }
        if (i == p.size() - 1 || above_seg(p1, {p[i], p2})) {
            while (down.size() >= 2 && !above_seg(down[down.size() - 2], {down[down.size() - 1], p[i]})) {
                down.pop_back();
            }
            down.push_back(p[i]);
        }
    }
    p.clear();
    for (auto & i : up) {
        p.push_back(i);
    }
    for (size_t i = down.size() - 2; i > 0; --i) {
        p.push_back(down[i]);
    }
    return {p};
}

bool cross(point A, seg s) {
    return (s.b.y < A.y && s.e.y > A.y - eps || s.e.y < A.y && s.b.y > A.y - eps) &&
           (A.y * (s.b.x - s.e.x) + s.b.y * s.e.x - s.b.x * s.e.y) / (s.b.y - s.e.y) < A.x;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n, m, r;
    cin >> n >> m >> r;
    vector<point> p;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        p.emplace_back(a, b);
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        for (int j = 0; j < n; ++j) {
            if (a * p[j].x + b * p[j].y + c < 0) {
                p[j].code += '1';
            } else {
                p[j].code += '0';
            }
        }
    }
    unordered_set<string> s;
    for (int i = 0; i < n; ++i) {
        s.insert(p[i].code);
    }
    if (s.size() == n) {
        cout << "NO";
    } else {
        cout << "YES";
    }
    return 0;
}