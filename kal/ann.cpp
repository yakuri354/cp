// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll c[26];
ll s[365][26];
ll last[365][26];

ll cur[356];

ll d;
ll score() {
    ll ans = 0;
    for (ll i = 0; i < d; i++) {
        for (ll j = 0; j < 26; j++) {
            if (i == 0) last[i][j] = 0;
            else last[i][j] = last[i-1][j];
        }
        last[i][cur[i]] = i;
    }

    for (ll i = 0; i < d; i++) {
        ans += s[i][cur[i]];
        for (ll j = 0; j < 26; j++) {
            ans -= c[j] * (i - last[i][j]);
        }
    }

    return ans;
}

void solve() {
    cin >> d;
    
    for (ll i = 0; i < 26; i++) {
        cin >> c[i];
    }

    for (ll i = 0; i < d; i++) {
        ll mx = -inf;
        for (ll j = 0; j < 26; j++) {
            cin >> s[i][j];
            if (s[i][j] > mx) {
                mx = s[i][j];
                cur[i] = j;
            }
        }
    }

    fl temp = 1;

    random_device rd;
    mt19937_64 mt(rd());
    
    uniform_int_distribution<ll> ddi(0, d - 1);
    uniform_int_distribution<ll> sdi(0, 25);
    uniform_real_distribution<fl> rdi;
    ll state = score();
    for (ll it = 0; it < ll(1.6 * 1e5); it++) {
        // if (it % 10000 == 0) {
        //     cerr << state << endl;
        // }
        ll di = ddi(mt);
        ll sj = sdi(mt);
        ll old = cur[di];
        cur[di] = sj;
        ll newst = score();

        if (rdi(mt) < exp((newst - state) / temp)) {
            state = newst;
        } else {
            cur[di] = old;
        }

        temp *= 0.99999;
    }

    for (ll i = 0; i < d; i++) {
        cout << cur[i] + 1 << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
