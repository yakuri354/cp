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

const ll inf = 1ll << 50;

vector<ll> t;
ll n;

void modify(ll i, ll v) {
    t[i += n] = v;
    
    for (i /= 2; i > 0; i /= 2) {
        t[i] = min(t[i * 2], t[i * 2 + 1]);
    }
}

ll query(ll l, ll r) {
    ll ans = inf;
    
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ans = min(ans, t[l++]);
        if (r & 1) ans = min(ans, t[--r]);
    }
    
    return ans;
}

vector<ll> d2;
set<ll> calc;
vector<ll> a, b;

vector<bool> used1;

ll fd1(ll i);

ll fd2(ll i) {
    if (i >= n) return 0;

    if (d2[i] != -1) return d2[i];

    if (i + a[i] >= n) return 1;

    auto it = calc.lower_bound(i);

    ll ans = query(i, i + a[i]);

    while (it != calc.end() && *it < i + a[i]) {
        ans = min(ans, fd1(*it));
    }

    return 
}

ll fd1(ll i) {
    if (i >= n) return 0;

    if (t[n + i] != -1) return t[n + i];
    else {
        if (used1[i]) return inf;
        used1[i] = true;
        calc.erase(i);
        modify(i, fd2(i - b[i]));
        used1[i] = false;
        return t[n + i];
    }
}

void solve() {
    cin >> n;

    a.resize(n);
    b.resize(n);
    used1.resize(n, false);

    for (ll i = 0; i < n; i++) {
        calc.insert(i);
        calc.insert(i);
    }

    t.assign(n * 2, -1);
    d2.assign(n, -1);

    for (ll &i: a) cin >> i;
    for (ll &i: b) cin >> i;
    
    ll ans = fd2(0);
    if (ans == -1 || ans >= inf / 2) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
