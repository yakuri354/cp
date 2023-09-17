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
const ll maxn = 1;

vector<ll> adj[maxn];
ll d[maxn], dv[maxn];
ll ld[maxn], ldv[maxn];
bool used[maxn];

ll st[maxn * 2];
ll n;

ll tin[maxn], tout[maxn];
ll t = 0;

void add_seg(ll l, ll r, ll x) {
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) st[l++] += x;
        if (r & 1) st[--r] += x;
    }
}

ll get_point(ll i) {
    ll ans = 0;
    for (i += n; i > 0; i >>= 1) {
        ans += st[i];
    }
    return ans;
}

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
        
        add_seg(tin[u], tout[u] + 1, other_sum);
    }
    
    d[v] += across_subtrees / 2;
    ld[v] += across_sum / 2;
}

void dfs_euler(ll v, ll p) {
    tin[v] = t++;
    st[n + t] = v;
    for (ll u : adj[v]) {
        if (u == p) continue;
        dfs_euler(u, v);
    }
    tout[v] = t;
}

void solve() {
    ll m;
    cin >> n >> m;

    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs_euler(0, -1);
    
    dfs(0, -1);
    
    
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
