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

const ull P = 307;

vector<ull> p;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<string> ss(n);
    for (auto &i: ss) cin >> i;

    vector<ll> a(m);
    for (auto &i: a) cin >> i;

    set<ll> gcds;

    vector<ll> lens;
    for (auto &i: ss) lens.push_back(i.size()), gcds.insert(i.size());

    for (ll x: lens) {
        for (ll y: a) {
            gcds.insert(__gcd(ull(x), ull(y)));
        }
    }

    ll maxdec = accumulate(lens.begin(), lens.end(), 0ll);

    vector<bool> dec(maxdec + 1);
    dec[0] = true;
    for (ll x: gcds) {
        for (ll i = x; i <= maxdec; i++) {
            dec[i] = dec[i] || dec[i-x];
        }
    }

    p.resize(10001);
    p[0] = 1;
    for (ll i = 1; i < 10001; i++) {
        p[i] = p[i-1] * P;
    }

    ll BP = 5000;

    set<ull> pxhs;

    for (ll i = 0; i < n; i++) {
        ull hs = ss[i][0] * p[BP - 1];
        pxhs.insert(hs);
        for (ll j = 1; j < ss[i].size(); j++) {
            hs += ss[i][j] * p[BP - j - 1];
            pxhs.insert(hs);
        }
    }

    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++) {
        string t;
        cin >> t;

        vector<ull> hs;
        
        hs.resize(t.size() + 1);
        hs[0] = 0;
        for (ll j = 1; j <= t.size(); j++) {
            hs[j] = hs[j-1] + t[j-1] * p[BP-j];
        }

        vector<bool> ok(t.size() + 1);
        ok[0] = true;
        for (ll i = 1; i <= t.size(); i++) {
            for (ll j = 0; j < i; j++) {
                if (dec[i - j] && ok[j] == true && pxhs.count(p[j] * (hs[i] - hs[j]))) {
                    ok[i] = true;
                    break;
                }
            }
        }

        if (ok[t.size()]) {
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

