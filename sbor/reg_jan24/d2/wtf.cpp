// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

mt19937_64 mt(0xab0ba);
uniform_int_distribution<ll> yd(INT64_MIN, INT64_MAX);

struct node {
    ll x, cnt = 1;
    ll sum = 1;
    ll sz = 1;
    node *l = 0, *r = 0;

    ll y;

    node(ll x, ll cnt): x(x), cnt(cnt), y(yd(mt)) {
        upd();
    }

    void upd() {
        sz = 1;
        sum = cnt;
        if (l) {
            sz += l->sz;
            sum += l->sum;
        }
        if (r) {
            sz += r->sz;
            sum += r->sum;
        }
    }

    void push() {
    }
};

node *merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;

    if (l->y > r->y) {
        l->push();
        l->r = merge(l->r, r);
        l->upd();
        return l;
    } else {
        r->push();
        r->l = merge(l, r->l);
        r->upd();
        return r;
    }
}

pair<node*, node*> split_n(node *t, ll n) {
    if (!t) return {0, 0};
    t->push();

    ll ls = t->l ? t->l->sz : 0;
    if (ls >= n) {
        auto [l1, r1] = split_n(t->l, n);
        t->l = r1;
        t->upd();
        return {l1, t};
    } else {
        auto [l1, r1] = split_n(t->r, n - ls - 1);
        t->r = l1;
        t->upd();
        return {t, r1};
    }
}

pair<node*, node*> split_x(node *t, ll x) {
    if (!t) return {0, 0};
    t->push();

    if (t->x >= x) {
        auto [l1, r1] = split_n(t->l, x);
        t->l = r1;
        t->upd();
        return {l1, t};
    } else {
        auto [l1, r1] = split_n(t->r, x);
        t->r = l1;
        t->upd();
        return {t, r1};
    }
}

pair<node*, node*> cut_x(node *t, ll x) {
    if (!t) return {0, 0};

    auto [l1, r] = split_x(t, x + 1);
    auto [l, m] = split_x(l1, x);

    t = merge(l, r);

    return {t, m};
}

node* add_insert(node *t, ll x, ll cnt) {
    if (!t) return 0;

    auto [l1, r] = split_x(t, x + 1);
    auto [l, m] = split_x(l1, x);

    if (m != nullptr) {
        m->cnt += cnt;
    } else {
        m = new node(x, cnt);
    }

    t = merge(l, merge(m, r));

    return t;
}

node* find_node(node *t, ll x) {
    if (!t) return 0;

    if (t->x == x) return t;
    if (t->x < x) {
        return find_node(t->r, x);
    }
    if (t->x > x) {
        return find_node(t->l, x);
    }
}

const ll K = 400;

ll a_bl[K][K];

vector<node*> kt;

void solve() {
    ll n, q;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        cin >> a_bl[i / K][i % K];
    }

    ll rk = n / K;
    if (n % K != 0) rk++;

    kt.assign(rk, nullptr);

    for (ll i = 0; i < rk; i++) {
        map<ll, ll> mp;
        for (ll j = 0; j < K && i * K + j < n; j++) {
            mp[a_bl[i][j]]++;
        }

        for (auto [v, cnt]: mp) {
            kt[i] = merge(kt[i], new node(v, cnt));
        }
    }

    for (ll qi = 0; qi < q; qi++) {
        ll ty;
        cin >> ty;

        if (ty == 1) {
            ll x;
            cin >> x;

            for (ll i = 0; i < rk; i++) {
                auto [t2, nx] = cut_x(kt[i], x);
                kt[i] = t2;
                if (nx != nullptr) {
                    kt[i] = add_insert(kt[i], x + 1, nx->cnt);
                }
            }
        } else if (ty == 2) {
            ll l, r, y;
            cin >> l >> r >> y;
            l--;

            ll ans = 0;
            for (ll i = l; i < r;) {
                if (i % K == 0 && i + K <= r) {
                    auto [l, r] = split_x(kt[i / K], y + 1);
                    ans += l->cnt;
                    kt[i / K] = merge(l, r);
                    i += K;
                } else {
                    if (a_bl[i / K][i % K] <= y) ans++;
                    i++;
                }
            }

            cout << ans << endl;
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

