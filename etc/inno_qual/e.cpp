// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

vector<ll> p;
vector<deque<ll>> tree;

ll count(ll x) {
    ll ans = 0;
    while (p[x] != x) {
        ll pos =
            find(tree[p[x]].begin(), tree[p[x]].end(), x) - tree[p[x]].begin();
        ans += min(pos, ll(tree[p[x]].size() - pos - 1)) + 1;
        x = p[x];
    }
    return ans;
}

struct qr {
    string ty;
    ll x, to;
};

vector<ll> d;
void dp(ll v, ll h) {
    d[v] = h;
    for (ll i = 0; i < tree[v].size(); i++) {
        dp(tree[v][i], h + min(i, ll(tree[v].size() - i - 1)) + 1);
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;

    p.resize(n);
    d.resize(n);
    tree.resize(n);
    iota(p.begin(), p.end(), 0);

    vector<qr> qs;

    for (ll i = 0; i < m; i++) {
        string ty;
        cin >> ty;

        if (ty == "push_back") {
            ll x, to;
            cin >> x >> to;
            x--, to--;

            qs.push_back({ty, x, to});
        }

        if (ty == "push_front") {
            ll x, to;
            cin >> x >> to;
            x--, to--;

            qs.push_back({ty, x, to});
        }

        if (ty == "pop_back") {
            ll x;
            cin >> x;
            x--;

            qs.push_back({ty, x});
        }

        if (ty == "pop_front") {
            ll x;
            cin >> x;
            x--;

            qs.push_back({ty, x});
        }

        if (ty == "pop_complexity") {
            ll x;
            cin >> x;
            x--;

            qs.push_back({ty, x});
        }
    }

    bool precalc = false;
    if (qs.end() - find_if(qs.begin(), qs.end(),
                           [](qr q) { return q.ty == "pop_complexity"; }) ==
        count_if(qs.begin(), qs.end(),
                 [](qr q) { return q.ty == "pop_complexity"; })) {

        precalc = true;
    }

    bool calced = false;

    for (ll i = 0; i < m; i++) {
        auto q = qs[i];

        if (q.ty == "push_back") {
            p[q.x] = q.to;
            tree[q.to].push_back(q.x);
        }

        if (q.ty == "push_front") {
            p[q.x] = q.to;
            tree[q.to].push_front(q.x);
        }

        if (q.ty == "pop_back") {
            ll y = tree[q.x].back();
            p[y] = y;
            tree[q.x].pop_back();
        }

        if (q.ty == "pop_front") {
            ll y = tree[q.x].front();
            p[y] = y;
            tree[q.x].pop_front();
        }

        if (q.ty == "pop_complexity") {
            if (precalc && !calced) {
                for (ll i = 0; i < n; i++) {
                    if (p[i] == i) {
                        dp(i, 0);
                    }
                }
                calced = true;
            }
            if (precalc) {
                cout << d[q.x] << endl;
            } else {
                cout << count(q.x) << '\n';
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
