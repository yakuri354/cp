// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <queue>
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

struct edge {
    ll v, cnt;
};

void solve() {
    ll n;
    cin >> n;

    vector<ll> deg_in(n), cnt(n), curr_in(n);
    vector<vector<edge>> g(n);
    unordered_map<string, ll> names;
    vector<string> inv_n(n);

    ll maxi = 0;
    for (ll i = 0; i < n; i++) {
        string n1;
        ll m;
        cin >> n1 >> m;

        if (!names.count(n1)) {
            names[n1] = maxi;
            inv_n[maxi] = n1;
            maxi++;
        }

        for (ll j = 0; j < m; j++) {
            string n2;
            ll c;
            cin >> n2 >> c;

            if (!names.count(n2)) {
                names[n2] = maxi;
                inv_n[maxi] = n2;
                maxi++;
            }

            g[names[n1]].push_back({names[n2], c});
            deg_in[names[n2]]++;
        }
    }

    string r;
    cin >> r;

    queue<ll> q;
    q.push(names[r]);
    cnt[names[r]] = 1;

    while (!q.empty()) {
        ll v = q.front();
        q.pop();

        // cerr << "in " << inv_n[v] << endl;

        for (edge e: g[v]) {
            cnt[e.v] += cnt[v] * e.cnt;
            curr_in[e.v]++;

            if (curr_in[e.v] == deg_in[e.v]) {
                // cerr << "pushing " << inv_n[e.v] << " from " << inv_n[v] << endl;
                q.push(e.v);
            }
        }
    }

    for (ll i = 0; i < n; i++) {
        if (g[i].size() == 0) {
            cout << inv_n[i] << ' ' << cnt[i] << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

