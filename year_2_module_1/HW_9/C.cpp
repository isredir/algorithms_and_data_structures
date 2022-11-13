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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    double x, y, x1, y1, x2, y2;
    cin >> x >> y >> x1 >> y1 >> x2 >> y2;
    point A(x, y);
    line l(point(x1, y1), point(x2, y2));
    if (!l.is_point_on_line(A)) {
        cout << "NO";
        return 0;
    }
    if (A.x >= min(x1, x2) && A.x <= max(x1, x2) && A.y >= min(y1, y2) && A.y <= max(y1, y2)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}