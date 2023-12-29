// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

ll mom[maxn];
ll sum[maxn];
ll sz[maxn];
ll qa[maxn];
ll perm[maxn];
bool state[maxn];

ll ldr(ll v) {
    return mom[v] == v ? v : mom[v] = ldr(mom[v]);
}

void unite(ll a, ll b) {
    a = ldr(a), b = ldr(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    sum[a] += sum[b];
    mom[b] = a;
}

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> sum[i];
        mom[i] = i;
        sz[i] = 1;
    }

    for (ll i = 0; i < n; i++) {
        cin >> perm[i];
        perm[i]--;
    }

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        qa[n-1-i] = ans;
        ll freed = perm[n-i-1];
        if (freed < n -1 && state[freed+1]) unite(freed, freed+1);
        if (freed > 0 && state[freed-1]) unite(freed, freed-1);
        ans = max(ans, sum[ldr(freed)]);
        state[freed] = true;
    }

    for (ll i = 0; i < n; i++) {
        cout << qa[i] << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
