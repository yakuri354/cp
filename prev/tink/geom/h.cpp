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

vec2 a[1000];

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
       a[i] = iv();
    }

    ll ans = 0;
    for (ll i = 0; i < n - 2; i++) {
        vec2 ab = a[i+1] - a[i], bc = a[i+2] - a[i+1];
        if (ab.cross(bc) > 0) ans++;
    }

    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
