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

vector<ll> a, b;

void calc1(ll i, ll x, vector<vector<ll>> &all, vector<ll> &st) {
    if (x == b[i]) {
        all.push_back(st);
        return;
    }
    
    if (x < b[i]) return;

    for (ll m = 1; m <= x; m++) {
        st.push_back(m);
        calc1(i, x % m, all, st);
        st.pop_back();
    }
}

void solve() {
    ll n;
    cin >> n;

    a.resize(n);
    b.resize(n);
    
    for (ll &i : a) cin >> i;
    for (ll &i : b) cin >> i;
    
    vector<vector<vector<ll>>> zlp(n);
        
    for (ll i = 0; i < n; i++) {
        vector<ll> st;
        calc1(i, a[i], zlp[i], st);
        
        if (zlp[i].empty()) {
            cout << -1 << endl;
            return;
        }
    }

    set<ll> ans;
    
    ull ansv = 0;
    
    vector<bool> del(n);
    
    for (ll m = 50; m > 0; m--) {
        ll all_max = -inf;
        for (ll i = 0; i < n; i++) {
            if (del[i]) continue;
            ll seq_min = inf;
            for (auto &seq : zlp[i]) {
                if (seq.empty()) continue;
                seq_min = min(seq_min, *seq.rbegin());
            }
            
            if (seq_min != inf) all_max = max(all_max, seq_min);
        }
        
        if (all_max == m) {
            ans.insert(m);
            ansv |= 1ull << m;
            
            for (ll i = 0; i < n; i++) {
                if (del[i]) continue;
                for (auto &seq: zlp[i]) {
                    if (!seq.empty() && *seq.rbegin() == m) {
                        seq.pop_back();
                    }
                    
                    if (seq.empty()) {
                        del[i] = true;
                        break;
                    }
                }
            }
        }
        
    }
    
    cout << ansv << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
