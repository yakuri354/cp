#include <utility>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_set>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5 + 1;
// const ll k = 550;

vector<vector<ll>> g;
vector<pair<ll, ll>> el;
vector<bool> heavy;
ll n, m;
ll state = 0;

ll all_light = 0;

void solve() {
    cin >> n >> m;
    
    g.resize(n);
    heavy.resize(n);

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        
        el.emplace_back(u, v);
    }
    
    vector<ll> zlp(n);
    
    for (ll i = 0; i < n; i++) {
        zlp[i] = i;
        sort(g[i].begin(), g[i].end(), [](ll a, ll b) {
            return make_pair(g[a].size(), a) < make_pair(g[b].size(), b);
        });
    }
    
    sort(zlp.begin(), zlp.end(), [](ll a, ll b) {
        return make_pair(g[a].size(), a) < make_pair(g[b].size(), b);
    });
    
    vector<ll> pos(n);
    
    for (ll i = 0; i < n; i++) {
        pos[zlp[i]] = i;
    }
    
    ll ans = 0;
    
    vector<ll> vis(n, 0);
    
    for (ll i : zlp) {
        for (ll v : g[i]) {
            vis[v]++;
        }
        
        for (ll v : g[i]) {
            if (pos[v] > pos[i]) break;
            
            for (ll u : g[v]) {
                if (pos[u] > pos[v]) break;
                
                ans += vis[u];
            }
        }

        for (ll v : g[i]) {
            vis[v]--;
        }
    }
    
    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
