#include <tuple>
#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>
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

    bool operator<(const pt3 &o) const {
        return make_tuple(x, y, z) < make_tuple(o.x, o.y, o.z);
    }

    bool operator==(const pt3 &o) const {
        return make_tuple(x, y, z) == make_tuple(o.x, o.y, o.z);
    }
};

void solve() {
    ll n;
    cin >> n;

    pt3 p1 = pt3::read();
    pt3 p2 = pt3::read();

    ll ans = p1.dist(p2);

    set<pt3> used;

    queue<pair<pt3, ll>> q;
    q.push({p1, 0});

    while (!q.empty()) {
        auto [x, dd] = q.front();
        q.pop();

        if (x == p2) {
            ans = dd;
            break;
        }

        if (used.count(x) == 0) {
            used.insert(x);

            for (ll c1d = -1; c1d <= 1; c1d++) {
                for (ll c2d = -1; c2d <= 1; c2d++) {
                    for (ll c3d = -1; c3d <= 1; c3d++) {
                        pt3 z = {x.x + c1d, x.y + c2d, x.z + c3d};
                        if (z.dist(x) == 1) {
                            
                        }
                    }
                }
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

