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
using ll = __int128;
using li = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

ll mod(ll x) {
    return x % ll(1e9 + 7);
}

struct ent {
    ll w, h;
};

ll solvedumb(vector<ent> &a) {
    li n = a.size();
    ll ans = 0;

    for (ll i = 0; i < n; i++) {
        ans = mod(ans + mod((a[i].h * (a[i].h + 1)) / 2) * mod(a[i].w * (a[i].w + 1) / 2));

        ll y = a[i].h;
        for (ll j = i - 1; j >= 0; j--) {
            y = min(y, a[j].h);
            ans = mod(ans + mod(a[i].w * a[j].w) * mod(y * (y + 1) / 2));
        }
    }

    return ans;
}

void solve() {
    li _n;
    cin >> _n;
    ll n = _n;

    vector<ent> a(n);
    for (auto &[w, h]: a) {
        li _h;
        cin >> _h;
        h = _h;
    }
    for (auto &[w, h]: a) {
        li _w;
        cin >> _w;
        w = _w;
    }

    a.push_back({0, 0});

    vector<pll> st = {{0, 0}};
    ll x = 0;
    ll ans = 0;
    for (ll i = 0; i <= n; i++) {
        ll lx = x;
        while (st.back().first > a[i].h) {
            ll dx = x - st.back().second;
            lx = min(lx, st.back().second);
            ll ly = max(st[st.size() - 2].first, a[i].h);
            ll dy = st.back().first - ly;
            ans = mod(ans + mod(mod(dy * ly) + (dy * (dy + 1)) / 2) * mod((dx * (dx + 1)) / 2));
            st.pop_back();
        }

        if (st.back().first < a[i].h) {
            st.emplace_back(a[i].h, lx);
        }

        x += a[i].w;
    }

    // a.pop_back();
    // if (ans != solvedumb(a)) {
    //     cout << "GOVNO" << endl;
    //     cout << li(ans) << endl;
    //     cout << li(solvedumb(a)) << endl;
    // }

    cout << li(mod(ans)) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

