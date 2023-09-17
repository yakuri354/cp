// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct qr {
    ll l, r, i;

    pair<ll, ll> toPair(ll bs) const {
            return make_pair(l / bs, ((l / bs) & 1) ? -r : +r);
    }
};

void solve() {
    ll n;
    cin >> n;
    n++;

    vector<ll> a(n);
    for (ll i = 1; i < n; i++) {
        cin >> a[i];
    }

    ll q;
    cin >> q;

    ll bs = 317;
    vector<vector<qr>> bb(bs);
    vector<ll> rs(q);
    vector<ll> ls(q);
    
    for (ll i = 0; i < q; i++) {
        qr qq;
        cin >> qq.l >> qq.r;
        qq.i = i;

        bb[qq.l / bs].push_back(qq);
        
        rs[i] = qq.r;
        ls[i] = qq.l;
    }

    for (auto &b : bb) {
        sort(b.begin(), b.end(), [](qr &a, qr &b) {
            return a.r > b.r;
        });
        reverse(b.begin(), b.end());
    }

    vector<ll> px(n);
    for (ll i = 1; i < n; i++) {
        px[i] = px[i-1] xor a[i];
    }

    auto pxor = [&](ll i) {
        if (i < 0) return 0ll;
        else return px[i];
    };

    vector<ll> ans(q);

    unordered_map<ll, ll> al1;
    unordered_map<ll, ll> ar1;
    ll z = 0;
    for (ll i = 0; i < bb.size(); z += bs, i++) {
        ll l;
        if (i % 2 == 0) l = z;
        else l = (i - 1) * bs + bs;

        ll r = l;
        ll st = 0;
        r--;

        if (l == 0) {
            l++, r++;
        }

        al1.clear();
        ar1.clear();

        if (l > n) goto zz;

        for (auto qq : bb[i]) {
            g: if (l > qq.l) {
                l -= 1;
                st += ar1[pxor(l - 1)];
                al1[pxor(l - 1)] += 1;
                ar1[pxor(l)] += 1;
                goto g;
            }

            if (r < qq.r) {
                r += 1;
                st += al1[pxor(r)];
                al1[pxor(r - 1)] += 1;
                ar1[pxor(r)] += 1;
                goto g;
            }

            if (l < qq.l) {
                st -= ar1[pxor(l - 1)];
                al1[pxor(l - 1)] -= 1;
                ar1[pxor(l)] -= 1;
                l += 1;
                goto g;
            }

            ans[qq.i] = st;
        }
    }

zz: for (ll i = 0; i < q; i++) {
        ll y = (rs[i] - ls[i] + 1) * (rs[i] - ls[i] + 2) / 2 - ans[i];
        cout << y << '\n';
    }
    cout << flush;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
