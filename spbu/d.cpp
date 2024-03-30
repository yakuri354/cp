#pragma GCC optimize("Ofast")
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

vector<ll> p;
ll n;

bool act(ll a, ll b) {
    cout << a + 1 << ' ' << b + 1 << endl;
    swap(p[a], p[b]);
    rotate(p.begin(), p.begin() + 1, p.end());

    // cerr << "now ";
    // for (ll &i: p) cerr << i << ' ';
    // cerr << endl;

    string s;
    cin >> s;

    if (s == "!") exit(0);

    return s == "<";
}

ll pos(ll x) {
    return find(p.begin(), p.end(), x) - p.begin();
}


bool cmp2(ll a, ll b) {
    while (p[0] != a) {
        act(0, 0);
    }

    bool res = !act(1, pos(b)); // mega sus !
    // cerr << "- " << a << (res ? " < " : " > ") << b << endl;
    return res;
}

bool cmp3(ll a, ll b) {
    if (p[0] != a) act(1, pos(a));

    return !act(1, pos(b));
}

bool cmp(ll a, ll b) {
    while (p[0] != a && p[0] != b) {
        act(0, 0);
    }

    if (p[0] == a) {
        return !act(1, pos(b)); // mega sus !
    } else {
        return act(1, pos(a));
    }
}

void solve() {
    cin >> n;

    p.resize(n);

    iota(p.begin(), p.end(), 0ll);

    auto p2 = p;

    sort(p2.begin(), p2.end(), [](ll a, ll b) {
        return cmp3(a, b);
    });

    vector<ll> p_orig(n, 0);
    for (ll i = 0; i < n; i++) {
        p_orig[p2[i]] = i;
    }

    // cerr << "FOUND" << endl;
    // for (ll &i: p_orig) cerr << i << ' ';
    // cerr << endl;
    // for (ll &i: p) cerr << i << ' ';
    // cerr << endl << endl;

    vector<ll> p_tgt = p2;
    vector<ll> from = p;
    reverse(p_tgt.begin(), p_tgt.end());

    // ll bgn = pos(p_tgt[0]);
    for (ll i = 1; i < n; i++) {
        ll b0 = pos(p_tgt[0]);
        ll need = (b0 + i) % n;
        ll have = pos(p_tgt[i]);
        // for (ll &i: p) cerr << i << ' ';
        // cerr << " => " << need << " " << have << endl;
        if (need != have) {
            act(have, need);
        }
    }

    while (pos(p_tgt[0]) != 0) act(0, 0);

    // cout << "!" << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

