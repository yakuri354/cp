// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <functional>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <map>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

struct ff {
    ll x[3];
};

using ms = set<pair<ll, ll>, greater<>>;

ll ans = 0;
vector<ff> f;

void del(ms &s, pair<ll, ll> x) {
    s.erase(s.find(x));
}

ms s[3][3];

void take(ll ix, ll from) {
    for (ll to = 0; to < 3; to++) {
        if (to == from) continue;
        del(s[from][to], {f[ix].x[to] - f[ix].x[from], ix});
    }
}

void put(ll ix, ll to) {
    for (ll next = 0; next < 3; next++) {
        if (to == next) continue;
        s[to][next].emplace(f[ix].x[next] - f[ix].x[to], ix);
    }
}

bool s_swap(ll a, ll b) {
    auto a_b_m = *s[a][b].begin(), b_a_m = *s[b][a].begin();
    ll sum = a_b_m.first + b_a_m.first;

    if (sum > 0) {
        take(a_b_m.second, a);
        take(b_a_m.second, b);

        put(a_b_m.second, b);
        put(b_a_m.second, a);

        ans += sum;
        return true;
    }
    return false;
}

bool s_cycle(ll a, ll b, ll c) {
    auto a_b_m = *s[a][b].begin(), b_c_m = *s[b][c].begin(), c_a_m = *s[c][a].begin();
    ll sum = a_b_m.first + b_c_m.first + c_a_m.first;
    
    if (sum > 0) {
        ll ab = a_b_m.second;
        take(ab, a);
        put(ab, b);

        ll bc = b_c_m.second;
        take(bc, b);
        put(bc, c);

        ll ca = c_a_m.second;
        take(ca, c);
        put(ca, a);

        ans += sum;
        return true;
    }
    return false;
}

void solve() {
    ll x, y, z;
    cin >> x >> y >> z;
    ll n = x + y + z;
    
    f.resize(n);

    for (ff &z: f) {
        cin >> z.x[0] >> z.x[1] >> z.x[2];
    }
    
    {
        ll i = 0;
        for (; i < x; i++) {
            ans += f[i].x[0];
            put(i, 0);
        }

        for (; i < x + y; i++) {
            ans += f[i].x[1];
            put(i, 1);
        }

        for (; i < x + y + z; i++) {
            ans += f[i].x[2];
            put(i, 2);
        }
    }
    
    while (    s_swap(0, 1)
            || s_swap(0, 2)
            || s_swap(1, 2)

            || s_cycle(0, 1, 2)
            || s_cycle(2, 1, 0)
    ) continue;
    
    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
