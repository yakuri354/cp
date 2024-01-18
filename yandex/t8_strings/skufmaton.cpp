// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <array>
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

const ll sigma = 26;

struct node {
    ll len = 0, link = -1;

    std::array<ll, sigma> n;

    node() {
        fill(n.begin(), n.end(), -1);
    }
};

const ll maxn = 1e2 + 1; // TODO

node a[2 * maxn];
ll last = 0, sz = 1;

void sa_extend(ll c) {
    ll cur = sz++;
    a[cur].len = a[last].len + 1;

    ll p = last;
    for (; p != -1 && a[p].n[c] == -1; p = a[p].link) a[p].n[c] = cur;

    if (p == -1) {
        a[cur].link = 0;
        last = cur;
        return;
    }

    auto q = a[p].n[c];

    if (a[q].len != a[p].len + 1) {
        ll cl = sz++;
        a[cl] = a[q];
        a[cl].len = a[p].len + 1;
        a[q].link = cl;
        a[cur].link = cl;

        ll p2 = p;
        for (; p2 != -1 && a[p2].n[c] == q; p2 = a[p2].link) a[p2].n[c] = cl;
    } else {
        a[cur].link = q;
    }

    last = cur;
}

void solve() {

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

