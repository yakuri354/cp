// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;
const ll p = 1e6 + 3;

ll ldr[maxn];
vector<ll> lst[maxn];
ll stmsg[maxn];
ll elmsg[maxn];

void unite(ll a, ll b) {
    a = ldr[a], b = ldr[b];
    if (a == b) return;
    if (lst[a].size() < lst[b].size()) swap(a, b);
    // eta linia pochemuto tlitsa
    // lst[a].reserve(lst[a].size() + lst[b].size());
    for (ll el : lst[b]) {
        elmsg[el] -= stmsg[a];
        elmsg[el] += stmsg[b];
        ldr[el] = a;
        lst[a].push_back(el);
    }
    lst[b].clear();
    stmsg[b] = 0;
}

void solve() {
    ll n, m, zerg = 0;
    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        ldr[i] = i;
        lst[i] = {i};
    }

    for (ll i = 0; i < m; i++) {
        ll t;
        cin >> t;

        if (t == 1) {
            ll i;
            cin >> i;

            i = (i + zerg) % n;
            // cerr << "t 1 i " << i << endl;

            stmsg[ldr[i]] += 1;

            zerg = (30 * zerg + 239) % p;
        }
        if (t == 2) {
            ll i, j;
            cin >> i >> j;
            i = (i + zerg) % n;
            j = (j + zerg) % n;

            // cerr << "t 2 i " << i << " j " << j << endl;

            if (ldr[i] == ldr[j]) continue;
            unite(i, j);
            zerg = (13 * zerg + 11) % p;
        }
        if (t == 3) {
            ll i;
            cin >> i;
            i = (i + zerg) % n;
            ll q = stmsg[ldr[i]] + elmsg[i];
            elmsg[i] = -stmsg[ldr[i]];
            zerg = (100500 * zerg + q) % p;
            cout << q << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
