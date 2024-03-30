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
using pll = pair<ll, ll>;

ll ask(ll a, ll b, ll c, ll d) {
    cout << "? " << a+1 << ' ' << b+1 << ' ' << c+1 << ' ' << d+1 << endl;
    string r;
    cin >> r;

    if (r == "0") return 0;
    if (r == "-") return -1;
    if (r == "+") return 1;
    
    exit(-1);
}

void done(bool convex) {
    cout << "! " << (convex ? "YES": "NO") << endl;
    exit(0);
}

void solve() {
    ll n;
    cin >> n;

    ll sgn = ask(0, 1, 1, 2);
    if (sgn == 0) done(false);

    for (ll i = 1; i < n; i++) {
        ll x = ask(i, (i + 1) % n, (i + 1) % n, (i + 2) % n);
        if (i != 1) {
            if (ask(i, 0, 0, 1) != sgn) done(false);
        }
        if (x != sgn) done(false);
    }

    for (ll i = 1; i < n; i++) {
        if (ask(0, i, 0, (i + 1) % n) != sgn) done(false);
    }

    done(true);
}

int main() {
    // ll t; cin >> t; while (t --> 0)
    solve();
}

