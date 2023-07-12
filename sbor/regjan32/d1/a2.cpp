// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

struct dpe {
    ll xpl;
    ll ypl;
    ll m1x;
    ll m1y;
    ll msq;
};

const ll logn = 11;
const ll maxn = 2001;

bool s[maxn][maxn][logn + 1];

bool query(ll x, ll y, ll sz) {
    ll lg = __lg(sz);
    ll pw = 1 << lg;
    bool ans = s[x][y][lg];
    ans &= s[x + sz - pw][y][lg];
    ans &= s[x][y + sz - pw][lg];
    ans &= s[x + sz - pw][y + sz - pw][lg];
    return ans;
}

void solve() {
    ll n, m;
    cin >> n;
    m = n;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            char c;
            cin >> c;
            s[i][j][0] = c == '#';
        }
    }

    for (ll lg = 1; lg <= logn; lg++) {
        for (ll x = 0; x < n - (1 << lg) + 1; x++) {
            for (ll y = 0; y < m - (1 << lg) + 1; y++) {
                s[x][y][lg] = s[x][y][lg-1];
                s[x][y][lg] &= s[x + (1 << (lg - 1))][y][lg-1];
                s[x][y][lg] &= s[x][y + (1 << (lg - 1))][lg-1];
                s[x][y][lg] &= s[x + (1 << (lg - 1))][y + (1 << (lg - 1))][lg-1];
            }
        }
    }

    vector<pair<ll, pair<ll, ll>>> sqs;

    for (ll x = 0; x < n; x++) {
        for (ll y = 0; y < m; y++) {
            if (!s[x][y][0]) {
                // cerr << x << ' ' << y << " fastfail" << endl;
                continue;
            }
            ll lo = 1, hi = min(n - x, m - y) + 1;
            while (lo + 1 < hi) {
                ll m = (lo + hi) / 2;
                if (query(x, y, m)) {
                    lo = m;
                } else {
                    hi = m;
                }
            }
            sqs.emplace_back(lo, make_pair(x + 1, y + 1));
        }
    }

    sort(sqs.rbegin(), sqs.rend());


    if (sqs.size() == 1 || sqs[0].first > sqs[1].first) {
        cout << sqs[0].first << '\n';
        cout << sqs[0].second.first << ' ' << sqs[0].second.second << '\n';
        cout << sqs[0].second.first << ' ' << sqs[0].second.second << '\n';
    } else {
        ll liketop = 0;
        while (sqs[liketop].first == sqs[0].first) liketop++;
        const ll inf = 10000000;
        if (liketop > 2) {
            pair<ll, ll> lu = {inf, inf}, rd = {-inf, -inf};
            for (ll i = 0; i < liketop; i++) {
                lu = min(lu, sqs[i].second);
                rd = max(rd, sqs[i].second);
            }
            cout << sqs[0].first << '\n';
            cout << lu.first << ' ' << lu.second << '\n';
            cout << rd.first << ' ' << rd.second << '\n';
        } else {
            cout << sqs[0].first << '\n';
            cout << sqs[0].second.first << ' ' << sqs[0].second.second << '\n';
            cout << sqs[1].second.first << ' ' << sqs[1].second.second << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
