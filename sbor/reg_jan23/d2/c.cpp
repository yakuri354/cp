// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

string txt;
ll sz[51];
ll d[201];
string ans[201];
ll lastarg[201];
ll p[201];
ll pw[201];
ll k, b;

ll to_dig(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return -1;
}

void solve() {
    cin >> k >> b;

    pw[0] = 1;
    for (ll i = 1; i <= 200; i++) {
        if (pw[i-1] <= 1e13) {
            pw[i] = pw[i-1] * b;
        }
    }

    for (ll i = 0; i < k; i++) {
        cin >> sz[i];
    }
    getline(cin, txt);
    getline(cin, txt);
    ll n = txt.size();

    d[0] = 0;
    p[0] = -1;
    for (ll i = 1; i <= n; i++) {
        d[i] = d[i-1] + 1;
        ans[i] = txt[i-1];
        lastarg[i] = -1;
        p[i] = i-1;
        for (ll z = 0, nval = 0; i - z - 1 >= 0; z++) {
            ll dig = to_dig(txt[i - z - 1]);
            if (dig == -1 || dig >= b) break;

            nval += pw[z] * dig;
            auto lit = lower_bound(sz, sz + k, nval);
            if (lit == sz + k) break;
            ll j = lit - sz;

            if (dig != 0) {
                ll hi = i - z - 1;
                ll alt = d[hi] + 2 + j;
                if (alt <= d[i]) {
                    ans[i] = "%";
                    for (ll z = 0; z < j; z++) {
                        ans[i] += "l";
                    }
                    ans[i] += "i";
                    lastarg[i] = nval;
                    d[i] = alt;
                    p[i] = hi;
                }
            }
        }
    }

    ll nx = n;
    vector<string> ans1;
    vector<ll> args;
    while (nx > 0) {
        ans1.push_back(ans[nx]);
        args.push_back(lastarg[nx]);
        nx = p[nx];
    }

    reverse(ans1.begin(), ans1.end());
    reverse(args.begin(), args.end());
    string ans2;

    for (auto &i : ans1) {
        ans2 += i;
    }

    assert(ans2.size() == d[n]);
    cout << ans2 << '\n';

    for (ll i : args) {
        if (i == -1) continue;
        cout << i << ' ';
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
