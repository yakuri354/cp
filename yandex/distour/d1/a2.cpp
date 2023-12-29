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

const fl eps = 1e-9;

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

    fl ang_x() const {
        return atan2l(cross({1, 0}), dot({1, 0}));
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

    v2 norm_up() const { // super ultra mega sus
        v2 n = norm();

        if (zero(n.x)) {
            n.y = abs(n.y);
            return n;
        }

        if (zero(n.y)) {
            n.x = abs(n.x);
            return n;
        }

        if (n.y < 0) { // x?
            n = n * -1;
        }

        return n;
    }

    bool operator==(const line &o) const { // ultra sus
        // v2 o_pt = o.point();
        // return norm().colin(o.norm()) && zero((point() - o_pt).len());

        return !(*this < o) && !(o < *this);
    }

    bool operator<(const line &o) const {
        if (norm().colin(o.norm())) {
            if (b == 0) {
                return c / a > eps + o.c / o.a;
            }

            return c / b > eps + o.c / o.b;
        } else {
            return norm_up().cross(o.norm_up()) > eps; // sus eps
        }

        // fl ang1 = norm_up().ang_x(), ang2 = o.norm_up().ang_x();

        // if (zero(ang1 - ang2)) {
        //     return 
        // } else {
        //     return ang1 + eps < ang2;
        // }
    }
};

struct eqiv {
    line l;
    ll sum;

    eqiv(line l): l(l), sum(l.q) {}

    bool operator<(const eqiv &o) const { // maybe sort by atan2
        return l.norm_up().cross(o.l.norm_up()) > eps; // sus + eps
    }
};

void solve() {
    ll n, sum_all = 0;
    cin >> n;
    
    set<eqiv> es;
    set<line> lines1;

    for (ll i = 0; i < n; i++) {
        ll t, a, b, c;
        cin >> t >> a >> b >> c;

        line l1 = line(a, b, c, 0);

        auto found_eq = es.find(eqiv(l1));
        auto found_line = lines1.find(l1);

        if (t == 1) {
            ll q;
            cin >> q;

            l1.q = q;

            if (found_line != lines1.end()) {
                line l2 = *found_line;

                lines1.erase(found_line);

                l2.q += l1.q;
                lines1.insert(l2);
            } else {
                lines1.insert(l1);
            }
            
            if (found_eq != es.end()) {
                eqiv e2 = *found_eq;

                es.erase(found_eq);
                e2.sum += q;
                es.insert(e2);
            } else {
                es.insert(eqiv(l1));
            }

            sum_all += q;
        }
        
        if (t == 2) {
            if (found_line != lines1.end()) {
                line l2 = *found_line;

                if (l2.q != 0) {
                    cout << "inf\n";
                    continue;
                }
            }
            
            if (found_eq != es.end()) {
                cout << sum_all - found_eq->sum << '\n';
            } else {
                cout << sum_all << '\n';
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
