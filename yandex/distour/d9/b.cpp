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

const ll maxn = 3e5;

vector<ll> g[maxn];
vector<ll> term[maxn];
vector<pair<ll, ll>> qs;

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < n - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    qs.resize(m);

    for (auto &[a, b]: qs) {
        cin >> a >> b;
        a--, b--;

        term[a].push_back(b);
        term[b].push_back(a);
    }

    
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

