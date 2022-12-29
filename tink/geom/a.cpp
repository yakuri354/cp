// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct vec2 {
    fl x, y;

    vec2(fl x, fl y) : x(x), y(y) {}

    vec2 operator+(const vec2 &other) {
        return vec2(this->x + other.x, this->y + other.y);
    }

    fl dot(const vec2 &other) {
        return this->x * other.x + this->y * other.y;
    }

    fl cross(const vec2 &other) {
        return this->x * other.y - this->y * other.x;
    }
};

void solve() {
    fl x1, y1, x2, y2, x3, y3;

    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    vec2 a(x2 - x1, y2 - y1), b(x3 - x1, y3 - y1);

    cout << abs(a.cross(b)) / 2.0 << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
