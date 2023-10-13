// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

const ll inf = INT32_MAX;

random_device rd;
mt19937_64 mt(rd());
uniform_int_distribution<ll> y_dist(INT64_MIN, INT64_MAX);

struct node {
    ll x, y, sz = 1;
    ll sum;
    
    node *l, *r;
    
    node(ll x) : x(x), y(y_dist(mt)), sum(x) {}
    
    void upd() {
        sum = x;
        sz = 1;
        if (l) {
            sum += l->sum;
            sz += l->sz;
        }
        if (r) {
            sum += r->sum;
            sz += r->sz;
        }
    }
};

pair<node*, node*> split_n(node *t, ll n) {
    if (!t) return {0, 0};
    
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

void solve() {

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
