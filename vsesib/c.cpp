// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const fl eps = 1e-10;

struct ent {
    ll v, c, i;

    bool operator<(const ent &other) {
        return this->v < other.v;
    }
};

struct bs {
    ll len, cs, last;
};

ent a[5000];

void solve() {
    ll n, maxsi = -1, maxsl = -1, maxsc = inf, maxsj = -1;
    fl maxsq;
    cin >> n;

    vector<map<fl, bs>> d(n);

    for (ll i = 0; i < n; i++) {
        cin >> a[i].v;
        a[i].i = i;
    }

    for (ll i = 0; i < n; i++) {
        cin >> a[i].c;
    }

    sort(a, a + n);

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < i; j++) {
            fl q = fl(i)/fl(j);
            if (d[j].count(q)) {
                d[i][q].len = d[j][q].len + 1;
                d[i][q].cs = d[j][q].cs + a[i].c;
                d[i][q].last = j;
            } else {
                d[i][q] = {2, a[i].c + a[j].c};
                d[i][q].last = -1;
            }

            if (d[i][q].len > maxsl || (d[i][q].len == maxsl && d[i][q].cs < maxsc)) {
                maxsi = i;
                maxsj = j;
                maxsc = d[q][i].cs;
                maxsq = q;
            }
        }
    }

    vector<ll> ans;
    ll its = 0, lj = maxsj;
    ans.push_back(maxsi);

    while (lj != -1) {
        if (its > n * n * 10) assert(0);
        ans.push_back(a[lj].i);
        lj = d[lj][maxsq].last;
        its++;
    }

    cout << ans.size() << ' ' << maxsc << endl;
    
    reverse(ans.begin(), ans.end());
    for (ll i : ans) {
        cout << i + 1 << ' ';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
