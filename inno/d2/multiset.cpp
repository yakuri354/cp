// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using ui = unsigned int;
using fl = long double;

const ll inf = INT32_MAX;

ui bswap(ui v) {
    ui v2 = 0;
    for (ui i = 0; i < sizeof(ui) * 8 - 1; i++) {
        ui x = (v >> i) & 1;
        v2 |= x << (sizeof(ui) * 8 - i - 2);
    }
    
    return v2;
}

struct node {
    ui term = 0;
    ll term_children = 0;
    node *c[2] = {};

    void add_num(ui v, ui i) {
        term_children += 1;
        if (i >= sizeof(ui) * 8 - 1) {
            term++;
            return;
        } 

        ui ix = (v >> i) & 1;

        if (c[ix] == 0) {
            // c[ix] = new node(ix);
            c[ix] = new node();
        }

        c[ix]->add_num(v, i + 1);
    }

    void rm_num(ui v, ui i) {
        term_children -= 1;
        if (i >= sizeof(ui) * 8 - 1) {
            term--;
            return;
        }

        ui ix = (v >> i) & 1;

        c[ix]->rm_num(v, i + 1);

        if (c[ix]->term_children <= 0) {
            delete c[ix];
            c[ix] = 0;
        }
    }

    ui max_xor(ui v, ui i, bool x) {
        ui ix = (v >> i) & 1, nxt = ix ^ 1;

        if (!c[nxt]) nxt ^= 1;

        if (!c[nxt]) return x;

        return (c[nxt]-> max_xor(v, i + 1, nxt) << 1) | x;
    }

    void dfs(ui v, ui i) {
        if (term > 0) {
            cout << bswap(v) << " x " << term << endl;
            return;
        }

        if (c[0]) c[0]->dfs(v, i + 1);
        if (c[1]) c[1]->dfs(v | (1 << i), i + 1);
    }
};

void solve() {
    // node *r[2] = {new node(0), new node(1)};
    node *r = new node();
    r->add_num(0, 0);
    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        string qt;
        ui x;
        cin >> qt >> x;

        if (qt == "+") {
            r->add_num(bswap(x), 0);
        }

        if (qt == "-") {
            r->rm_num(bswap(x), 0);
        }

        if (qt == "?") {
            ll el = r->max_xor(bswap(x), 0, 0) >> 1;
            cout << (x ^ bswap(el)) << '\n';
        }
        
        if (qt == "p") {
            r->dfs(0, 0);
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
