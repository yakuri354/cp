// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;
using ll = long long;
using ull = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e6;
const ull P = 307;

ull p[maxn], h[maxn];

ull hs(ll l, ll r) {
    ull v = 0;
    if (r > 0) v += h[r-1];
    if (l > 0) v -= h[l-1];

    return v * p[l];
}

void solve() {
    string t;
    cin >> t;
    ll n = t.size();

    p[0] = 1;
    for (ll i = 1; i < n; i++) {
        p[i] = p[i-1] * P;
    }

    h[0] = t[0] * p[n - 1];
    for (ll i = 1; i < n; i++) {
        h[i] = h[i-1] + t[i] * p[n - i - 1];
    }

    ll q;
    cin >> q;

    unordered_map<ull, ll> q_hashes;
    vector<bool> q_ans(q);

    for (ll i = 0; i < q; i++) {
        string s;
        cin >> s;

        if (s.size() > n) continue;

        ull hq = s[0] * p[n - 1];
        for (ll i = 1; i < s.size(); i++) {
            hq += s[i] * p[n - i - 1];
        }
        q_hashes[hq] = i;
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 1; j <= 30 && i + j <= n; j++) {
            ull hh = hs(i, i + j);
            if (q_hashes.count(hh)) {
                q_ans[q_hashes[hh]] = true;
                q_hashes.erase(hh); // ??
            }
        }
    }

    for (auto x : q_ans) {
        if (x) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
