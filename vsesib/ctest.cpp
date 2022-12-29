// #pragma GCC optimize("Ofast")
#include <random>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct ent {
    ll v, c, i;

    bool operator<(const ent &other) {
        return this->v < other.v;
    }
};

struct bs {
    ll len, cs;
};

ent a[5000];

void solve() {
    ll n;
    cin >> n;

    map<pair<fl, ll>, bs> seq;
    vector<map<fl, ll>> par(n);
    random_device rd;
    mt19937_64 mt(rd());
    uniform_int_distribution<ll> dist(1, 1e18);
    uniform_int_distribution<ll> dist2(1, 1e6);

    for (ll i = 0; i < n; i++) {
        a[i].v = dist(mt);
        a[i].i = i;
    }

    for (ll i = 0; i < n; i++) {
        a[i].c = dist2(mt);
    }

    sort(a, a + n);

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < i; j++) {
            pair<fl, ll> ip{fl(a[i].v)/fl(a[j].v), j};
            if (seq.count(ip)) {
                auto pl = seq[ip];
                seq.erase(ip);
                seq[{ip.first, i}] = {pl.len + 1, pl.cs + a[i].c};
                par[i][ip.first] = j;
            } else {
                seq[{ip.first, i}] = {2, a[i].c + a[j].c};
                par[i][ip.first] = j;
                par[j][ip.first] = -1;
            }
        }
    }

    ll last = -1, len = -1, sum = inf;
    fl coeff = -1;
    for (auto [k, v] : seq) {
        if (v.len > len || (v.len == len && v.cs <= sum)) {
            len = v.len;
            last = k.second;
            coeff = k.first;
            sum = v.cs;
        }
    }

    vector<ll> ans;
    ll its = 0;

    while (last != -1) {
        if (its > n * n * 10) assert(0);
        ans.push_back(a[last].i);
        last = par[last][coeff];
        its++;
    }

    cout << ans.size() << ' ' << sum << endl;
    
    reverse(ans.begin(), ans.end());
    for (ll i : ans) {
        cout << i + 1 << ' ';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
