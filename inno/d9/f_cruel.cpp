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

ll fmex(vector<ll>& m, ll t) {
    ll res = inf;
    for (ll x = 0; x <= m.size(); x++) {
        if (m[x] == t) continue;
        res = x;
        break;
    }
    if (res == inf) exit(-1);
    return res;
}

void solve() {
    ll n;
    cin >> n;
    
    vector<ll> d(n + 1);
    d[0] = 0;
    d[1] = 0;
    
    vector<ll> mex(n + 1, -1);
    ll t = 0;
    
    for (ll i = 2; i <= n; i++) {
        t++;
        
        for (ll j = 0; j < i; j++) {
            mex[d[j] ^ d[i - j - 1]] = t;
        }
        
        d[i] = fmex(mex, t);
    }
    
    cout << endl;
    for (ll j = 0; j <= n; j++) {
        cout << d[j] << ' ';
    }
    cout << endl << endl;
    
    vector<ll> win_pos;
    
    for (ll j = 0; j < n; j++) {
        if ((d[j] ^ d[n - j - 1]) == 0) {
            win_pos.push_back(j + 1);
        }
    }

    if (!win_pos.size()) {
        cout << "Mueller" << endl;
        return;
    }

    cout << "Schtirlitz\n";
    
    for (ll x : win_pos) {
        cout << x << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
