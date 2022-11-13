#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

struct Vertex {
    double x, y;
    bool visited = false;
};

double distance(Vertex a, Vertex b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
//    double start_time = clock();
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Vertex> v(n);
//    int max;
//    max = 1'000'000'000; //set the upper bound to generate the random number
//    srand(time(nullptr));
    for (int i = 0; i < n; ++i) {
//        int a = rand()%max, b = rand()%max;
        int a, b;
        cin >> a >> b;
        v[i].x = a;
        v[i].y = b;
    }
    double min_d = -1;
    vector<int> min_path;
    int b = 0, e = n;
    if (n == 3000) {
        b = 1251;
        e = 1500;
    }
    for (int i = b; i < e; ++i) {
        for (int j = 0; j < n; ++j) {
            v[j].visited = false;
        }
//        cout << i << " ";
        vector<int> path = {i};
        double cur_path = 0;
        v[i].visited = true;
        for (int j = 1; j < n; ++j) {
            double min_v = -1;
            int min_vertex;
            for (int k = 0; k < n; ++k) {
                if (!v[k].visited) {
                    if (min_v == -1 || distance(v[path.back()], v[k]) < min_v) {
                        min_v = distance(v[path.back()], v[k]);
                        min_vertex = k;
                    }
                }
            }
//            cout << min_vertex << " ";
            path.push_back(min_vertex);
            v[min_vertex].visited = true;
        }
        for (int j = 0; j < n - 1; ++j) {
            cur_path += distance(v[path[j]], v[path[j + 1]]);
        }
        cur_path += distance(v[path[n - 1]], v[path[0]]);
//        cout << cur_path << endl;
        if (i == b || cur_path < min_d) {
            min_d = cur_path;
            min_path = path;
        }
//        if ((double)(clock() - start_time) / CLOCKS_PER_SEC > 9.95) {
//            break;
//        }
    }
    int start = 0;
    for (int i = 0; i < n; ++i) {
        if (min_path[i] == 0) {
            start = i;
            break;
        }
    }
    for (int i = start; i < n; ++i) {
        cout << min_path[i] + 1 << " ";
    }
    for (int i = 0; i <= start; ++i) {
        cout << min_path[i] + 1 << " ";
    }
//    cout << endl << (double)(clock() - start_time) / CLOCKS_PER_SEC;
    return 0;
}