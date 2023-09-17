// #pragma GCC optimize("Ofast")
#include <fstream>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <unordered_set>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;
const ull P = 307;

ull p[maxn], h[maxn];

ifstream fin("keepcounted.in");
ofstream fout("keepcounted.out");

ull hs(ll l, ll r) {
    ull v = 0;
    if (r > 0) v += h[r-1];
    if (l > 0) v -= h[l-1];

    return v * p[l];
}

void solve() {
    string s;
    fin >> s;
    ll n = s.size();

    p[0] = 1;
    for (ll i = 1; i < n; i++) {
        p[i] = p[i-1] * P;
    }

    h[0] = s[0] * p[n - 1];
    for (ll i = 1; i < n; i++) {
        h[i] = h[i-1] + s[i] * p[n - i - 1];
    }

    unordered_set<ull> subs;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j <= i; j++) {
            // fout << "inserting " << s.substr(j, i - j + 1) << endl;;
            subs.insert(hs(j, i + 1));
        }
        fout << subs.size() << '\n';
    }
}


int main() {
    fin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
