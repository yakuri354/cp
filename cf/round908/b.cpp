// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

void solve() {
    ll n;

    cin >> n;

    vector<ll> a(n);
    map<ll, ll> st;
    for (ll &i: a) {
        cin >> i;
        st[i]++;
    }

    set<ll> st2;

    for (auto [k, v]: st) {
        if (v >= 2) st2.insert(k);
    }

    if (st2.size() < 2) {
        cout << "-1\n";
        return;
    }

    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) {
        if (a[i] == *st2.begin() && cnt.count(a[i]) == 0) {
            cout << 2 << ' ';
        } else if (cnt.count(a[i]) == 0) {
            cout << 1 << ' ';
        } else {
            cout << 3 << ' ';
        }
        cnt[a[i]]++;
    }
    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}

