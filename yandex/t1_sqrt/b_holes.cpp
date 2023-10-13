// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

// const ll maxn = 1e5;

const ll inf = INT32_MAX;

// ll a[k][k], next_block[k][k], next_block_last[k][k], next_block_delta[k][k];
vector<vector<ll>> a, next_block, next_block_last, next_block_delta;
ll n, q, k;

void recalc(ll bl) {
    for (ll i = min(k, n - bl * k) - 1; i >= 0; i--) {
        ll next = a[bl][i] + bl * k + i;
        if (next / k > bl || next >= n) {
            next_block[bl][i] = next;
            next_block_last[bl][i] = bl * k + i;
            next_block_delta[bl][i] = 1;
        } else {
            next_block[bl][i] = next_block[bl][a[bl][i] + i];
            next_block_last[bl][i] = next_block_last[bl][a[bl][i] + i];
            next_block_delta[bl][i] = next_block_delta[bl][a[bl][i] + i] + 1;
        }
    }
}

pair<ll, ll> path_len(ll i) {
    ll ans = 0, last = i;
    while (i < n) {
        ans += next_block_delta[i / k][i % k];
        last = next_block_last[i / k][i % k];
        i = next_block[i / k][i % k];
    }
    
    return {ans, last};
}

void solve() {
    cin >> n >> q;
    
    k = 320;

    a.assign(n / k + 1, vector<ll>(k));
    next_block.assign(n / k + 1, vector<ll>(k));
    next_block_last.assign(n / k + 1, vector<ll>(k));
    next_block_delta.assign(n / k + 1, vector<ll>(k));
    
    for (ll i = 0; i < n; i++) {
        cin >> a[i / k][i % k];
    }
    
    for (ll i = 0; i <= n / k; i++) {
        recalc(i);
    }
    
    for (ll i = 0; i < q; i++) {
        ll qt;
        cin >> qt;
        if (qt == 0) {
            ll i, x;
            cin >> i >> x;
            i--;
            a[i / k][i % k] = x;
            recalc(i / k);
        }
        if (qt == 1) {
            ll x;
            cin >> x;

            auto [len, last] = path_len(x - 1);
            cout << last + 1 << ' ' << len << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
