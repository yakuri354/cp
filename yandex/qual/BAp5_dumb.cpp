// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <ctime>
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
    ll n;
    cin >> n;

    vector<ll> a(n), b(n);
    
    for (ll &i : a) cin >> i;
    for (ll &i : b) cin >> i;
    
    auto t1 = clock();
    
    volatile ll x = 0;

    if (n == 32) {
        // while (fl(clock() - t1) / CLOCKS_PER_SEC < fl(n) * 0.01) x++;
    }
    
    vector<pair<ll, ll>> ms;
    vector<ll> mm(n);
    vector<bool> del(n);
    
    for (ll i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            del[i] = true;
            continue;
        }
        for (ll m = 1; m <= 50; m++) {
            if (a[i] % m == b[i]) {
                ms.emplace_back(m, i);
                mm[i] = m;
                goto next;
            }
        }
        cout << -1 << endl;
        return;
        next:;
    }
    
    sort(ms.begin(), ms.end(), less<>());
    
    ull ansv = 0;
    
    for (auto [m, i] : ms) {
        if (del[i]) continue;
        
        for (ll j = 0; j < n; j++) {
            if (i == j) continue;
            
            if (a[j] % m == b[j]) {
                del[j] = true;
            }
        }

        ansv |= 1ll << mm[i];
    }
    
    cout << ansv << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
