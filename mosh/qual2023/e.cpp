// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
#include <regex>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

enum {
    VAL = 1, SUM = 2, MIN = 3
};

struct ent {
    ll ty, ax, ay, bx, by, v;
};
vector<vector<ent>> a;

ll eval(ll x, ll y) {
    if (a[x][y].ty == VAL) return a[x][y].v;

    ll l = eval(a[x][y].ax, a[x][y].ay);
    ll r = eval(a[x][y].bx, a[x][y].by);

    if (a[x][y].ty == MIN) a[x][y].v = min(l, r);
    if (a[x][y].ty == SUM) a[x][y].v = l + r;
    a[x][y].ty = VAL;

    return a[x][y].v;
}

void solve() {
    ll h, w;
    cin >> h >> w;
    a.assign(h, vector<ent>(w));

    for (ll i = 0; i < h; i++) {
        for (ll j = 0; j < w; j++) {
            string zz;
            cin >> zz;
            a[i][j] = {VAL, -1, -1, -1, -1, 0}; 
            if (zz[0] != '=') {
                a[i][j] = {VAL, -1, -1, -1, -1, stoll(zz)};
                continue;
            } 

            char ax, bx;
            if (zz[1] == 'M' && zz[2] == 'I') {
                a[i][j].ty = MIN;
                sscanf(zz.c_str(), "=MIN(%c%lld;%c%lld)", &ax, &a[i][j].ay, &bx, &a[i][j].by);
            } else {
                a[i][j].ty = SUM;
                sscanf(zz.c_str(), "=%c%lld+%c%lld", &ax, &a[i][j].ay, &bx, &a[i][j].by);
            }
            a[i][j].ax = ax - 'A';
            a[i][j].bx = bx - 'A';
            a[i][j].ay -= 1;
            a[i][j].by -= 1;

            swap(a[i][j].ax, a[i][j].ay);
            swap(a[i][j].bx, a[i][j].by);
        }
    }

    for (ll i = 0; i < h; i++) {
        for (ll j = 0; j < w; j++) {
            cout << eval(i, j) << ' ';
        }
        cout << '\n';
    }

    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
        solve();
}
