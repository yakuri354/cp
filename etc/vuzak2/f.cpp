// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

struct entry {
    ll x;
    ll sz;
    ll hits = 0;

    entry(ll x, ll sz) : x(x), sz(sz) {
    }

    bool operator<(const entry& y) const {
        return x < y.x;
    }
};

map<ll, vector<entry>> horizontal, vertical;

enum class result {
    MISS = 0,
    HIT = 1,
    SINK = 2,
};

result try_vert(ll x, ll y) {
    if (horizontal.count(y) == 0)
        return result::MISS;

    auto e =
        upper_bound(horizontal[y].begin(), horizontal[y].end(), entry(x, 0));

    if (e == horizontal[y].begin())
        return result::MISS;
    e--;
    if (e == horizontal[y].end() || e->x + e->sz <= x)
        return result::MISS;

    e->hits++;

    if (e->hits >= e->sz) {
        return result::SINK;
    } else {
        return result::HIT;
    }
}

result try_vertical(ll x, ll y) {
    if (vertical.count(x) == 0)
        return result::MISS;

    auto e = upper_bound(vertical[x].begin(), vertical[x].end(), entry(y, 0));

    if (e == vertical[x].begin())
        return result::MISS;
    e--;
    if (e == vertical[x].end() || e->x + e->sz <= y)
        return result::MISS;

    e->hits++;

    if (e->hits >= e->sz) {
        return result::SINK;
    } else {
        return result::HIT;
    }
}

void solve() {
    ll n, k, q;
    cin >> n >> k >> q;

    set<pair<ll, ll>> hits;

    for (ll i = 0; i < k; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 == x2 && y1 == y2) {
            vertical[x1].push_back(entry(y1, 1));
        } else if (x1 == x2) {
            vertical[x1].push_back(entry(min(y1, y2), abs(y1 - y2) + 1));
        } else if (y1 == y2) {
            horizontal[y1].push_back(entry(min(x1, x2), abs(x1 - x2) + 1));
        } else {
            exit(-1);
        }
    }

    for (auto& [k, v] : horizontal) {
        sort(v.begin(), v.end());
    }

    for (auto& [k, v] : vertical) {
        sort(v.begin(), v.end());
    }

    for (ll i = 0; i < q; i++) {
        ll x, y;
        cin >> x >> y;

        if (hits.count({x, y})) {
            cout << "REPEAT\n";
            continue;
        }

        hits.insert({x, y});

        auto hh = try_vertical(x, y);
        if (hh == result::MISS)
            hh = try_vert(x, y);

        if (hh == result::MISS) {
            cout << "MISS\n";
        } else if (hh == result::HIT) {
            cout << "HIT\n";
        } else if (hh == result::SINK) {
            cout << "SINK\n";
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
