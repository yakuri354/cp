#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <bitset>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 5000;

bitset<maxn> rr[maxn], rb[maxn], g[maxn], stack, used;

ll n;

void dfsr(ll v) {
    used[v] = true;
    rr[v] |= stack;
    stack[v] = true;

    for (ll i = v + 1; i < n; i++) {
        if (g[v][i]) dfsr(i);
    }

    stack[v] = false;
}

void dfsb(ll v) {
    used[v] = true;
    rb[v] |= stack;
    stack[v] = true;

    for (ll i = v + 1; i < n; i++) {
        if (!g[v][i]) dfsb(i);
    }

    stack[v] = false;
}


void solve() {
    cin >> n;

    for (ll i = 0; i < n - 1; i++) {
        string l;
        cin >> l;

        for (ll j = 0; j < l.size(); j++) {
            if (l[j] == 'R') {
                g[i][i + j + 1] = true;
            }
        }
    }
    
    used &= 0;
    for (ll i = 0; i < n; i++) {
        if (!used[i]) {
            dfsr(i);
        }
    }

    used &= 0;
    for (ll i = 0; i < n; i++) {
        if (!used[i]) {
            dfsb(i);
        }
    }

    for (ll i = n - 1; i >= 0; i--) {
        if ((rr[i] & rb[i]).any()) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

