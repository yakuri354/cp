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

const ll maxn = 101;

vector<ll> g[maxn];

ll mt[maxn], used[maxn];

struct evt {
    ll t, x, y;
};

ll n, speed;

bool dfs_kuhn(ll v, ll it) {
    if (used[v] == it) return false;
    used[v] = it;

    for (ll u: g[v]) {
        if (used[u] == it) continue;
        if (mt[u] == -1 || dfs_kuhn(mt[u], it)) {
            mt[u] = v;
            return true;
        }
    }

    return false;
}

ll kuhn() {
    ll it = 1;

    for (ll i = 0; i < n; i++) {
        mt[i] = -1;
    }

    for (ll i = 0; i < n; i++) {
        if (dfs_kuhn(i, it)) it++;
    }

    return it - 1;
}

void solve() {

    cin >> n >> speed;

    vector<evt> evs;

    for (ll i = 0; i < n; i++) {
        string ts;
        ll x, y;
        cin >> ts >> x >> y;

        ll t = stoll(ts.substr(0, 2)) * 60 + stoll(ts.substr(3, 2));

        evs.push_back({t, x, y});
    }
    
    sort(evs.begin(), evs.end(), [](evt a, evt b) {
        return a.t < b.t;
    });

    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j < n; j++) {
            if (hypotl(evs[i].x - evs[j].x, evs[i].y - evs[j].y) <= (fl(speed) / 60) * fl(evs[j].t - evs[i].t)) {
                g[i].push_back(j);
            }
        }
    }

    ll match = kuhn();

    cout << n - match << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

