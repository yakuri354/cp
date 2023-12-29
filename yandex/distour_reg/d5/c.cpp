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

struct mergetree {
    ll n;
    vector<vector<ll>> t;

    explicit mergetree(vector<ll> &a) : n(a.size()), t(n * 2) {
        build(a);
    }

private: // sus
    ll less_cnt(vector<ll> &a, ll x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin();
    }

    ll more_cnt(vector<ll> &a, ll x) {
        return a.end() - upper_bound(a.begin(), a.end(), x);
    }

public:
    ll lessthan(ll l, ll r, ll x) {
        ll res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += less_cnt(t[l++], x);
            if (r & 1) res += less_cnt(t[--r], x);
        }
        return res;
    }

    ll morethan(ll l, ll r, ll x) {
        ll res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += more_cnt(t[l++], x);
            if (r & 1) res += more_cnt(t[--r], x);
        }
        return res;
    }

private:
    void build(vector<ll> &a) {
        for (ll i = 0; i < n; i++) {
            t[n + i] = {a[i]};
        }
        for (ll i = n - 1; i > 0; i--) {
            t[i].resize(t[i*2].size() + t[i*2+1].size());
            merge(t[i*2].begin(), t[i*2].end(), t[i*2+1].begin(), t[i*2+1].end(), t[i].begin());
        }
    }
};

vector<ll> calc(vector<ll> a) { // copy sus
    ll n = a.size();
    a.resize(n * 2);
    copy(a.begin(), a.begin() + n, a.begin() + n);

    auto t = mergetree(a);

    ll invs = 0; // slow sus
    for (ll i = 1; i < n; i++) {
        invs += t.morethan(0, i, a[i]);
    }

    vector<ll> ans(n);
    ans[0] = invs;

    for (ll i = 0; i + 1 < n; i++) {
        invs -= t.lessthan(i + 1, i + n, a[i]);
        invs += t.morethan(i + 1, i + n, a[i + n]);
        ans[i+1] = invs;
    }

    return ans;
}

void solve() {
    ll n;
    cin >> n;

    vector<ll> data[6];

    for (ll i = 0; i < n; i++) {
        string s;
        cin >> s;

        for (ll j = 0; j < 6; j++) {
            data[j].push_back(s[j] - '0');
        }
    }

    vector<ll> ans[6];
    for (ll i = 0; i < 6; i++) {
        ans[i] = calc(data[i]);
    }

    vector<ll> full(n);

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < 6; j++) {
            full[i] += ans[j][i];
        }
    }

    cout << *min_element(full.begin(), full.end()) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

