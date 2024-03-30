#pragma GCC optimize("Ofast")
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

struct pt3 {
    ll x, y, z;

    ll dist(const pt3 &o) const {
        ll d = abs(x - o.x) + abs(y - o.y) + abs(z - o.z);
        return d / 2;
    }

    static pt3 read() {
        pt3 p;
        cin >> p.x >> p.y >> p.z;

        return p;
    }

    ll &cc(ll i) {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: exit(-1);
        }
    }

    void print() {
        cout << x << ' ' << y << ' ' << z;
    }
};

void solve() {
    ll n;
    cin >> n;

    pt3 p1 = pt3::read();
    pt3 p2 = pt3::read();

    ll ans = p1.dist(p2);

    for (ll crd = 0; crd < 3; crd++) {
        for (ll sgn = -1; sgn <= 1; sgn += 2) {
            ll c2 = (crd + 1) % 3;
            ll c3 = (crd + 2) % 3;

            for (ll i = 0; i <= n; i++) {
                pt3 p;
                p.cc(crd) = sgn * 3;
                p.cc(c2) = i;
                p.cc(c3) = n - i;

                pt3 z;
                z.cc(crd) = -p.cc(crd);
                z.cc(c2) = i - n;
                z.cc(c3) = -i;

                // p.print();
                // cout << " -> ";
                // z.print();
                // cout << endl;

                ans = min(ans, p.dist(p1) + z.dist(p2));
                ans = min(ans, p.dist(p2) + z.dist(p1));
            }

            swap(c2, c3);

            for (ll i = 0; i <= n; i++) {
                pt3 p;
                p.cc(crd) = sgn * 3;
                p.cc(c2) = i;
                p.cc(c3) = n - i;

                pt3 z;
                z.cc(crd) = -p.cc(crd);
                z.cc(c2) = i - n;
                z.cc(c3) = -i;

                // p.print();
                // cout << " -> ";
                // z.print();
                // cout << endl;

                ans = min(ans, p.dist(p1) + z.dist(p2));
                ans = min(ans, p.dist(p2) + z.dist(p1));
            }
        }
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

