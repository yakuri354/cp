// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll grundy[] = {0, 1, 2, 1, 4, 3, 2, 1, 5, 6,  2, 1, 8, 7,  5,
                     9, 8, 7, 3, 4, 7, 4, 2, 1, 10, 9, 3, 6, 11, 12};

ll calc(ll n) {
    ll ans = 1;
    ll count = 1;
    
    unordered_set<ll> pws;

    for (ll i = 2; i * i <= n; i++) {
        if (pws.count(i)) continue;
        ll cnt = 0;
        for (ll j = i; j <= n; j *= i) {
            pws.insert(j);
            cnt++;
        }
        ans ^= grundy[cnt];                
        count += cnt;
    }
    
    ans ^= (n - count) & 1;

    return ans;
}

void solve() {
    ll n;
    cin >> n;

    if (calc(n) != 0) {
        cout << "Vanya" << endl;
    } else {
        cout << "Sasha" << endl;
    }
    
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
