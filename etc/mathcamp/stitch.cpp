// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

const fl eps = 1e-9;

bool zero(fl x) {
    return abs(x) < eps;
}

struct v2 {
    fl x, y;

    v2(fl x, fl y) : x(x), y(y) {
    }

    v2() : x(0), y(0) {
    }

    fl dot(const v2& other) const {
        return x * other.x + y * other.y;
    }

    fl operator*(const v2& other) const {
        return dot(other);
    }

    fl cross(const v2& other) const {
        return x * other.y - y * other.x;
    }

    fl operator%(const v2& other) const {
        return cross(other);
    }

    v2 operator-(const v2& other) const {
        return {x - other.x, y - other.y};
    }

    v2 operator+(const v2& other) const {
        return {x + other.x, y + other.y};
    }

    v2 operator*(fl k) const {
        return {x * k, y * k};
    }

    v2 operator/(fl k) const {
        return {x / k, y / k};
    }

    fl len() const {
        return hypotl(x, y);
    }

    bool operator==(const v2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const v2& other) const {
        return this->cross(other) > 0;
    }

    bool operator>(const v2& other) const {
        return this->cross(other) < 0;
    }

    bool operator<=(const v2& other) const {
        return *this < other || colin(other);
    }

    bool operator>=(const v2& other) const {
        return *this > other || colin(other);
    }

    bool colin(const v2& other) const {
        return zero(this->cross(other));
    }

    bool codir(const v2& other) const {
        return colin(other) && dot(other) > 0;
    }

    v2 unit_dir() const {
        return *this / len();
    }

    v2 norm() const {
        return {-y, x};
    }

    bool between_strict(const v2& a, const v2& b) const {  // sus
        if (a < b)
            return between_strict(b, a);
        return a > *this && *this > b;  // || between_strict(b, a);
    }

    bool between_weak(const v2& a, const v2& b) const {  // sus
        if (a < b)
            return between_weak(b, a);
        return a >= *this && *this >= b;  // || between_weak(b, a);
    }

    fl angle(const v2& other) const {
        return atan2l(cross(other), dot(other));
    }

    v2 to(const v2& other) const {
        return other - *this;
    }

    pair<fl, fl> to_pair() const {
        return make_pair(x, y);
    }

    static bool compare_as_pair(const v2 &a, const v2 &b) {
        return a.to_pair() < b.to_pair();
    }
};

// / / / /
// ///////

mt19937_64 mt(1337);

struct seg {
    v2 from, to;

    ll token;

    seg(v2 a, v2 b): from(a), to(b), token(uniform_int_distribution<ll>(INT64_MIN, INT64_MAX)(mt)){}

    bool operator<(const seg &o) const {
        return token < o.token;
    }
};

ll lg2(ll x) {
    return 63 - __builtin_clzll(x);
}

void solve() {
    vector<seg> pts;   

    ll n;
    cin >> n;
    n = n * 2 - 1;

    for (ll i = 0; i < n; i++) {
        pts.push_back({{fl(i), 0}, {fl(i) + 1, 1}});
        if (i % 2 == 0) {
            pts.push_back({{fl(i), 1}, {fl(i) + 1, 2}});
        }
    }

    ll cnt = pts.size();

    fl ans = INFINITY;

    vector<seg> z;
    ll ma = 0;

    cout << "out of " << cnt << endl;
    for (ll m = 0; m < (1 << cnt); m++) {
        if (m != 0 && lg2(m) > lg2(m - 1)) {
            cout << lg2(m) << " " << ans << endl;
        }

        auto p2 = pts;

        for (ll i = 0; i < cnt; i++) {
            if ((m >> i) & 1) {
                swap(p2[i].from, p2[i].to);
            }
        }

        // for (ll i = 0; i < cnt - 1; i++) {
        //     if (zero(p2[i].to.to(p2[i+1].from).len())) {
        //         goto nxt;
        //     }
        // }

        sort(p2.begin(), p2.end());
        while (next_permutation(p2.begin(), p2.end())) {
            fl ans2 = sqrt(2);
            for (ll i = 0; i < cnt - 1; i++) {
                if (zero(p2[i].to.to(p2[i+1].from).len())) {
                    ans2 += sqrt(2);
                }
                ans2 += p2[i].from.to(p2[i].to).len() + p2[i].to.to(p2[i+1].from).len();
            }
            if (ans2 < ans) {
                ans = ans2;
                z = p2;
                ma = m;
            }
        }
        nxt:;
    }

    cout << ans << endl;

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
