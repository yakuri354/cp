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
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

using namespace __gnu_pbds;

using oset = tree<ll, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

const ll inf = INT32_MAX;

vector<oset> t;
ll n;

void modify(ll p, ll x) {
    p += n;

    auto el = t[p].find(x);
    ll to_del = el == t[p].end() ? -1 : *el;
    
    for (; p > 0; p >>= 1) {
        if (to_del != -1) t[p].erase(to_del);        
        t[p].insert(x);
    }
}

ll more(oset &v, ll x) {
    return v.size() - v.order_of_key(x);
}

ll query(ll l, ll r, ll ql) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += more(t[l++], ql);
        if (r & 1) res += more(t[--r], ql);
    }
    
    return res;
}

void solve() {
    t.assign(n * 2, {});
    
    for (ll i = 0; i < n; i++) {
        ll p, x;
        cin >> p >> x;

        cout << query(0, p, x + 1) << ' ';
        modify(p - 1, x);
    }
    
    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    while (cin >> n) solve();
}
