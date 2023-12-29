#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ull M = 29;

ull p[1001];
ll taken[1001];
// gp_hash_table<ull, ll> table;
unordered_map<ull, ll> table;


static ull gs = 309823409; /* The state can be seeded with any value. */

ull rnd() {
	ull z = (gs += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return gs = z ^ (z >> 31);
}

void solve() {
    string s;
    cin >> s;
    ll n = s.length();
    ll k;
    cin >> k;

    p[0] = 1;
    for (ll i = 1; i <= k; i++) {
        p[i] = p[i-1] * M;
    }

    ll maxc = 0;

    ll iters = 1;
    while (clock() < CLOCKS_PER_SEC * 1.995) {
        ull h = 0;
        if (k > n / 2) {
            for (ll i = 0; i < n - k; i++) {
                ll ix = rnd() % n;
                while (taken[ix] == iters) ix = rnd() % n;
                taken[ix] = iters;
            }
            ll ix = 0;
            for (ll i = 0; i < n; i++) {
                if (taken[i] != iters) h += ull(s[i] - 'a' + 1) * p[ix++];
            }
        } else {
            for (ll i = 0; i < k; i++) {
                ll ix = rnd() % n;
                while (taken[ix] == iters) ix = rnd() % n;
                taken[ix] = iters;
            }
            ll ix = 0;
            for (ll i = 0; i < n; i++) {
                if (taken[i] == iters) h += ull(s[i] - 'a' + 1) * p[ix++];
            }
        }

        maxc = max(maxc, ++table[h]);
        iters++;
    }

    cerr << iters << endl;

    if (maxc >= iters * 0.5) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
