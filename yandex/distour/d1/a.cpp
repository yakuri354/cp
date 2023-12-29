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

const fl eps = 1e-10;

bool zero(fl x) {
    return abs(x) < eps;
}

struct v2 {
    fl x, y;

    v2 operator*(fl a) const {
        return {a * x, a * y};
    }

    v2 operator-(const v2 &o) const {
        return {x - o.x, y - o.y};
    }

    fl cross(const v2 &o) const {
        return x * o.y - y * o.x;
    }

    fl dot(const v2 &o) const {
        return x * o.x + y * o.y;
    }

    bool colin(const v2 &o) const {
        return zero(cross(o));
    }

    bool codir(const v2 &o) const {
        return colin(o) && dot(o) > 0;
    }

    fl len() const {
        return hypotl(x, y);
    }
};

struct line {
    fl a, b, c;

    ll q;

    line(fl a, fl b, fl c, ll q): a(a), b(b), c(c), q(q) {
        // if (a < 0) { // mega sus
        //     a *= -1;
        //     b *= -1;
        //     c *= -1;
        // }
    }

    v2 norm() const {
        return {a, b};
    }

    v2 point() const { // mega sus
        fl k = c / (a * a + b * b);

        return norm() * k;
    }

    v2 norm_up() const {
        v2 n = norm();

        if (zero(n.x)) {
            n.y = abs(n.y);
            return n;
        }

        if (zero(n.y)) {
            n.x = abs(n.x);
            return n;
        }

        if (n.x < 0) {
            n = n * -1;
        }

        return n;
    }

    bool operator==(const line &o) { // ultra sus
        v2 o_pt = o.point();
        return norm().colin(o.norm()) && zero((point() - o_pt).len());
    }

    bool operator<(const line &o) {
        if (norm().colin(o.norm())) {
            return point().len() + eps < o.point().len(); // sus eps
        } else {
            return norm_up().cross(o.norm_up()) > eps; // sus eps
        }
    }
};

struct eqiv {
    set<line> ls;
    v2 norm;
    ll sum;

    eqiv(line l): ls({l}), norm(l.norm_up()), sum(l.q) {}

    void add(line l) {
        sum += l.q;
        ls.insert(l);
    }

    bool operator<(const eqiv &o) const { // maybe sort by atan2
        return norm.cross(o.norm) > eps; // sus + eps
    }
};

void solve() {
    ll n, sum_all = 0;
    cin >> n;
    
    set<eqiv> es;

    for (ll i = 0; i < n; i++) {
        ll t, a, b, c;
        cin >> t >> a >> b >> c;

        line l1 = line(a, b, c, 0);

        auto found_eq = es.find(eqiv(l1));

        if (t == 1) {
            ll q;
            cin >> q;

            l1.q = q;

            if (found_eq == es.end()) {
                es.insert(eqiv(l1));
                sum_all += q;
            } else {
                auto found_l = found_eq->ls.find(l1);

                auto eq1 = const_cast<eqiv&>(*found_eq);

                if (found_l == found_eq->ls.end()) {
                    eq1.ls.insert(l1);
                    eq1.sum += q;
                } else {
                    line l2 = *found_l;
                }
            }
        }
        
        if (t == 2) {
            if (found_eq == es.end()) {

            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
