// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstdint>
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

const ll inf = 1ll << 50;

struct ev {
    ll ty, day, x;
};

ll mod(ll x, ll m) {
    return ((x % m) + m) % m;
}

mt19937_64 mt(1337);

ll solve_dumb(ll n, ll m, vector<ll> a) {
    if (n == 1) { // xxx
        return 0;
    }

    for (ll i = 1; i < n; i++) {
        a[i] -= a[0];
    }

    ll old_zero = a[0];
    a[0] = 0;

    ll ans = inf;

    for (ll i = -m + 1; i < 1; i++) {
        ll nd = (a.back() - i) / m + 1;
        vector<ll> ds(nd, 0);

        for (ll j = 0; j < n; j++) {
            ds[(a[j] - i) / m]++;
        }

        bool ok = true;
        for (ll j = 0; j < nd; j++) {
            ok &= ds[j] > 0;
        }

        if (ok) {
            ans = min(ans, mod(i + old_zero, m));
        }
    }

    if (ans == inf) {
        return -1;
    } else {
        return ans;
    }
}

ll solve_smart(ll n, ll m, vector<ll> a) {
    vector<ev> evs;

    if (n == 1) { // xxx
        return 0;
    }

    for (ll i = 1; i < n; i++) {
        a[i] -= a[0];
    }

    ll old_zero = a[0];
    a[0] = 0;

    for (ll i = 1; i < n; i++) {
        evs.push_back(ev {.ty = 1, .day = a[i] / m, .x = -((a[i] / m + 1) * m - a[i] - 1)}); // sus
        evs.push_back(ev {.ty = -1, .day = a[i] / m, .x = 1});
        evs.push_back(ev {.ty = 1, .day = (a[i] - 1) / m + 1, .x = -m + 1});
        evs.push_back(ev {.ty = -1, .day = (a[i] - 1) / m + 1, .x = a[i] - ((a[i] - 1) / m) * m - m + 1}); // sus
    }

    evs.push_back(ev {.ty = 1, .day = 0, .x = -m + 1});
    evs.push_back(ev {.ty = -1, .day = 0, .x = 1});

    sort(evs.begin(), evs.end(), [](ev a, ev b) {
        return make_pair(a.x, a.ty) < make_pair(b.x, b.ty);
    });

    ll x = -m + 1, last_x = -m + 1;
    unordered_map<ll, ll> days;
    ll ans = inf;

    for (ev e: evs) {
        if (e.x > x) {
            last_x = x;
            x = e.x;

            // from last_x to x - 1
            // if ((a.back() - last_x) / m != (a.back() - x + 1) / m) exit(-1);
            if (days.size() >= (a.back() - last_x) / m + 1) {
                ll from1 = last_x + old_zero;
                ll to1 = x - 1 + old_zero;

                if (mod(to1, m) < mod(from1, m) || to1 - from1 >= m) {
                    ans = 0;
                    break;
                } else {
                    ans = min(ans, mod(from1, m));
                }
            }
        }

        if (e.ty == -1) {
            days[e.day]--;
            if (days[e.day] <= 0) days.erase(e.day);
        } else if (e.ty == 1) {
            days[e.day]++;
        }
    }

    if (ans == inf) {
        return -1;
    } else {
        return ans;
    }
}

template <typename F>
void use(F f) {
    ll n, m;
    cin >> n >> m;

    vector<ll> a(n);

    for (ll &i: a) cin >> i;

    sort(a.begin(), a.end());

    ll res = f(n, m, a);

    cout << res << endl;
}

void stress() {
    for (ll it = 0;; it++) {
        if (it % 10000 == 0) {
            cout << "it " << it << endl;
        }

        ll n = uniform_int_distribution<ll>(1, 3)(mt);
        ll m = uniform_int_distribution<ll>(1, 100)(mt);

        vector<ll> a(n);
        for (ll &i: a) i = uniform_int_distribution<ll>(1, 1000)(mt);

        sort(a.begin(), a.end());

        ll dumb, smart;
        if ((dumb = solve_dumb(n, m, a)) != (smart = solve_smart(n, m, a))) {
            cout << "PROLAPS" << endl;
            cout << n << ' ' << m << endl;
            solve_smart(n, m, a);
            solve_dumb(n, m, a);
            exit(0);
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    stress();
}

