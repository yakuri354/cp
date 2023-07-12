// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
#include <cmath>

using namespace std;
using ll = long long;
using fl = long double;
using pf = pair<fl, fl>;
const ll inf = INT32_MAX;

pf a[1000];
pf b[1000];
ll n, k;

fl f() {
    fl ans = 0;
    for (ll i = 0; i < n; i++) {
        fl md = inf;
        for (ll j = 0; j < k; j++) {
            fl hd = a[i].first - b[j].first, vd = a[i].second - b[j].second;
            md = min(md, sqrtl(hd * hd + vd * vd));
        }
        ans += md;
    }
    return ans;
}

void solve() {
    cin >> n >> k;

    cout << fixed << setprecision(6);

    for (ll i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    mt19937_64 mt(random_device{}());
    uniform_int_distribution<ll> kd(0, k-1);
    uniform_int_distribution<ll> nd(0, n-1);
    uniform_real_distribution<fl> fd{};
    uniform_real_distribution<fl> ad(0, 2 * M_PI);

    for (ll i = 0; i < k; i++) {
        b[i] = a[i];
    }

    fl curr = f();
    fl temp = 1;
    fl dmod = 100;
    for (ll iter = 0;; iter++) {
        if (fl(clock()) / CLOCKS_PER_SEC > 0.99) {
            break;
        }

        if (iter % 10000 == 0) {
            cerr << "T " << temp << endl;
            cerr << "D " << curr << endl;
            cerr << endl;
        }

        ll ix = kd(mt);
        pf oldc = b[ix];

        if (fd(mt) < temp * temp / 2) {
            b[ix] = a[nd(mt)];
        } else {
            fl angle = ad(mt);
            b[ix].first += cos(angle) * temp;
            b[ix].second += sin(angle) * temp;
        }

        fl newst = f();

        if (fd(mt) < exp((curr - newst) / (temp * temp))) {
            curr = newst;
        } else {
            b[ix] = oldc;
        }

        temp = 1 - fl(clock()) / CLOCKS_PER_SEC;
    }

    for (ll i = 0; i < k; i++) {
        cout << b[i].first << ' ' << b[i].second << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
