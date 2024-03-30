#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
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

struct cond {
    ll x;
    ll v;
};

template<typename T, ll sz>
struct smallvec {
    array<T, sz> arr;
    ll n = 0;

    void push_back(const T &v) {
        arr[n++] = v;
    }

    void remove(const T &v) {
        
    }
};

struct clause {
    array<optional<cond>, 3> c;
};

struct state {
    vector<clause> base, curr;
    vector<bool> assign, deduced;

    
};

ll n, m;


void sat(ll i, state &d) {
    if (i == n) {
        for (ll i = 0; i < n; i++) {
            cout << char(char(d.assign[i]) + '0');
        }
        cout << endl;
        exit(0);
    }

    
}

void solve() {
    cin >> n >> m;
    state.resize(n);

    for (ll i = 0; i < m; i++) {
        clause c;
        cin >> c.x1 >> c.v1 >> c.x2 >> c.v2 >> c.x3 >> c.v3;
        c.x1--;
        c.x2--;
        c.x3--;
        cl.push_back(c);
    }

    sat(0);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
