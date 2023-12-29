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

struct node {
    unordered_map<ll, ll> p;

    ll operator()(ll x) {
        if (p.count(x)) return p[x];
        else return x;
    }
};

using el = node;
const el el_id = {{}};

vector<el> st;
ll N;
vector<ll> lp, rp;
 
ll query(ll l, ll r, ll x) {
    lp.clear(), rp.clear();
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) lp.push_back(l++);
        if (r & 1) rp.push_back(--r);
    }
    for (ll i : lp) {
        x = st[i](x);
    }
    reverse(rp.begin(), rp.end());
    for (ll i : rp) {
        x = st[i](x);
    }
    return x;
}
 
void set_el(ll i, pair<ll, ll> sw) {
    

}

ll n, m, q;

void solve_2() {
    lp.reserve(n);
    rp.reserve(n);
    st.resize(m * 2, 0);

    N = m;

    for (ll i = 0; i < q; i++) {
        ll ty;
        cin >> ty;

        if (ty == 0) {
            ll a, b, x;
            cin >> a >> b >> x;
            x--;

            set_el(x, st[m + x] ^ (a != b));
        } else {
            ll r, x;
            cin >> r >> x;
            r--, x--;
            
            cout << 1 + (r ^ query(0, x + 1)) << endl;
        }
    }
}

void solve_dumb() {
    vector<vector<pair<ll, ll>>> arr;
    arr.resize(m);
    for (ll i = 0; i < q; i++) {
        ll ty;
        cin >> ty;

        if (ty == 0) {
            ll a, b, x;
            cin >> a >> b >> x;
            x--;
            a--, b--;

            arr[x].push_back({a, b});
        } else {
            ll r, x;
            cin >> r >> x;
            r--, x--;
            
            for (ll i = 0; i <= x; i++) {
                for (auto &[a, b]: arr[i]) {
                    if (r == a) r = b;
                    if (r == b) r = a;
                }
            }

            cout << r + 1 << '\n';
        }
    }
}

void solve() {
    cin >> n >> m >> q;

    if (n == 2) solve_2();
    else solve_dumb();
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

