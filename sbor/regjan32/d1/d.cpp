// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 5000;

ll nxt[maxn];
char nextcol[maxn];
vector<string> daun;

ll n, m, k;

void run(ll v, string &path) {
    if (path.size() >= m) {
        daun.push_back(path);
        return;
    }

    path.push_back(nextcol[v]);
    run(nxt[v], path);
}

void solve() {
    cin >> n >> m >> k;

    for (ll i = 0; i < n; i++) {
        char z;
        ll nx;
        cin >> nx >> z;
        nxt[i] = nx - 1;
        nextcol[i] = z;
    }

    for (ll i = 0; i < n; i++) {
        string s = "";
        run(i, s);
    }

    sort(daun.begin(), daun.end());

    cout << daun[k - 1] << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
