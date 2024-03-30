// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <array>
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
using pll = pair<ll, ll>;

struct pt {
    ll i, j;
};

enum class dir {
    L = 0,
    R = 1,
    U = 2,
    D = 3,
    S = 4,
};

char to_c(dir d) {
    switch (d) {
        case dir::L: return 'L';
        case dir::R: return 'R';
        case dir::U: return 'U';
        case dir::D: return 'D';
        case dir::S: return 'S';
    }
}

const ll K = 5;

vector<dir> find_path(pt a, pt b) {
    vector<dir> ans;

    while (a.i != b.i) {
        if (a.i > b.i) {
            ans.push_back(dir::D);
            a.i--;
        } else if (a.i < b.i) {
            ans.push_back(dir::U);
            a.i++;
        }
    }

    while (a.j != b.j) {
        if (a.j > b.j) {
            ans.push_back(dir::L);
            a.j--;
        } else if (a.j < b.j) {
            ans.push_back(dir::R);
            a.j++;
        }
    }

    return ans;
}

void solve1() {
    ll n;
    cin >> n;

    vector<pt> pts(7);

    for (ll i = 0; i < 7; i++) {
        cin >> pts[i].i >> pts[i].j;
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            ll res = 0;
            ll kk = 1;
            for (ll x = 0; x < 7; x++) {
                pt a = {i, j};
                pt b = pts[x];
                auto move = dir::S;
                if (a.j > b.j) {
                    move = dir::L;
                } else if (a.j < b.j) {
                    move = dir::R;
                } else if (a.i > b.i) {
                    move = dir::D;
                } else if (a.i < b.i) {
                    move = dir::U;
                }
                res += ll(move) * kk;
                kk *= K;
            }
            cout << res << ' ';
        }
        cout << '\n';
    }
}

void solve2() {
    ll k0 = 1;
    for (ll x = 0; x < 7; x++) {
        while (true) {
            array<array<ll, 3>, 3> a;
            for (ll i = 0; i < 3; i++) {
                for (ll j = 0; j < 3; j++) {
                    cin >> a[i][j];
                }
            }

            auto d = dir((a[1][1] / k0) % K);

            cout << to_c(d) << endl;

            if (d == dir::S) break;
        }
        k0 *= K;
    }
}

// 39062 39062 39062 39062 39062 
// 39031 39034 39045 39100 39000 
// 35218 37093 34968 43843 31343 
// 27343 74218 11718 11718 11718 
// 58593 58593 58593 58593 58593

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    ll r, t;
    cin >> r >> t;
    while (t--) {
        if (r == 1) solve1();
        else solve2();
    }
}

