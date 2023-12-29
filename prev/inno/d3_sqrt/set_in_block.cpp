// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 1e5;
constexpr ll k = 333;

const ll inf = INT32_MAX;

vector<vector<ll>> a;
vector<ll> offset;
vector<unordered_multiset<ll>> mps;

ll exists(ll l, ll r, ll x) {
    for (ll i = l; i < r;) {
        if (i % k == 0 && i + k <= r) {
            if (mps[i / k].count(x - offset[i / k])) return true;
            i += k;
        } else {
            if (a[i / k][i % k] == x - offset[i / k]) return true;
            i++;
        }
    }
    
    return false;
}

void add(ll l, ll r, ll x) {
    for (ll i = l; i < r;) {
        if (i % k == 0 && i + k <= r) {
            offset[i / k] += x;
            i += k;
        } else {
            ll &val = a[i / k][i % k];
            mps[i / k].erase(mps[i / k].find(val));
            val += x;
            mps[i / k].insert(val);
            i++;
        }
    }
}


void solve() {
    ll n, q;
    cin >> n >> q;
    
    a.resize(k, vector<ll>(k));
    mps.resize(k, {});
    offset.resize(k, 0);

    for (ll i = 0; i < n; i++) {
        cin >> a[i / k][i % k];
    }
    
    for (ll i = 0; i < k; i++) {
        mps[i].insert(a[i].begin(), a[i].end());
    }
    
    for (ll i = 0; i < q; i++) {
        string qt;
        ll l, r, x;
        cin >> qt >> l >> r >> x;
        l--;

        if (qt == "+") {
            add(l, r, x);
        }
        if (qt == "?") {
            cout << (exists(l, r, x) ? "YES" : "NO") << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
