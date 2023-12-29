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
    ll n, m;
    cin >> n >> m;
    
    vector<ll> a(m), b(n);

    for (ll &i: a) cin >> i;
    for (ll &i: b) cin >> i;
    
    vector<ll> ord;
    vector<bool> used(n + 1);
    auto bp = b;

    ll ops = 0;
    for (ll i = 0; i < m; i++) {
        if (used[a[i]]) {
            ord.push_back(a[i]);
            ops++;
        } else {
            for (;;) {
                ll nxt = bp.back();
                ord.push_back(nxt);
                used[nxt] = true;
                bp.pop_back();
                ops++;
                if (nxt == a[i] || bp.empty()) break;
            }
        }
    }
    
    
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
