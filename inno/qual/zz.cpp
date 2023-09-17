// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct query {
    ll l, r, i;
};

query qr[200000];
ll ans[200000];
vector<vector<ll>> calc;
vector<vector<ll>> arr;
vector<vector<ll>> inv;
vector<ll> curr;
vector<ll> tmp;
ll n, m, q, sum = 0, ls, rs, bs;

void add_r() {
    ll nsum = 0;
    rs++;
    for (ll i = 0; i < m; i++) {
        tmp[i] = arr[rs][curr[i]];
        nsum += (tmp[i] + 1) * (i + 1);
    }
    sum = nsum;
    curr = tmp;
}

void add_l() {
    ll nsum = 0;
    ls--;
    for (ll i = 0; i < m; i++) {
        tmp[i] = curr[arr[ls][i]];
        nsum += (tmp[i] + 1) * (i + 1);
    }
    sum = nsum;
    curr = tmp;
}

void remove_r() {
    ll nsum = 0;
    for (ll i = 0; i < m; i++) {
        tmp[i] = inv[rs][tmp[i]];
        nsum += (tmp[i] + 1) * (i + 1);
    }
    sum = nsum;
    curr = tmp;
    rs--;
}

void remove_l() {
    ll nsum = 0;
    for (ll i = 0; i < m; i++) {
        tmp[arr[ls][i]] = curr[i];
        nsum += (tmp[arr[ls][i]] + 1) * (arr[ls][i] + 1);
    }
    sum = nsum;
    curr = tmp;
    ls++;
}

constexpr int logn = 18;
constexpr int maxn = 1 << logn;

long long hilbertorder(ll x, ll y) {
    long long d = 0;
    for (ll s = 1 << (logn - 1); s; s >>= 1) {
        bool rx = x && s, ry = y && s;
        d = d << 2 | rx * 3 ^ ll(ry);
        if (!ry) {
            if (rx) {
                x = maxn - x;
                y = maxn - y;
            }
            swap(x, y);
        }
    }
    return d;
}

void solve() {
    cin >> n >> m;

    bs = sqrt(n) / 10 + 1;

    curr.assign(m, 0);
    tmp.assign(m, 0);
    arr.assign(n, {});
    inv.assign(n, {});

    for (ll i = 0; i < n; i++) {
        arr[i].assign(m, 0);
        inv[i].assign(m, 0);
        for (ll j = 0; j < m; j++) {
            cin >> arr[i][j];
            arr[i][j]--;
            inv[i][arr[i][j]] = j;
        }
    }

    cin >> q;
    for (ll i = 0; i < q; i++) {
        cin >> qr[i].l >> qr[i].r;
        qr[i].l--;
        qr[i].r--;
        qr[i].i = i;
    }

    sort(qr, qr + q, [](auto &a, auto &b) {
             if (a.l/bs != b.l/bs) {
                 return a.l < b.l;
             }
             if (a.l/bs % 2 == 0) {
                 return a.r < b.r;
             } else {
                 return a.r > b.r;
             }
         });


    ls = 0, rs = 0;
    sum = 0;
    for (ll i = 0; i < m; i++) {
        curr[i] = arr[0][i];
        sum += (curr[i] + 1) * (i + 1);
    }
    for (ll i = 0; i < q; i++) {
        while (rs < qr[i].r) add_r();
        while (rs > qr[i].r) remove_r();
        while (ls > qr[i].l) add_l();
        while (ls < qr[i].l) remove_l();

        ans[qr[i].i] = sum;
    }

    for (ll i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
        solve();
}

