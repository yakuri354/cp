#include <cstdio>
// #pragma GCC optimize("Ofast")
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

ipt r_up_corner, origin;
ipt pC, pS;

bool is_stone(ipt pt) {
    ll room_x = pt.x / r_up_corner.x;
    ll room_y = pt.y / r_up_corner.y;

    ipt rel_stone = pS;
    if (abs(room_x) % 2 == 1) {
        rel_stone.x = r_up_corner.x - rel_stone.x;
    }
    if (abs(room_y) % 2 == 1) {
        rel_stone.y = r_up_corner.y - rel_stone.y;
    }

    rel_stone.x = rel_stone.x + r_up_corner.x * room_x;
    rel_stone.y = rel_stone.y + r_up_corner.y * room_y;

    return rel_stone == pt;
}

bool is_corner(ipt pt) {
    return abs(pt.x) % r_up_corner.x == 0 && abs(pt.y) % r_up_corner.y == 0;
}

ll xc, yc, xs, ys;
ll w, h, k;

ipt ans;

void solve() {
    // cin >> w >> h;

    r_up_corner = {w, h};
    origin = {0, 0};

    // cin >> k;

    // cin >> xc >> yc >> xs >> ys;

    pC = {xc, yc};
    pS = {xs, ys};

    ll best_ints = inf;

    for (ll x_room = -k; x_room <= k + 1; x_room++) {
        for (ll y_room = -k; y_room <= k + 1; y_room++) {
            ll total_ints = abs(x_room) + abs(y_room);
            if (x_room > 0) {
                total_ints -= 1;
            }
            if (y_room > 0) {
                total_ints -= 1;
            }

            if (total_ints >= best_ints) {
                continue;
            }
            if (total_ints > k) {
                continue;
            }

            ipt pTgt = {w * x_room, h * y_room};
            iseg path(pC, pTgt);

            bool stone_intersect = false;
            for (ipt pt : path) {
                if (is_corner(pt)) {
                    goto next;
                }
                if (is_stone(pt) && stone_intersect) {
                    goto next;  // cocos is left where stone was
                } else if (is_stone(pt)) {
                    stone_intersect = true;
                }
            }

            if (!stone_intersect) {
                goto next;
            }

            best_ints = min(best_ints, total_ints);

            if (total_ints < best_ints) {
                best_ints = total_ints;
                ans = pTgt;
            }

        next:;
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

    freopen("/dev/null", "w", stdout);

    uniform_int_distribution<ll> sd(3, 1000);

    uniform_int_distribution<ll> kd(0, 200);

    for (;;) {
        w = sd(mt), h = sd(mt);

        k = kd(mt);

        uniform_int_distribution<ll> xcd(1, w - 1);
        uniform_int_distribution<ll> ycd(1, h - 1);

        xc = xcd(mt), xs = xcd(mt);
        yc = ycd(mt), ys = ycd(mt);

        solve();

        iseg path(pC, ans);

        ll is = 0;

        for (ipt p : path) {
        }
    }

    // solve();
}
