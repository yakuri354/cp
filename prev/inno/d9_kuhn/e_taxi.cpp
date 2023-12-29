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
const ll maxn = 500;

struct ride {
    ll time, x0, y0, x1, y1;
    
    ll len() const {
        return abs(x0 - x1) + abs(y0 - y1);
    }
    
    ll then_can(const ride &other) const {
        return time + len() + abs(x1 - other.x0) + abs(y1 - other.y0) < other.time;
    }
};

ride arr[maxn];

ll parse_time(string s) {
    auto it = s.find(':');
    return stoll(s.substr(0, it + 1)) * 60 +
        stoll(s.substr(it + 1));
}

vector<vector<ll>> g;
vector<ll> used, mt_b;

bool tyan(ll v, ll i) {
    if (used[v] == i) return false;
    used[v] = i;
    
    for (ll u : g[v]) {
        if (mt_b[u] == -1 || tyan(mt_b[u], i)) {
            mt_b[u] = v;
            return true;
        }
    }
    
    return false;
}

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        string time;
        cin >> time >> arr[i].x0 >> arr[i].y0 >> arr[i].x1 >> arr[i].y1;
        arr[i].time = parse_time(time);
    }
    
    g.resize(n);
    used.assign(n, -1);
    mt_b.assign(n, -1);
    
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (i != j && arr[i].then_can(arr[j])) {
                g[i].push_back(j);
            }
        }
    }
    
    ll total = 0;
    for (ll i = 0; i < n; i++) {
        total += tyan(i, i);
    }
    
    cout << n - total << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
