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
};


void solve() {
    ll n;
    cin >> n;

    pt3 p1 = pt3::read();
    pt3 p2 = pt3::read();

    cout << p1.dist(p2) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

