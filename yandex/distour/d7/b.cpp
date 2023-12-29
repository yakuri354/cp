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
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

template<typename E>
using st = tree<E, null_type, std::less<>, rb_tree_tag, tree_order_statistics_node_update>;

#ifdef DBG
#define inv(__inv_x)                                                       \
    if (!(__inv_x)) {                                                      \
        cerr << "invariant " #__inv_x " violated at " << __LINE__ << endl; \
        exit(-1);                                                    \
    }
#else
#define inv(x)
#endif

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

mt19937_64 mt(228);

st<ll> inside, outside;
st<pair<ll, ll>> ans;
ll diff = 0;
ll ops = 0;

ll pick(st<ll> &s) {
    inv(s.size() > 0);
    auto it = s.find_by_order(uniform_int_distribution<ll>(0, s.size() - 1)(mt));
    ll v = *it;
    s.erase(it);
    return v;
}

pair<ll, ll> in_rnd() {
    ll x = pick(outside);
    cout << "? " << x << endl;
    ops++;
    inside.insert(x);
    ll old = diff;
    cin >> diff;
    inv(diff >= old);
    return {x, diff - old};
}

pair<ll, ll> out_rnd(ll except) {
    inv((inside.size() > 1 || except == -1) && inside.size() > 0);

    ll x = except;
    while (x == except) {
        ll xi = uniform_int_distribution<ll>(0, inside.size() - 1)(mt);
        auto it = inside.find_by_order(xi);
        if (*it == except) continue;
        x = *it;
        inside.erase(it);
    }

    cout << "? " << x << endl;
    ops++;
    outside.insert(x);

    ll old = diff;
    cin >> diff;
    inv(diff <= old);
    return {x, old - diff};
}

void put_out(ll x) {
    while (inside.size() > 1) {
        inv(inside.size() == diff + 1);
        auto [y, d] = out_rnd(x);
        inv(x != y);
        if (d == 0) {
            ans.insert({x, y});
            cout << "? " << x << endl;
            ops++;
            inside.erase(x);
            cin >> diff;
            return;
        }
    }
}

void put_in() {
    while (outside.size() > 0) {
        inv(inside.size() == diff);
        auto [x, d] = in_rnd();
        if (d == 0) {
            put_out(x);
        }
    }
}

void solve() {
    ll n;
    cin >> n;

    for (ll i = 1; i <= 2 * n; i++) {
        outside.insert(i);
    }

    put_in();

    cout << "! ";
    for (auto [l, r]: ans) {
        cout << l << ' ' << r << ' ';
    }
    cout << endl << flush;


    cout << endl << endl << ops << endl;
}

int main() {
    // cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

