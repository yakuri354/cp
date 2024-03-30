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

const ll maxn = 1e5 + 1;

vector<ll> adj[maxn];
vector<ll> pos;

vector<ll> ans;

// ll tr = 0;

void solve() {
    ll n, q;
    cin >> n >> q;

    pos.resize(n);

    for (ll i = 0; i < n; i++) {
        ll m;
        cin >> m;

        adj[i].resize(m);
        for (ll &j: adj[i]) {
            cin >> j;
            j--;
        }
    }

    // vector<ll> qs(q);

    // for (ll &i: qs) cin >> i;

    ll v = 0;
    while (ans.size() < 1e6) {
        ans.push_back(v);

        ll nxt = adj[v][pos[v]];
        pos[v] = (pos[v] + 1) % ll(adj[v].size());
        v = nxt;
    }

    for (ll i = 0; i < q; i++) {
        ll t;
        cin >> t;

        cout << ans[t] + 1 << ' ';
    }
    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

