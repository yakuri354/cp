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
const ll maxn = 1e5;

ll n, m, v, p;

ll a[maxn];

bool check(ll x) {
    if (a[x] >= a[p-1]) return true;
    if (m < a[p - 1] - a[x]) return false;
    if (v < p + n - x - 1) return true;

    // while (x < n - 1 && a[x] == a[x+1]) x++;

    ll eps = 0;
    for (ll i = p - 1; i <= x; i++) {
        eps += a[i] - a[x];
    }

    ll c = n - v;
    return eps <= c * m;
}

void solve() {
    cin >> n >> m >> v >> p;
    
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a, a + n, greater<>());
    
    check(4);
    
    ll lo = 0, hi = n;
    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;

        if (check(m)) lo = m;
        else hi = m;
    }
    
    cout << hi << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
