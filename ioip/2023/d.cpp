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

struct ent {
    ll w, c, i, ans = 0;
};

void solve() {
    ll n;
    cin >> n;

    vector<ent> a(n);

    for (ll i = 0; i < n; i++) {
        cin >> a[i].c >> a[i].w;
        a[i].i = i;
        a[i].ans = 0;
    }

    sort(a.begin(), a.end(), [](ent a, ent b) {return a.c < b.c;});

    vector<ll> ps(n+1);
    for (ll i = 1; i <= n; i++) {
        ps[i] = ps[i-1] + a[i-1].w;
    }

    vector<ll> xbyy(n);
    for (ll i = 0; i < n; i++) {

    }

    ll x = 0, y = 0;
    for (ll i = 0; i < n; i++) {
        ll want = a[i].c;

        
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

