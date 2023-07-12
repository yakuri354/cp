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
    vec2() : x(0), y(0) {}

    fl dot(const vec2 &other) const {
        return this->x * other.x + this->y * other.y;
    }

    fl cross(const vec2 &other) const {
        return this->x * other.y - this->y * other.x;
    }

    fl mg() const {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    vec2 operator+(const vec2 &other) const {
        return vec2(this->x + other.x, this->y + other.y);
    }

    vec2 operator-() const {
        return vec2(-this->x, -this->y);
    }

    vec2 operator-(const vec2 &other) const {
        return *this + (-other);
    }
};

const ll maxn = 1e5;

vec2 arr[maxn];

void solve() {
    ll n;

    cin >> n;

    for (ll i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        arr[i] = {fl(x), fl(y)};
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
        solve();
}
