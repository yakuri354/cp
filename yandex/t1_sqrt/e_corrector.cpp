// #pragma GCC optimize("Ofast")
#include <ios>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 1e5 + 1;
const ull P = 307;

const ll k = 320;

ull p[maxn], h[maxn];

ull hs(ll l, ll r) {
    ull v = 0;
    if (r > 0) v += h[r-1];
    if (l > 0) v -= h[l-1];

    return v * p[l];
}

struct qr {
    ll l, r, i;
};

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

    ll m;
    cin >> m;

    vector<unordered_set<ull>> q_hashes(n + 1);
    vector<int> qs;

    for (ll i = 0; i < m; i++) {
        string s;
        cin >> s;

        if (s.size() > n) continue;

        ull hq = s[0] * p[n - 1];
        for (ll i = 1; i < s.size(); i++) {
            hq += s[i] * p[n - i - 1];
        }
        q_hashes[s.size()].insert(hq);
        qs.push_back(s.size());
    }
    
    sort(qs.begin(), qs.end());
    qs.erase(unique(qs.begin(), qs.end()), qs.end());
    
    cerr << "szs " << qs.size() << endl;
    cerr << "n " << t.size() << endl;
    
    vector<vector<int>> cnt(qs.size(), vector<int>(n));
    
    for (ll j = 0; j < qs.size(); j++) {
        for (ll i = 0; i < n; i++) {
            if (i + qs[j] > n) break;
            ull hh = hs(i, i + qs[j]);
            if (q_hashes[qs[j]].count(hh)) {
                cnt[j][i] += 1;
            }
        }
        
        ll curr = 0;
        for (ll i = 0; i < n; i++) {
            curr += cnt[j][i];
            cnt[j][i] = curr;
        }
    }
    
    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l--;
        
        ll ans = 0;
        for (ll j = 0; j < qs.size(); j++) {
            if (l + qs[j] > r) break;
            ans += cnt[j][r - qs[j]];
            if (l > 0) ans -= cnt[j][l - 1];
        }
        
        cout << ans << ' ';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
