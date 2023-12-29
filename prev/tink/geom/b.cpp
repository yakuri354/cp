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

    vec2 operator-(const vec2 &other) {
        return vec2(this->x - other.x, this->y - other.y);
    }

    vec2 operator-() {
        return vec2(-this->x, -this->y);
    }

    fl dot(const vec2 &other) {
        return this->x * other.x + this->y * other.y;
    }

    fl cross(const vec2 &other) {
        return this->x * other.y - this->y * other.x;
    }
};

vec2 iv() {
    fl x, y;
    cin >> x >> y;
    return vec2(x, y);
}

void solve() {
    vec2 a = iv(), o = iv(), b = iv(), p = iv();
    vec2 oa = a - o, ob = b - o, op = p - o;

    if (oa.cross(ob) > 0) swap(oa, ob);

    if (oa.cross(op) <= 0 && ob.cross(op) >= 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
