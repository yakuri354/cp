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
const ll maxn = 1e5;

vector<ll> adj[maxn];
ll d[maxn], dv[maxn];
ll ld[maxn], ldv[maxn];
bool used[maxn];

void dfs(ll v, ll p) {
    used[v] = true;
    d[v] = 0;
    ldv[v] = 0;
    
    for (ll u : adj[v]) {
        if (u == p) continue;
        dfs(u, v);
        d[v] += d[u] + dv[u];
        ld[v] += ld[u] + ldv[u];
        dv[v] += dv[u] + 1;
        ldv[v] += ldv[u] + dv[u] + 1;
    }
    
    ll across_subtrees = 0, across_sum = 0;
    
    for (ll u : adj[v]) {
        if (u == p) continue;
        ll other = dv[v] - dv[u] - 1;
        ll curr = dv[u] + 1;
        across_subtrees += other * curr;
        ll curr_sum = ldv[u] + dv[u] + 1; 
        ll other_sum = ldv[v] - curr_sum;
        across_sum += curr * other_sum + other * curr_sum;
    }
    
    d[v] += across_subtrees / 2;
    ld[v] += across_sum / 2;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    ll ans = 0;
    ll ans_sum = 0;
    for (ll i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, -1);
            ans += d[i] + dv[i];
            ans_sum += ld[i] + ldv[i];
        }
    }
    
    cout << ans << '\n' << ans_sum << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
