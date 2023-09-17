#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const fl eps = 1e-9;
const fl max_abs_c = 1e9;

mt19937_64 mt(0xab0ba);

bool zero(fl x) {
    return abs(x) < eps;
}

ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }

    return gcd(b, a % b);
}

struct ipt {
    ll x, y;

    ipt(ll x, ll y) : x(x), y(y) {
    }
    explicit ipt() : x(0), y(0) {
    }

    ipt operator-(const ipt& other) const {
        return {x - other.x, y - other.y};
    }

    ipt operator*(ll s) const {
        return {x * s, y * s};
    }

    ipt operator+(const ipt& other) const {
        return {x + other.x, y + other.y};
    }

    fl magnitude() const {
        return sqrtl(fl(x * x) + fl(y * y));
    }

    ll dot_prod(const ipt& other) const {
        return x * other.x + y * other.y;
    }

    bool kinda_codir(const ipt& other) const {
        return dot_prod(other) > 0;
    }

    bool operator==(const ipt& other) const {
        return x == other.x && y == other.y;
    }

    ipt shortened() const {
        if (x == 0 && y == 0) {
            return {0, 0};
        }
        if (x == 0) {
            return {x, 1};
        }
        if (y == 0) {
            return {1, y};
        }
        ll g = gcd(abs(x), abs(y));

        return {x / g, y / g};
    }
};

template <typename T>
struct iseg_iter {
    T seg;
    ipt curr;

    ipt operator*() const {
        return curr;
    }

    void operator++() {
        if (curr == seg.last) {
            return;
        }
        curr = curr + seg.step;
    }

    void operator++(int) {
        if (curr == seg.last) {
            return;
        }
        curr = curr + seg.step;
    }

    bool operator==(const iseg_iter& other) const {
        return seg == other.seg && curr == other.curr;
    }

    bool operator!=(const iseg_iter& other) const {
        return !(*this == other);
    }
};

struct iseg {
    ipt first, last;

    ipt step;

    bool operator==(const iseg& other) const {
        return first == other.first && last == other.last;
    }

    bool operator!=(const iseg& other) const {
        return !(*this == other);
    }

    bool has(const ipt& other) const { // mega fucking sus
        ipt p2 = other - first;

        return other == first || other == last ||
               (p2.x % step.x == 0 && p2.y % step.y == 0 &&
                p2.y / step.y == p2.x / step.x &&
                (p2 - first).kinda_codir(step) &&
                (p2 - first).magnitude() <= (last - first).magnitude());
    }

    iseg_iter<iseg> begin() const {
        auto it = iseg_iter<iseg>{*this, first};
        it++;
        return it;
    }

    iseg_iter<iseg> end() const {
        return iseg_iter<iseg>{*this, last};
    }

    iseg(ipt begin, ipt end)
        : first(begin), last(end), step((end - begin).shortened()) {
    }
};

// ipt r_up_corner, origin;
ipt pC, pS;

// bool is_corner(ipt pt) {
// return abs(pt.x) % r_up_corner.x == 0 && abs(pt.y) % r_up_corner.y == 0;
// }

ll xc, yc, xs, ys;
ll w, h, k;

ipt stone_in_room(ll x_room, ll y_room) {
    ipt rel_stone = pS;
    if (abs(x_room) % 2 == 1) {
        rel_stone.x = w - rel_stone.x;
    }
    if (abs(y_room) % 2 == 1) {
        rel_stone.y = h - rel_stone.y;
    }

    rel_stone.x = rel_stone.x + w * x_room;
    rel_stone.y = rel_stone.y + h * y_room;

    return rel_stone;
}

void solve() {
    cin >> w >> h;

    // r_up_corner = {w, h};
    // origin = {0, 0};

    cin >> k;

    cin >> xc >> yc >> xs >> ys;

    pC = {xc, yc};
    pS = {xs, ys};

    ll best_ints = inf;

    for (ll x_room = -k - 1; x_room <= k + 2; x_room++) {
        for (ll y_room = -k - 1; y_room <= k + 2; y_room++) {
            ll total_ints = abs(x_room) + abs(y_room);
            if (x_room > 0) total_ints -= 1;
            if (y_room > 0) total_ints -= 1;

            if (total_ints >= best_ints) continue;
            if (total_ints > k) continue;
            
            ipt pTgt = {w * x_room, h * y_room};
            // iseg path(pC, pTgt);

            
        }
    }

    if (best_ints == inf) {
        cout << -1 << endl;
    } else {
        cout << best_ints << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)

    solve();
}
