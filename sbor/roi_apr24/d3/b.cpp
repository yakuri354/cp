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

struct rect {
    ll l1, l2, r1, r2;
    
    auto to_tup() const {
        return make_tuple(l1, l2, r1, r2);
    }

    bool operator<(const rect &o) const {
        return to_tup() < o.to_tup();
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<ll> a(m);
    for (ll &i: a) cin >> i;

    string s;
    cin >> s;

    vector<ll> lst(m, 0);

    vector<array<ll, 30>> nxt(n+1);
    for (ll i = 0; i < n; i++) nxt[i].fill(-1);

    vector<array<ll, 30>> jmp(n+1);
    for (ll i = 0; i < n; i++) jmp[i].fill(-1);

    vector<rect> rs;

    for (ll i = 0; i < n; i++) {
        nxt[lst[a[i]-'a']][a[i]-'a'] = i+1;
        lst[a[i] - 'a'] = i+1;
    }

    for (ll let = 0; let < m; let++) {
        if (nxt[0][let] == -1) continue;

        ll curr = 1;
        ll l0 = 0;
        ll l = nxt[0][let], r = nxt[0][let];
        while (curr < a[let] && r != -1 && nxt[r][let] != -1) curr++, r = nxt[r][let];
        if (curr < a[let]) continue;
        
        rs.push_back({l0 + 1, l, r, nxt[0]})
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

