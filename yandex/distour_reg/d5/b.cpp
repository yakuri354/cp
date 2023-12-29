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

struct pt {
    ll x, t;
};

vector<pt> a;
ll N, T;

bool check1(ll k) { // can we eat k or more in T?
    if (k == 0) return true;
    if (k > N) return false;

    multiset<ll, greater<>> best;   

    ll bound = 0, sum = 0;
    for (ll i = 0; i < k; i++) {
        best.insert(a[i].t);
        sum += a[i].t;
        bound = a[i].x;
    }

    if (bound + sum <= T) return true;

    for (ll i = k; i < N; i++) {
        ll worst = *best.begin();
        bound = a[i].x;
        if (a[i].t < worst) {
            best.erase(best.begin());
            best.insert(a[i].t);
            sum = sum - worst + a[i].t;
        }
        if (bound + sum <= T) return true;
    }

    return false;
}

void solve() {
    cin >> N >> T;

    a.resize(N);
    
    for (auto &[x, y]: a) cin >> x >> y;

    ll lo = 0, hi = N + 1;

    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;

        if (check1(m)) lo = m;
        else hi = m;
    }

    cout << lo << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

