// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cmath>
#include <iomanip>
#include <iostream>
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

struct line {
    fl k, b;
    
    fl operator()(fl x) const {
        return k * x + b;
    }
};

struct v2 {
    fl x, y;

    v2 operator-(const v2 &o) const {
        return {x - o.x, y - o.y};
    }

    v2 operator+(const v2 &o) const {
        return {x + o.x, y + o.y};
    }

    fl dot(const v2 &o) const {
        return x * o.x + y * o.y;
    }

    fl cross(const v2 &o) const {
        return x * o.y - y * o.x;
    }

    fl len() const {
        return hypotl(x, y);
    }

    fl higher(const line &o) const {
        return o(x) > y;
    }

    line l_to(const v2 &o) const {
        if (x > o.x) return o.l_to(*this);

        fl k = (o.y - y) / (o.x - x);
        fl b = y - k * x;

        return {k, b};
    }
};

struct convex_half {
    vector<v2> pts;

    void add(v2 pt) {
        while (!pts.empty() && pt.cross(pts.back()) > 0) { // sus maybe <
            pts.pop_back();
        }

        pts.push_back(pt);
    }

    bool intersects(v2 from, v2 to) {

    }
};

void solve() {
    ll n;
    cin >> n;

    vector<fl> dp(n, INFINITY);
    dp.back() = 0;

    vector<v2> a(n);
    for (v2 &x: a) {
        cin >> x.x >> x.y;
    }

    // convex_half h1;
    // h1.add(a.back());

    for (ll i = n - 2; i >= 0; i--) {
        for (ll j = i + 1; j < n; j++) {
            for (ll k = i + 1; k < j; k++) {
                if (a[i].l_to(a[j])(a[k].x) <= a[k].y) goto next;
            }

            dp[i] = min(dp[i], max(dp[j], (a[j] - a[i]).len()));

            next:;
        }
    }

    cout << fixed << setprecision(10) << dp[0] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
