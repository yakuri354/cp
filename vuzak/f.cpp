// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
using pll = pair<ll, ll>;

struct pt {
    ll x, y;

    pt operator+(const pt &o) const {
        return {x + o.x, y + o.y};
    }
   
    pt operator-() const {
        return {-x, -y};
    }

    pt operator-(const pt &o) const {
        return *this + (-o);
    }

    pt rotl() const {
        return {-y, x};
    }

    pt rotr() const {
        return {y, -x};
    }
};

void solve() {
    ll n;
    cin >> n;

    vector<pt> pts(n);

    for (pt &p: pts) cin >> p.x >> p.y;

    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++) {
        string qt;
        cin >> qt;

        ll x1, y1;
        cin >> x1 >> y1;

        pt p1 = {x1, y1};

        if (qt == "r90") {
            for (ll i = 0; i < n; i++) {
                auto v1 = pts[i] - p1;
                pts[i] = p1 + v1.rotl();
            }
        }

        if (qt == "r180") {
            for (ll i = 0; i < n; i++) {
                auto v1 = pts[i] - p1;
                pts[i] = p1 - v1;
            }
        }

        if (qt == "r270") {
            for (ll i = 0; i < n; i++) {
                auto v1 = pts[i] - p1;
                pts[i] = p1 + v1.rotr();
            }
        }

        if (qt == "ask") {
            ll x2, y2;
            cin >> x2 >> y2;

            ll res = 0;
            for (ll i = 0; i < n; i++) {
                if (x1 <= pts[i].x && pts[i].x <= x2 && y1 <= pts[i].y && pts[i].y <= y2) {
                    res++;
                }
            }

            cout << res << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}


