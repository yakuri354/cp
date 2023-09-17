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

    for (ll m = 1; m < x; m++) {
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
        vector<vector<ll>> z1;
        vector<ll> st;
        calc1(i, a[i], z1, st);
        
        if (z1.empty()) {
            cout << -1 << endl;
            return;
        }

        zlp[i] = std::move(z1);
    }

    set<ll> ans;
    
    ull ansv = 0;
    
    for (ll m = 50; m > 0; m--) {
        bool add = false;
        for (ll i = 0; i < n; i++) {
            bool can = false;
            if (zlp[i].empty()) exit(-1);
            for (auto &seq: zlp[i]) {
                if (find(seq.begin(), seq.end(), m) == seq.end()) {
                    can = true;
                    break;
                }
            }
            if (!can) {
                ans.insert(m);
                ansv |= 1ull << m;
                add = true;
                break;
            } 
        }
        
        if (add) continue;
        
        for (auto &ss: zlp) {
            for (auto it = ss.begin(); it != ss.end();) {
                if (find(it->begin(), it->end(), m) != it->end()) {
                    it = ss.erase(it);
                } else {
                    it++;
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
