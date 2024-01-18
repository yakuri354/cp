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

const ll maxn = 2e5;

vector<ll> ga[maxn], gb[maxn];
ll ca[maxn], cb[maxn];

void dfs_a(ll v, ll c) {
    if (ca[v] != -1) return;
    ca[v] = c;

    for (ll u: ga[v]) {
        dfs_a(u, c);
    }
}

void dfs_b(ll v, ll c) {
    if (cb[v] != -1) return;
    cb[v] = c;

    for (ll u: gb[v]) {
        dfs_b(u, c);
    }
}

void solve() {
    ll n, m1, m2;
    cin >> n >> m1 >> m2;

    for (ll i = 0; i < n; i++) {
        ca[i] = cb[i] = -1;
    }

    for (ll i = 0; i < m1; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        ga[a].push_back(b);
        ga[b].push_back(a);
    }

    for (ll i = 0; i < m2; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        gb[a].push_back(b);
        gb[b].push_back(a);
    }

    ll comps_a = 0, comps_b = 0;
    for (ll i = 0; i < n; i++) {
        if (ca[i] == -1) dfs_a(i, comps_a++);
        if (cb[i] == -1) dfs_b(i, comps_b++);
    }

    unordered_map<ll, ll> cnt;

    for (ll i = 0; i < n; i++) {
        cnt[ca[i] * ll(1e9) + cb[i]]++;
    }

    for (ll i = 0; i < n; i++) {
        cout << cnt[ca[i] * ll(1e9) + cb[i]] << ' ';
    }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

