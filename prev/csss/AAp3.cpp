// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll maxn = 2 * 1e5;

ll pts[maxn];

mt19937_64 mt(random_device{}());
ll n, q, s, t;

ll calc(vector<bool> &data) {
    ll lastl = s, lastr = t, ans = 0;
    for (ll i = 0; i < data.size(); i++) {
        if (data[i]) {
            ans += abs(pts[i] - lastr);
            lastr = pts[i];
        } else {
            ans += abs(pts[i] - lastl);
            lastl = pts[i];
        }
    }

    return ans;
}

ll recalc(vector<bool> &data, ll ix, ll state) {
    bool orig = data[ix];
    data[ix] = !data[ix];
    ll ri = ix + 1, li = ix - 1;
    while (ri < q && data[ri] == orig) ri++;
    while (li >= 0 && data[li] == orig) li--;
    ll lastl = li == -1 ? (orig ? s : t) : pts[li];
    state += abs(lastl - pts[ix]);
    if (ri != q) {
        state -= abs(lastl - pts[ri]);
        state += abs(pts[ix] - pts[ri]);
    }

    ri = ix, li = ix;
    while (ri < q && data[ri] != orig) ri++;
    while (li >= 0 && data[li] != orig) li--;
    lastl = li == -1 ? (orig ? t : s) : pts[li];
    state -= abs(lastl - pts[ix]);
    if (ri != q) {
        state -= abs(pts[ix] - pts[ri]);
        state += abs(lastl - pts[ri]);
    }

    return state;
}

void solve() {
    cin >> n >> q >> s >> t;

    for (ll i = 0; i < q; i++) {
        cin >> pts[i];
    }

    vector<bool> data(q);
    uniform_int_distribution bd(0, 1);
    for (auto && i : data) {
        i = bd(mt);
    }

    ll state = calc(data);

    uniform_int_distribution nd(0ll, q-1);
    uniform_real_distribution<fl> fd;
    fl temp = 100;
    while (fl(clock()) < fl(CLOCKS_PER_SEC) * 1.99) {
        ll ix = nd(mt);

        ll news = recalc(data, ix, state);

        if (fd(mt) < exp((state - news) / temp)) {
            state = news;
        } else {
            data[ix] = !data[ix];
        }

        // fl zz = 1 - (fl(clock()) / fl(CLOCKS_PER_SEC * 2));
        // temp = zz * zz;
        
        temp *= 0.99999;
    }

    cout << state << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
