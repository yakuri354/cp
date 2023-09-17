// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
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

const ll inf = INT32_MAX;

random_device rd;
mt19937_64 mt(rd());
uniform_int_distribution<ll> y_dist(INT64_MIN, INT64_MAX);

enum class v_ty { enter, leave };

struct node {
    ll v, y, sz = 1;
    node *l, *r, *p;

    node *v_in, *v_out;
    v_ty v_type;
    node* head;

    ll v_idx;

    node(ll v, node* p) : v(v), y(y_dist(mt)), p(p) {
    }

    void upd() {
        sz = 1;
        if (l) {
            sz += l->sz;
            l->p = this;
        }
        if (r) {
            sz += r->sz;
            r->p = this;
        }
    }
};

pair<node*, node*> split_n(node* t, ll n) {
    if (!t) {
        return {0, 0};
    }

    ll ls = t->l ? t->l->sz : 0;
    if (ls >= n) {
        auto [l1, l2] = split_n(t->l, n);
        t->l = l2;
        t->upd();
        return {l1, t};
    } else {
        auto [r1, r2] = split_n(t->r, n - ls - 1);
        t->r = r1;
        t->upd();
        return {t, r2};
    }
}

node* merge(node* l, node* r) {  // sus?
    if (!l) {
        return r;
    }
    if (!r) {
        return l;
    }

    if (l->y > r->y) {
        l->r = merge(l->r, r);
        l->upd();
        return l;
    } else {
        r->l = merge(l, r->l);
        r->upd();
        return r;
    }
}

// idk sus
ll get_idx(node* t) {
    if (!t) return 0;

    ll ans = 0;
    if (t->l) ans += t->l->sz;

    if (t->p) {
        ans += get_idx(t->p);
        if (t->p->l == t) {
            ans -= t->sz;
        }
    } 
    
    return ans;
}

void solve() {
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
