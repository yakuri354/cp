// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <iterator>
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

const ll inf = 1ll << 50;

vector<ll> t;
ll n;

void modify(ll i, ll v) {
    t[i += n] = v;
    
    for (i /= 2; i > 0; i /= 2) {
        t[i] = min(t[i * 2], t[i * 2 + 1]);
    }
}

ll query(ll l, ll r) {
    ll ans = inf;
    
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ans = min(ans, t[l++]);
        if (r & 1) ans = min(ans, t[--r]);
    }
    
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 > x2 || (x1 == x2 && y1 > y2)) {
            swap(x1, x2);
            swap(y1, y2);
        }

        if (!(x1 == 0 && y1 == k) && !(x1 == k && y1 == 0)) {
            if ((x1 + y1 + x2 + y2 - 2 * k) % 2) {
                cout << "Petr\n";
            } else {
                cout << "Maria\n";
            }
            continue;
        }

        if (x1 == 0 && y1 == k) {
            
        }
        ]
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
