// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<ll> rowpos;
ll n;
vector<ll> colcnt;
vector<ll> negdiagcnt;
vector<ll> posdiagcnt;
ll curr = 0;

void upd(ll ix, ll p) {
    ll old = rowpos[ix];
    ll neww = (rowpos[ix] = p);

    curr -= --colcnt[old];
    curr += colcnt[neww]++;

    curr -= --negdiagcnt[n + ix - old];
    curr += negdiagcnt[n + ix - neww]++;

    curr -= --posdiagcnt[ix + old];
    curr += posdiagcnt[ix + neww]++;
}

void solve() {
    cin >> n;

    rowpos.resize(n);
    random_device rd;
    mt19937_64 mt(rd());
    uniform_int_distribution<ll> dist(0, n - 1);
    uniform_real_distribution<fl> fd;

    fl temp = 1;

    iota(rowpos.begin(), rowpos.end(), 0);
    shuffle(rowpos.begin(), rowpos.end(), mt);

    colcnt.assign(n, 0);
    for (ll i = 0; i < n; i++) {
        curr += colcnt[rowpos[i]]++;
    }
    negdiagcnt.assign(2*n, 0);
    for (ll i = 0; i < n; i++) {
        curr += negdiagcnt[n + i - rowpos[i]]++;
    }
    posdiagcnt.assign(2*n, 0);
    for (ll i = 0; i < n; i++) {
        curr += posdiagcnt[i + rowpos[i]]++;
    }

    temp = fl(curr) / fl(n*n);

    for (ll iter = 0;;iter++) {
        // if (iter % 10000 == 0) {
        //     cerr << "T " << temp << endl;
        //     cerr << "C " << curr << endl;
        // }
        ll ix = dist(mt);
        ll old = rowpos[ix];
        ll oldh = curr;
        upd(ix, dist(mt));

        if (curr == 0) break;

        if (!(fd(mt) < exp((oldh - curr) / temp))) {
            upd(ix, old);
        }

        temp *= 0.99999;
    }

    for (ll i = 0; i < n; i++) {
        cout << rowpos[i] + 1 << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
