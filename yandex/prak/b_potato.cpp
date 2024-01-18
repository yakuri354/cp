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
#include <cstring>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

struct query {
    ll k;
    string perm;
    ll i;
};

struct node {
    ll term = 0, through = 0;

    node* n[26] = {0};
};

vector<string> a;

void add(string &s, node *t) {
    t->through++;
    for (ll i = 0; i < s.size(); i++) {
        if (!t->n[s[i] - 'a']) {
            t->n[s[i] - 'a'] = new node();
        }
        t = t->n[s[i] - 'a'];
        t->through++;
    }
    t->term++;
}

struct res {
    ll x[26][26];
    ll term;
};

void calc(string &s, node *t, res *r) {
    for (ll i = 0; i < s.size(); i++) {
        for (ll j = 0; j < 26; j++) {
            if (j == s[i] - 'a') continue;
            if (t->n[j]) r->x[s[i] - 'a'][j] += t->n[j]->through;
        }
        r->term += t->term;
        if (i != s.size() - 1) t = t->n[s[i] - 'a'];
    }
}

void solve() {
    ll n;
    cin >> n;

    a.resize(n);

    for (auto &i: a) cin >> i;

    ll q;
    cin >> q;

    vector<vector<query>> qs(n);

    for (ll i = 0; i < q; i++) {
        ll k;
        string p;
        cin >> k >> p;
        k--;

        qs[k].push_back({k, p, i});
    }

    vector<ll> qa(q);

    auto t = new node();
    for (auto &s: a) add(s, t);

    auto r = new res();
    vector<ll> pos(26);
    for (ll i = 0; i < n; i++) {
        if (qs[i].empty()) continue;

        r->term = 0;
        for (ll i = 0; i < 26; i++) {
            for (ll j = 0; j < 26; j++) {
                r->x[i][j] = 0;
            }
        }

        calc(a[i], t, r);

        for (query &q: qs[i]) {
            for (ll i = 0; i < q.perm.size(); i++) {
                pos[q.perm[i] - 'a'] = i;
            }

            ll ans = r->term;

            for (ll i = 0; i < 26; i++) {
                for (ll j = 0; j < 26; j++) {
                    if (pos[j] < pos[i]) ans += r->x[i][j];
                }
            }

            qa[q.i] = ans;
        }
    }

    for (ll i = 0; i < q; i++) {
        cout << qa[i] + 1 << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

