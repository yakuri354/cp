// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iomanip>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const fl eps = 1e-5;

struct pt {
    ll x, y;
};

struct obj {
    ll x, y, v;

    fl time_to(const pt& p) const {
        return sqrtl(powl(abs(x - p.x), 2) + powl(abs(y - p.y), 2)) / fl(v);
    }
};

ll n;

vector<obj> objs;
vector<pt> holes;

vector<vector<ll>> g;

vector<ll> mt, used;

bool kuhn(ll v, ll i) { // v - hole, u - obj
    if (used[v] == i) return false;
    used[v] = i;

    for (ll u : g[v]) {
        if (mt[u] == -1 || kuhn(mt[u], i)) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

bool check(fl t) {
    g.assign(n, vector<ll>());
    mt.assign(n, -1);
    used.assign(n, -1);

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (objs[i].time_to(holes[j]) <= t) {
                g[i].push_back(j);
            }
        }
    }

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ans += kuhn(i, i);
    }
    
    return ans == n;
}

void solve() {
    cin >> n;

    objs.resize(n);
    holes.resize(n);

    for (ll i = 0; i < n; i++) {
        cin >> objs[i].x >> objs[i].y >> objs[i].v;
    }

    for (ll i = 0; i < n; i++) {
        cin >> holes[i].x >> holes[i].y;
    }
    
    fl lo = 0, hi = 10001;
    while (hi - lo > eps) {
        fl m = (hi + lo) / 2;
        
        if (check(m)) hi = m;
        else lo = m;
    }
    
    cout << fixed << setprecision(5) << lo << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
