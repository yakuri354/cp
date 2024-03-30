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

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

struct node {
    ll x, sum;

    node *par = nullptr;
};

node null_node = {0, 0, nullptr};

void solve() {
    ll n;
    cin >> n;

    vector<node*> a{&null_node};

    for (ll i = 0; i < n; i++) {
        ll t, m;
        cin >> t >> m;

        if (m == 0) {
            a.push_back(a[t]->par);
        } else {
            a.push_back(new node{m, m + a[t]->sum, a[t]});
        }
    }

    ll ans = 0;
    for (auto x: a) {
        ans += x->sum;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

