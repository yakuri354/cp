// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 2e5;

vector<int> g[maxn];
int s[maxn], p[maxn], tin[maxn], tout[maxn];
int head[maxn];
int t = 0;

void sizes(int v = 0) {
    s[v] = 1;
    for (int &u : g[v]) {
        sizes(u);
        s[v] += s[u];
        if (s[u] > s[g[v][0]])
            swap(u, g[v][0]);
    }
}

void hld(int v = 0) {
    tin[v] = t++;
    for (int u : g[v]) {
        head[u] = (u == g[v][0] ? head[v] : u);
        hld(u);
    }
    tout[v] = t;
}

void solve() {
    
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
