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
#include <optional>
#include <queue>
#include <array>
#include <tuple>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;
template<typename T>
using opt = optional<T>;

const ll maxn = 5e5 + 1;

const ll tries = 3;
const ll all_tries = 30;

ll n;

ll prefs[maxn + 1];

struct evt {
    ll ty, x, qi;
};

struct qstate {
    array<ll, 10> tt = {}, c1 = {};
    ll want = 0;
    ll ans = 0;
};

ll a[maxn];

void solve() {
    ll q;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    mt19937_64 mt(0xab0ba);

    unordered_map<ll, ll> t1;

    vector<qstate> qs(q);

    vector<vector<evt>> evs(n + 1);

    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l--;

        t1.clear();
        priority_queue<pll, vector<pll>> t2;

        for (ll j = 0; j < all_tries; j++) {
            ll x = a[uniform_int_distribution<ll>(l, r - 1)(mt)];
            t1[x]++;
        }

        for (auto [k, v]: t1) {
            t2.push({v, k});
        }

        for (ll j = 0; j < tries && !t2.empty(); j++) {
            ll x = t2.top().second;
            t2.pop();
            qs[i].tt[j] = x;
        }

        qs[i].want = (r - l) / 2;

        if (l > 0) {
            evs[l - 1].push_back({1, l - 1, i});
        }
        evs[r - 1].push_back({-1, r - 1, i});
    }

    for (ll i = 0; i < n; i++) {
        prefs[a[i]] += 1;

        for (evt e: evs[i]) {
            if (e.ty == 1) {
                for (ll j = 0; j < tries; j++) {
                    qs[e.qi].c1[j] -= prefs[qs[e.qi].tt[j]];
                }
            } else {
                for (ll j = 0; j < tries; j++) {
                    qs[e.qi].c1[j] += prefs[qs[e.qi].tt[j]];

                    if (qs[e.qi].c1[j] > qs[e.qi].want) {
                        qs[e.qi].ans = qs[e.qi].tt[j];
                        break;
                    }
                }
            }
        }
    }

    for (ll i = 0; i < q; i++) {
        cout << qs[i].ans << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
