// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll sigma = 26;

struct node {
    char c;
    vector<int> term{};
    node *suff = 0, *exit = 0, *p{};

    unordered_map<char, node*> fail{}, nx{};

    node(ll c, node* par = nullptr) : c(c) {
        if (par == nullptr) {
            this->p = this;
            this->exit = this;
            this->suff = this;
        } else {
            this->p = par;
        }
    }

    node* link() {
        if (!suff) {
            if (p->p == p) { // 1 char string
                suff = p;
            } else {
                suff = p->link()->go(c);
            }
        }
        return suff;
    }

    node* go(char x) {
        if (!fail.count(x)) {
            if (nx.count(x)) {
                fail[x] = nx[x];
            } else if (p == this) {
                fail[x] = this;
            } else {
                fail[x] = link()->go(x);
            }
        }

        return fail[x];
    }

    node *next_term() {
        if (!exit) {
            if (!link()->term.empty()) {
                return link();
            } else {
                return link()->next_term();
            }
        }
        
        return exit;
    }

    void add(string& s, ll idx) {
        auto t = this;

        for (char _c : s) {
            char c = _c - 'a';
            if (!t->nx.count(c)) {
                t->nx[c] = new node(c, t);
            }

            t = t->nx[c];
        }

        t->term.push_back(idx);
    }
};


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

    auto root = new node(-1);

    vector<ll> sz(n);

    for (ll i = 0; i < n; i++) {
        string s;
        fin >> s;

        sz[i] = s.size();

        root->add(s, i);
    }

    vector<vector<ll>> ans(n);

    auto curr = root;
    for (ll i = 0; i < t.size(); i++) {
        curr = curr->go(t[i] - 'a');

        auto top = curr;
        while (top->p != top) {
            for (ll x: top->term) {
                ans[x].push_back(i - sz[x] + 1);
            }
            top = top->next_term();
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

