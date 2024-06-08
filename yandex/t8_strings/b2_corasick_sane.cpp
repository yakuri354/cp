// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>

using namespace std;
using ll = int;
using ull = unsigned long long;
using fl = long double;

const ll sigma = 26;

struct node {
    char c;
    // vector<int> term{};
    int term = -1;
    int suff = -1, exit = -1, p = -1;

    array<int, sigma> fail{}, nx{};

    node(): c('\xff') {
        fill(fail.begin(), fail.end(), -1);
        fill(nx.begin(), nx.end(), -1);
    }
};

const ll maxn = 1e6 + 2;

node a[maxn];

int root = 0, sz = 1;

int go(int i, char c);

int link(int i) {
    if (a[i].suff == -1) {
        if (a[i].p == root) { // 1 char string
            a[i].suff = root;
        } else {
            a[i].suff = go(link(a[i].p), a[i].c);
        }
    }
    return a[i].suff;
}

int go(int i, char c) {
    if (a[i].fail[c] == -1) {
        if (a[i].nx[c] != -1) {
            a[i].fail[c] = a[i].nx[c];
        } else if (i == root) {
            a[i].fail[c] = root;
        } else {
            a[i].fail[c] = go(link(i), c);
        }
    }

    return a[i].fail[c];
}

int next_term(int i) {
    if (a[i].exit == -1) {
        int l = link(i);
        if (a[l].term != -1) {
            return l;
        } else {
            return next_term(l);
        }
    }
    
    return a[i].exit;
}

void halt() {
    volatile ull x = 0;
    while (1) x++;
}

map<int, vector<int>> more_ents;

void add(string& s, ll idx) {
    int i = root;
    for (char _c : s) {
        char c = _c - 'a';
        if (a[i].nx[c] == -1) {
            sz++;
            if (sz > maxn) halt();
            a[i].nx[c] = sz - 1;
            a[sz - 1].c = c;
            a[sz - 1].p = i;
        }

        i = a[i].nx[c];
    }

    if (a[i].term != -1) {
        more_ents[a[i].term].push_back(idx);
    } else {
        a[i].term = idx;
    }
}

void solve() {
#ifdef DBG
#define fin cin
#define fout cout
#else
    fstream fin("inputik.txt");
    fstream fout("outputik.txt");
#endif

    string t;
    fin >> t;

    ll n;
    fin >> n;

    vector<ll> sz(n);

    a[root].c = 255;
    a[root].exit = root;
    a[root].p = root;
    a[root].suff = root;

    for (ll i = 0; i < n; i++) {
        string s;
        fin >> s;

        sz[i] = s.size();

        add(s, i);
    }

    vector<vector<ll>> ans(n);

    int curr = root;
    for (ll i = 0; i < t.size(); i++) {
        curr = go(curr, t[i] - 'a');

        int top = curr;
        while (top != root) {
            // for (ll x: a[top].term) {
            ll x = a[top].term;
            if (x != -1) {
                ans[x].push_back(i - sz[x] + 1);
                if (more_ents.count(x)) {
                    for (int x1: more_ents[x]) {
                        ans[x1].push_back(i - sz[x1] + 1);
                    }
                }
            }
            // }
            top = next_term(top);
        }
    }

    for (ll i = 0; i < n; i++) {
        fout << ans[i].size() << ' ';
        for (ll j : ans[i]) {
            fout << j + 1 << ' ';
        }
        fout << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

