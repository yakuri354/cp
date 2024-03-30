#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

namespace pbds {
    using namespace __gnu_pbds;
};

const ull P = 307;

const ll maxl = 2e5;

ull p[maxl];

struct node {
    ull left, right;
    ll ix;
};

ll l, n;

vector<string> s;
vector<node> ns;

void answer(vector<ll> &res) {
    for (ll i = 0; i < n - 1; i++) {
        cout << s[res[i]][0];
    }

    cout << s[res.back()] << '\n';

    exit(0);
}

vector<bool> used;

pbds::gp_hash_table<ull, ll> in_deg, out_deg;
pbds::gp_hash_table<ull, vector<ll>> adj;

vector<ll> stack;
void dfs(ll x) {
    if (used[x]) return;
    used[x] = true;

    stack.push_back(x);

    if (stack.size() == n) {
        answer(stack);
    }

    for (auto x: adj[ns[x].right]) {
        dfs(x);
    }

    stack.pop_back();
}

void solve() {
    string s0;

    p[0] = 1;
    for (ll i = 1; i < maxl; i++) {
        p[i] = p[i-1] * P;
    }


    ll start = 0;

    for (ll i = 0; cin >> s0; i++) {
        s.push_back(s0);
        
        ull hl = s0[0] * p[s0.size() - 2];
        for (ll i = 1; i < s0.size() - 1; i++) {
            hl += s0[i] * p[s0.size() - i - 2];
        }

        ull hr = (hl - (s0[0] * p[s0.size() - 2])) * P + s0.back();

        ns.push_back({hl, hr, i});
        in_deg[hr]++;
        out_deg[hl]++;
        adj[hl].push_back(i);
    }

    n = s.size();
    l = s[0].size();

    if (n == 1) {
        cout << s[0] << endl;
        return;
    }

    // for (ll i = 0; i < n; i++) {
    //     if (in_deg[ns[i].left] == 0) {
    //         start = i;
    //     }
    // }

    // vector<ll> ans = {start};
    // for (ll i = 1; i < n; i++) {
    //     for (auto x: ins[ns[ans.back()].right]) {
    //         if (in_deg[ns[x].right] == 0 && i != n - 1) continue;
    //         ans.push_back(x);
    //         goto nxt;
    //     }

    //     exit(-1);

    //     nxt:;
    // }

    vector<ll> order(n);
    iota(order.begin(), order.end(), 0);

    sort(order.begin(), order.end(), [](ll a, ll b) {
        return in_deg[a] < in_deg[b];
    });

    for (ll i = 0; i < n; i++) {
        used.assign(n, false);
        dfs(order[i]);
    }

    exit(-1);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

