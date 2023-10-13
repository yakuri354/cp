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

const ll inf = INT32_MAX;

void solve() {

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}


struct segt {
    ll n;
    vector<ll> t;
    
    segt(const vector<ll> &a): n(a.size()), t(n * 2) {
        copy(a.begin(), a.end(), t.begin() + n);
        build();
    }

    segt(ll n): n(n), t(n * 2) {}
    
    ll query(ll l, ll r) {
        ll res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
    
    void set(ll i, ll x) {
        t[i += n] = x;
        for (i >>= 1; i > 0; i >>= 1) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }
private:
    void build() {
        for (ll i = n - 1; i > 0; i--) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }
};

vector<ll> invs(vector<ll> &a) {
    auto b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    
    unordered_map<ll, ll> cmp;
    for (ll i = 0; i < b.size(); i++) {
        cmp[b[i]] = i;
    }
    
    segt t(b.size());
    
    vector<ll> res(a.size());
    for (ll i = 0; i < a.size(); i++) {
        res[i] = t.query(cmp[a[i]] + 1, b.size());
        t.set(cmp[a[i]], t.t[b.size() + cmp[a[i]]] + 1); // sus
    }
    return res;
}