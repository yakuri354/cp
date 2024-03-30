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
#include <array>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll lg = 20;

struct node {
    array<node *, lg> up{};
    ll x;

    node() : up(), x(0) {
        up.fill(this);
    }

    node(ll x, node *p): up(), x(x) {
        up[0] = p;
        for (ll i = 1; i < lg; i++) {
            up[i] = up[i-1]->up[i-1];
        }
    }

    node *la(ll n) {
        node *x = this;
        for (ll i = lg - 1; i >= 0; i--) {
            if ((n >> i) & 1) {
                x = x->up[i];
            }
        }
        return x;
    }
};

vector<node*> a;
vector<ll> sz;

void solve() {
    ll n;
    cin >> n;

    a.push_back(new node());
    sz.push_back(0);

    for (ll i = 0; i < n; i++) {
        ll ty, x, m;
        cin >> ty >> x;

        if (ty == -1) {
            cout << a[x]->la(sz[x] - 1)->x << '\n';
            if (sz[x] == 1) {
                a.push_back(new node());
                sz.push_back(0);
            } else {
                a.push_back(a[x]);
                sz.push_back(sz[x] - 1);
            }
        }

        if (ty == 1) {
            cin >> m;

            a.push_back(new node(m, a[x]));
            sz.push_back(sz[x] + 1);
        }
    }

    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

