// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct op {
    ll from, to;
    bool succ;
};

op arr[100000];

unordered_map<ll, vector<ll>> g;
unordered_map<ll, ll> last_v;
unordered_map<ll, ll> in_deg;

multimap<pair<ll, ll>, ll> rev;

vector<ll> ans;
ll fc = 0;

void euler(ll v) {
    for (; last_v[v] < g[v].size(); last_v[v]++) {
        euler(g[v][last_v[v]]);
        fc++;
    }
    ans.push_back(v);
}

void solve() {
    ll n, x0;
    cin >> n >> x0;

    ll sc = 0;

    multimap<ll, ll> to_del;

    for (ll i = 0; i < n; i++) {
        cin >> arr[i].from >> arr[i].to >> arr[i].succ;
        if (arr[i].succ) {
            rev.insert({{arr[i].from, arr[i].to}, i});
            g[arr[i].from].push_back(arr[i].to);
            sc++;
        } else {
            to_del.insert({arr[i].from, i});
        }
    }

    ll cnt = 0;
    for (auto &v: g) {
        if (abs(ll(v.second.size()) - in_deg[v.first]) > 1) {
            cout << "No" << endl;
            return;
        }
        if (v.second.size() != in_deg[v.first]) {
            cnt++;
            if (cnt > 2) {
                cout << "No" << endl;
                return;
            }
        }
    }

    euler(x0);

    reverse(ans.begin(), ans.end());

    if (sc != fc) {
        cout << "No" << endl;
        return;
    }

    set<ll> checked;

    vector<ll> final;

    for (ll i = 0; i < ans.size() - 1; i++) {
        if (!to_del.empty() && checked.count(ans[i]) == 0) {
            set<ll> gg;
            for (auto x : to_del) {
                if (x.first != ans[i]) {
                    final.push_back(x.second + 1);
                    gg.insert(x.first);
                }
            }
            for (auto x : gg) {
                to_del.erase(x);
            }
            checked.insert(ans[i]);
        }
        auto range = rev.equal_range({ans[i], ans[i+1]});

        for (auto i = range.first; i != range.second; i++) {
            final.push_back(i->second + 1);
        }
    }

    if (final.size() != n || !to_del.empty()) {
        cout << "No" << endl;
        return;
    }

    cout << "Yes" << '\n';

    for (ll i : final) {
        cout << i << ' ';
   }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
