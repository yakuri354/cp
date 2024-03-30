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

using col = array<ll, 50>;

vector<col> a;

ll N, M;

struct dsu {
    vector<ll> par = {0}, sz = {1};

    ll comps = 1;

    dsu() {}

    ll make_new() {
        par.push_back(par.size());
        sz.push_back(1);
        comps++;
        return par.size() - 1;
    }

    ll leader(ll x) {
        return x == par[x] ? x : (par[x] = leader(par[x]));
    }

    void unite(ll a, ll b) {
        a = leader(a), b = leader(b);

        if (a == b) return;

        if (sz[a] < sz[b]) swap(a, b);

        par[b] = a;
        sz[a] += sz[b];
        comps--;
    }
};

struct f_state {
    col head_l{}, head_r{};
    dsu d{};
    ll ix_l, ix_r;

    f_state(ll s) {
        ix_l = s, ix_r = s;
        // todo
    }

    void advance_right() {
        auto nc = a[ix_r++];

        for (ll i = 0; i < M; i++) {
            if (nc[i] == 0) continue;

            nc[i] = d.make_new();
            if (i > 0 && nc[i-1] != 0) d.unite(nc[i], nc[i-1]);
            if (head_r[i] != 0) d.unite(head_r[i], nc[i]);
        }

        head_r = nc;
    }

    void advance_left() {
        auto nc = a[--ix_l];

        for (ll i = 0; i < M; i++) {
            if (nc[i] == 0) continue;

            nc[i] = d.make_new();
            if (i > 0 && nc[i-1] != 0) d.unite(nc[i], nc[i-1]);
            if (head_l[i] != 0) d.unite(head_l[i], nc[i]);
        }

        head_l = nc;
    }

    ll cnt() {
        return d.comps - 1;
    }
};

ll dnc(ll l, ll r) {
    if (r <= l) return 0; 

    ll mid = (l + r) / 2;

    vector<ll> comp_l, comp_r;

    {
        f_state sl(mid);

        ll shit = sl.d.make_new();
        sl.head_l = a[mid];

        for (ll i = 0; i < M; i++) {
            if (sl.head_l[i] == 1) sl.head_l[i] = shit;
        }

        for (ll i = mid - 1; i >= l; i--) {
            sl.advance_left();
            comp_l.push_back(sl.cnt() - 1);
        }

        auto ml = a[mid-1];

        f_state midsl(mid);
        vector<ll> last(M, -1);

        for (ll i = 0; i < M; i++) {
            if (a[mid][i] && ml[i]) {
                ml[i] = midsl.d.make_new();
            }

            if (i > 0 && ml[i-1] != 0 && ml[i] != 0) {
                midsl.d.unite(ml[i], ml[i-1]);
            }
        }
    }

    {
        f_state sl(mid);

        ll shit = sl.d.make_new();
        sl.head_r = a[mid - 1];

        for (ll i = 0; i < M; i++) {
            if (sl.head_r[i] == 1) sl.head_r[i] = shit;
        }

        for (ll i = mid; i < r; i++) {
            sl.advance_right();
            comp_r.push_back(sl.cnt() - 1);
        }
    }

    auto ml = a[mid - 1], mr = a[mid];

    {

    }

}

ll dumb() {
    ll ans = 0;

    for (ll l = 0; l < N; l++) {
        f_state st(l);
        for (ll r = l + 1; r <= N; r++) {
            st.advance_right();
            // cout << l << " " << r << " -> " << st.cnt() << endl;
            ans += st.cnt();
        }
    }

    return ans;
}

void solve() {
    cin >> N >> M;

    a.resize(N);

    for (ll i = 0; i < N; i++) {
        string s;
        cin >> s;

        for (ll j = 0; j < M; j++) {
            a[i][j] = s[j] - '0';
        }
    }

    cout << dumb() << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

