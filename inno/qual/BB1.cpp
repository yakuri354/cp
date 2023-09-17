// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n, k;
    cin >> n >> k;

    unordered_map<string, ll> cnt;

    for (ll i = 0; i < n; i++) {
        string x;
        cin >> x;
        cnt[x]++;
    }

    ll q;
    cin >> q;

    while (q--) {
        string h;
        cin >> h;

        unordered_set<string> ss;
        for (ll i = 0; i < h.length(); i++) {
            string h_prime = h;
            h_prime.erase(i, 1);
            ss.insert(h_prime);
        }

        ll ans = 0;
        for (string x : ss) {
            ans += cnt[x]; 
        }

        cout << ans << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
