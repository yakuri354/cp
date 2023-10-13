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

template <typename G>
struct fwk {
    vector<G> t;
    ll n;
    
    fwk(ll n): t(n + 1, G()), n(n + 1) {}
    fwk(vector<G> v): t(v.size() + 1, G()), n(v.size() + 1) {
        for (ll i = 0; i < v.size(); i++) {
            add(i + 1, v[i]);            
        }        
    }
    
    void add(ll i, G x) {
        for (; i <= n; i += i & -i) {
            t[i] += x;
        }
    }
    
    G pref(ll i) {
        G ans{};
        for (; i > 0; i -= i & -i) {
            ans += t[i];            
        }
        return ans;
    }
    
    G sum(ll l, ll r) {
        return pref(r) - pref(l - 1);
    }
};

template <typename G>
struct fwk_r {
    fwk<G> a;
    fwk<G> b;    
    
    fwk_r(ll n): a(n), b(n) {}
    
    void add(ll l, ll r, G x) {
        a.add(l, x);
        a.add(r, -x);
        b.add(l, x * (l - 1));
        b.add(r, -x * r);
    }
    
    G pref(ll i) {
        return a.pref(i) * i - b.pref(i);
    }
    
    G sum(ll l, ll r) {
        return pref(r) - pref(l - 1);
    } 
};

void solve() {

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
