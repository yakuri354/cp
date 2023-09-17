#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>

using namespace std;
using ll = int;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5 + 1;
const ll k = 500;

vector<vector<ll>> adj;
vector<vector<ll>> adj_heavy;
vector<ll> ver;
vector<unordered_map<ll, ll>> heavy;
ll n, m;
ll state = 0;

void solve() {
    cin >> n >> m;
    
    adj.resize(n);
    ver.resize(n);
    heavy.resize(n);
    adj_heavy.resize(n);

    for (ll i = 0; i < n; i++) cin >> ver[i];
    
    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (ll i = 0; i < n; i++) {
        for (ll u : adj[i]) {
            if (adj[i].size() > k) {
                heavy[i][ver[u]]++;
            }
            if (adj[u].size() > k) {
                adj_heavy[i].push_back(u);
            }
            if (ver[u] != ver[i]) {
                state++;
            }
        } 
    }
    
    state /= 2;
    
    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++) {
        ll c, v;
        cin >> c >> v;
        c--;

        for (ll u : adj_heavy[c]) {
            heavy[u][ver[c]]--;
            heavy[u][v]++;
        }
        
        if (adj[c].size() > k) {
            state += heavy[c][ver[c]];
            state -= heavy[c][v];
        } else {
            for (ll u : adj[c]) {
                if (ver[u] == ver[c]) state++;                
                if (ver[u] == v) state--;
            }
        }
        
        ver[c] = v;
        cout << state << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
