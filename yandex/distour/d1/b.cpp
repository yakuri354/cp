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

ll a[300][300];
ll n, m;

ll global(ll i, ll j) {
    return i * m + j;
}

void clockwise_next(ll &i, ll &j) {
    if (i == 0) {
        if (j == m - 1) {
            i++;
        } else {
            j++;
        }
    } else {
        if (j == 0) {
            i--;
        } else {
            j--;
        }
    }
}

void counterclockwise_next(ll &i, ll &j) {
    if (i == 0) {
        if (j == 0) { i++; }
        else { j--; }
    } else {
        if (j == m - 1) { i--; }
        else { j++; }
    }
}

template <typename F>
void tour(ll i, ll j, F f) {
    ll start = global(i, j), sum = 0;
    vector<pair<ll, ll>> pos;
    do {
        pos.push_back({i, j});
        sum += a[i][j];
        if (sum < 0) return;
        f(i, j);
    } while (global(i, j) != start);

    for (auto [x, y]: pos) {
        cout << x + 1 << ' ' << y + 1 << '\n';
    }

    exit(0);
}

struct pt {
    ll i, j;

    ll global() const {
        return i * m + j;
    }

    bool operator==(const pt &o) const {
        return i == o.i && j == o.j;
    }

    bool operator!=(const pt &o) const {
        return !(*this == o);
    }
};

void print_path(vector<pt> &path) {
    for (auto [i, j]: path) {
        cout << i + 1 << ' ' << j + 1 << '\n';
    }
}

pt go(pt from, pt to, vector<pt> &path) {
    while (from.i != to.i) {
        path.push_back(from);
        if (from.i < to.i) {
            from.i++;
        } else {
            from.i--;
        }
    }

    while (from.j != to.j) {
        path.push_back(from);
        if (from.j < to.j) {
            from.j++;
        } else {
            from.j--;
        }
    }

    return to;
}

void solve_for_2() {
    for (ll i = 0; i < 2; i++) {
        for (ll j = 0; j < m; j++) {
            tour(i, j, &clockwise_next);
            tour(i, j, &counterclockwise_next);
        }
    }

    cout << -1 << endl;
}

pair<bool, vector<pt>> fill2() {
    vector<pt> path;
    pt p = {0, 0};

    for (ll i1 = 0; i1 < n; i1++) {
        if (i1 % 2 == 0) {
            p = go(p, {i1, m - 1}, path);
            if (i1 + 1 < n) p = go(p, {i1 + 1, m - 1}, path);
        } else {
            p = go(p, {i1, 1}, path);
            if (i1 + 1 < n) p = go(p, {i1 + 1, 1}, path);
        }
    }

    if (p.j != 1) {
        return {false, {}};
    }

    p = go(p, {n - 1, 0}, path);
    p = go(p, {0, 0}, path);

    return {true, path};
}

pair<bool, vector<pt>> fill1() {
    vector<pt> path;
    pt p = {0, 0};

    for (ll j1 = 0; j1 < m; j1++) {
        if (j1 % 2 == 0) {
            p = go(p, {n - 1, p.j}, path);
            if (j1 + 1 < m) p = go(p, {p.i, p.j + 1}, path);
        } else {
            p = go(p, {1, p.j}, path);
            if (j1 + 1 < m) p = go(p, {p.i, p.j + 1}, path);
        }
    }

    if (p.i != 1) {
        return {false, {}};
    }

    p = go(p, {0, p.j}, path);
    p = go(p, {0, 0}, path);

    return {true, path};
}

void solve_pos() {
    if (m % 2 == 0) {
        auto [_, p1] = fill1();
        print_path(p1);
    } else {
        auto [_, p1] = fill2();
        print_path(p1);
    }
}

void solve() {
    cout << -1 << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    cin >> n >> m;

    if (n % 2 == 1 && m % 2 == 1) { // sus
        cout << -1 << endl;
        return 0;
    }

    ll negs = 0;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] < 0) negs++;
        }
    }

    if (n == 2) {
        solve_for_2();
    } else if (negs == 0) {
        solve_pos();
    } else {
        solve();
    }
}

