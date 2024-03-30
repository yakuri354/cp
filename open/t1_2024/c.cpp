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

struct ectr {
    unordered_map<ll, ll> m;

    void add(ll x) {
        m[x]++;
    }

    void rm(ll x) {
        m[x]--;
        if (m[x] == 0) m.erase(x);
    }

    ll cnt() {
        return m.size();
    }

    bool has(ll x) {
        return m.count(x);
    }
};

ll n, k, t;
vector<ll> a;

ll cdiff() {
    unordered_map<ll, ll> m;
    for (ll i: a) m[i]++;
    return m.size();
}

pair<vector<ll>, vector<ll>> calc0() {
    ectr ctr;
    vector<ll> nxt(n), cnt(n);
    ll l = 0, r = 0;

    while (l < n) {
        while (ctr.cnt() < t) {
            ctr.add(a[r]);
            r++;
        }
        while (ctr.has(a[r])) ctr.add(a[r]), r++;
        while (ctr.cnt() == t && l < n) {
            nxt[l] = r % n;
            cnt[l] = r - l;
            ctr.rm(a[l]);
            l++;
        }
    }

    return {nxt, cnt};
}

void solve() {
    cin >> n >> k >> t;

    a.resize(n);
    for (ll &i: a) cin >> i;

    a.resize(n * 2);
    copy(a.begin(), a.begin() + n, a.begin() + n);

    if (cdiff() <= t) {
        cout << 1 << endl;
        return;
    }

    auto [nxt, jsz] = calc0();


    ll i = 0, left = n * k, ans = 0;
    unordered_map<ll, ll> dist, res;
    while (left > 0 && dist.count(i) == 0) {
        dist[i] = left;
        res[i] = ans;
        left -= jsz[i];
        i = nxt[i];
        ans++;
    }

    if (left <= 0) {
        cout << ans << endl;
        return;
    }

    ll cycle_len = dist[i] - left, cycle_sz = ans - res[i];
    
    ans += (left / cycle_len) * cycle_sz;
    left %= cycle_len;

    while (left > 0) {
        left -= jsz[i];
        i = nxt[i];
        ans++;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

