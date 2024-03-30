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

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

struct node {
    ll cnt = 0, sum = 0;
};

node cmb(node l, node r) {
    return {l.cnt + r.cnt, l.sum + r.sum};
}

struct segt {
    ll n;
    vector<node> t;

    segt(ll n): n(n), t(n * 4) {}

    void modify(ll p, ll val, ll cnt) {
        p += n;
        t[p] = cmb(t[p], {cnt, val});
        for (p /= 2; p > 0; p /= 2) t[p] = cmb(t[p*2], t[p*2+1]);
    }

    node get(ll l, ll r) {
        node res = {0, 0};
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) res = cmb(res, t[l++]);
            if (r & 1) res = cmb(res, t[--r]);
        }
        return res;
    }
};

vector<ll> a;

vector<ll> diff;
vector<ll> diffs = {0};

vector<ll> ans;

void solve() {
    ll n, q;
    cin >> n >> q;

    a.resize(n);
    for (ll& i : a)
        cin >> i;

    vector<pll> ai;

    for (ll i = 0; i < n; i++) ai.push_back({a[i], i});

    sort(a.begin(), a.end());
    sort(ai.begin(), ai.end());

    vector<ll> perma(n);
    for (ll i = 0; i < n; i++) {
        perma[ai[i].second] = i;
    }

    vector<ll> diff(n, 0);
    vector<ll> diffs = {0};
    vector<pll> diff_ixs;

    for (ll i = 1; i < n; i++) {
        diff[i] = a[i] - a[i-1];
        if (diff[i] != 0) {
            diffs.push_back(diff[i]);
        }
        diff_ixs.push_back({diff[i], i});
    }
    diff_ixs.push_back({0, n});

    sort(diff_ixs.begin(), diff_ixs.end());

    vector<ll> diff_pref_left(n + 1, 0);
    for (ll i = 1; i <= n; i++) {
        diff_pref_left[i] = diff_pref_left[i-1] + diff_ixs[i-1].first * diff_ixs[i-1].second;
    }

    vector<ll> diff_pref_right(n + 1, 0);
    for (ll i = n - 1; i >= 0; i--) {
        diff_pref_right[i] = diff_pref_right[i+1] + diff_ixs[i].second;
    }

    sort(diffs.begin(), diffs.end());

    auto solve_t1 = [&](ll k) -> ll {
        if (k == 0) return diffs.size();
        
        return diffs.end() - upper_bound(diffs.begin(), diffs.end(), k) + 1;
    };

    auto solve_t2 = [&](ll k) -> ll {
        if (k == 0) return 0;

        auto bnd = upper_bound(diff_ixs.begin(), diff_ixs.end(), pll{k, 100000000000000ll}) - diff_ixs.begin();
        ll ans = diff_pref_left[bnd] + diff_pref_right[bnd] * k;
        return ans;
    };

    // diffs.erase(unique(diffs.begin(), diffs.end()), diffs.end());

    ans.resize(q);

    vector<tuple<ll, ll, ll>> t3qs;

    for (ll qi = 0; qi < q; qi++) {
        ll qty, k;
        cin >> qty >> k;

        if (qty == 1) {  // OK
            ans[qi] = solve_t1(k);
        }

        if (qty == 2) {
            ans[qi] = solve_t2(k);
        }

        if (qty == 3) {
            ll i;
            cin >> i;
            i--;
            t3qs.push_back({perma[i], k, qi});
        }
    }

    diffs.erase(unique(diffs.begin(), diffs.end()), diffs.end());

    if (!t3qs.empty()) {
        sort(t3qs.begin(), t3qs.end(), greater<>());

        unordered_map<ll, ll> difi;
        for (ll i = 0; i < diffs.size(); i++) {
            difi[diffs[i]] = i;
        }

        segt t(difi.size() + 1);

        ll l = n;
        for (auto [p, k, qi]: t3qs) {
            while (p < l) {
                l--;
                if (diff[l] > 0) t.modify(difi[diff[l]], diff[l], 1);
            }

            ll bnd = upper_bound(diffs.begin(), diffs.end(), k) - diffs.begin();
            ans[qi] = a[p] + t.get(0, bnd).sum + t.get(bnd, difi.size() + 1).cnt * k;
        }
    }

    for (ll qi = 0; qi < q; qi++) {
        cout << ans[qi] << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
