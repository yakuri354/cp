// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
#include <cmath>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct vec2 {
    fl x, y;

    vec2() : x(0), y(0) {}
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

    fl angle(const vec2 &other) {
        return atan2l(this->cross(other), this->dot(other));
    }
};

vec2 iv() {
    fl x, y;
    cin >> x >> y;
    return vec2(x, y);
}

void solve() {

}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
