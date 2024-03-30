// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <map>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

ll n, t, s;

vector<ll> a;

void solve() {
    cin >> n >> t >> s;

    set<ll> data;
    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        data.insert(x);
    }

    ll q;
    cin >> q;

    reverse(a.begin(), a.end());

    for (ll qi = 0; qi < q; qi++) {
        ll val, ord;
        cin >> val >> ord;

        ord--;

        auto arr = data;
        set<ll> curr;

        ll lb = -1, ub = n - 1;

        ll prev = 0;
        for (ll day = 0;; day++) {
            while (arr.size() > 0 && *arr.rbegin() >= t - s * day) {
                curr.insert(*arr.rbegin());
                arr.erase(*arr.rbegin());
            }

            if (curr.empty()) continue;

            if (curr.count(val) && lb == -1) lb = prev;

            if (*curr.rbegin() == val) {
                ub = prev + curr.size() - 1;
                break;
            } else {
                prev++;
                curr.erase(*curr.rbegin());
            }
        }

        if (lb <= ord && ord <= ub) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}


