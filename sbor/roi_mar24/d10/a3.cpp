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

const ll all_tries = 25;

ll n;

ll prefs[maxn + 1];

struct evt {
    ll ty, qi;
};

struct qstate {
    array<pll, all_tries> st;
    ll want = 0, cnt = 0, ans = 0;
};

ll a[maxn];

void solve() {
    ll q;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    mt19937_64 mt(20);

    vector<qstate> qs(q);

    vector<vector<evt>> evs(n + 1);

    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l--;

        for (ll j = 0; j < all_tries; j++) {
            ll x = a[uniform_int_distribution<ll>(l, r - 1)(mt)];
            if (find(qs[i].st.begin(), qs[i].st.begin() + qs[i].cnt, pll{0, x}) == qs[i].st.begin() + qs[i].cnt) {
                qs[i].st[qs[i].cnt] = {0, x};
                qs[i].cnt++;
            }
        }

        qs[i].want = (r - l) / 2;

        if (l > 0) {
            evs[l - 1].push_back({1, i});
        }
        evs[r - 1].push_back({-1, i});
    }

    for (ll i = 0; i < n; i++) {
        prefs[a[i]] += 1;

        for (evt e: evs[i]) {
            if (e.ty == 1) {
                for (auto &[c, x]: qs[e.qi].st) {
                    c -= prefs[x];
                }
            } else {
                for (auto &[c, x]: qs[e.qi].st) {
                    c += prefs[x];

                    if (c > qs[e.qi].want) {
                        qs[e.qi].ans = x;
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
