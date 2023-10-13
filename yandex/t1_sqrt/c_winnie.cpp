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

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll k = 320;
const ll maxb = 2e9;

struct qr {
    ll l, r, x, y;
};

void solve() {
    ll n, m;
    cin >> n;
    vector<ll> a(n), b(n);

    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) cin >> b[i];
    
    cin >> m;
    
    vector<qr> qs(m);
    
    for (ll i = 0; i < m; i++) {
        cin >> qs[i].l >> qs[i].r >> qs[i].x >> qs[i].y;
        qs[i].l--;
    }
    
    vector<vector<int>> states(m / k + 2, vector<int>(n));
    
    vector<ll> dy(n + 1), ddy(n + 1);
    
    for (ll i = 0; i <= m; i++) {
        if (i % k == 0 || i == m) {
            vector<ll> dy2(n);
            
            ll curr = 0;
            for (ll j = 0; j < n; j++) {
                curr += ddy[j];
                dy2[j] = curr + dy[j];
            }
            
            ll curr2 = 0;
            for (ll j = 0; j < n; j++) {
                curr2 += dy2[j];

                states[i / k + (i % k != 0)][j] = min(maxb, curr2 + a[j]);
            }
            
            if (i == m) break;
        }

        dy[qs[i].l] += qs[i].x;
        dy[qs[i].r] -= qs[i].x;

        ddy[qs[i].l + 1] += qs[i].y;
        ddy[qs[i].r] -= qs[i].y;
        
        dy[qs[i].r] -= qs[i].y * (qs[i].r - qs[i].l - 1);
    }
    
    for (ll i = 0; i < n; i++) {
        ll lo = 0, hi = m / k + 1;
        
        while (hi - lo > 1) {
            ll mid = (lo + hi) / 2;

            if (states[mid][i] < b[i]) lo = mid;
            else hi = mid;
        }
        
        ll curr = states[lo][i];
        ll j = 0;
        for (;lo * k + j < m; j++) {
            if (curr >= b[i]) {
                cout << lo * k + j << ' ';
                goto next;
            }

            auto [l, r, x, y] = qs[lo * k + j];

            if (l <= i && i < r) {
                curr += x + y * (i - l);
            }
        }

        if (curr >= b[i]) {
            cout << lo * k + j << ' ';
            goto next;
        }

        cout << -1 << ' ';
        
        next:;
    }
    
    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
