// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstdint>
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

const ll inf = INT64_MAX / 2;

struct rect {
    ll w, h;
    
    pair<ll, ll> to_pair() const {
        return {w, h};
    }
    
    bool operator<(const rect &other) const {
        return to_pair() < other.to_pair();
    }
};

struct line {
    ll k, b;
    
    line(): k(0), b(inf) {}
    line(ll k, ll b): k(k), b(b) {}
    
    ll operator()(ll x) const {
        return k * x + b;
    }
};

struct li_chao2 {
    ll lb, rb;
    
    li_chao2(ll lb, ll rb): lb(lb), rb(rb) {}
    
    unordered_map<ll, line> t;
    
    void _add(line f, ll i, ll l, ll r) {
        if (!t.count(i)) {
            t[i] = f;
            return;
        }

        ll m = (l + r) / 2;

        ll lv = f(l) < t[i](l);
        ll mv = f(m) < t[i](m);
        
        if (mv) swap(f, t[i]);
        
        if (r - l <= 1) return;
        else if (lv != mv) _add(f, i * 2 + 1, l, m);
        else _add(f, i * 2 + 2, m, r);
    }
    
    void add(line f) {
        _add(f, 0, lb, rb);
    }
    
    ll _min_y(ll x, ll i, ll l, ll r) {
        if (!t.count(i)) {
            return inf;
        }

        ll m = (l + r) / 2;

        if (r - l <= 1) return t[i](x);
        
        if (x < m) return min(t[i](x), _min_y(x, i * 2 + 1, l, m));
        else return min(t[i](x), _min_y(x, i * 2 + 2, m, r));
    }
    
    ll min_y(ll x) {
        return _min_y(x, 0, lb, rb);
    }
};

vector<rect> a1, a;

void solve() {
    ll n1;
    
    cin >> n1;
    
    a1.resize(n1);

    for (auto &[w, h] : a1) {
        cin >> w >> h;
    }
    
    sort(a1.begin(), a1.end());

    for (auto [w, h]: a1) {
        while (!a.empty() && a.back().h <= h) a.pop_back();
        a.push_back({w, h});
    }
    
    ll n = a.size();

    vector<ll> d(n + 1);
    
    li_chao2 c(0, 1e6+1);
    
    c.add({a[0].h, 0});

    for (ll i = 1; i <= n; i++) {
        d[i] = c.min_y(a[i-1].w);
        if (i < n) c.add({a[i].h, d[i]});
    }
    
    cout << d[n] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}