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
#include <deque>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = 1ll << 50;

struct segt_min {
    ll n;
    vector<ll> t;

    segt_min(ll n): n(n), t(n * 2) { }
    segt_min(vector<ll> &a): n(a.size()), t(n * 2) {
        copy(a.begin(), a.end(), t.begin() + n);
        for (ll i = n - 1; i > 0; i--) {
            t[i] = min(t[i * 2], t[i * 2 + 1]);
        }
    }

    ll query(ll l, ll r) {
        ll res = inf;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, t[l++]);
            if (r & 1) res = min(res, t[--r]);
        }
        return res;
    }
};

struct segt_max {
    ll n;
    vector<ll> t;

    segt_max(ll n): n(n), t(n * 2) { }
    segt_max(vector<ll> &a): n(a.size()), t(n * 2) {
        copy(a.begin(), a.end(), t.begin() + n);
        for (ll i = n - 1; i > 0; i--) {
            t[i] = max(t[i * 2], t[i * 2 + 1]);
        }
    }

    ll query(ll l, ll r) {
        ll res = inf;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }
};

string s;

bool check(vector<string> &ans) {
    string t;
    for (auto &s: ans) t += s;
    if (t != s) {
        return false;
        // exit(-1);
    }

    volatile ull x = 0;
    if (ans[1] <= ans[0] && ans[1] <= ans[2]) return true;
    if (ans[1] >= ans[0] && ans[1] >= ans[2]) return true;

    // while (true) x++;
    return false;
}

void solve() {
    cin >> s;

    ll n = s.size();

    vector<ll> sv(s.begin(), s.end());

    vector<string> ans;

    if (s[1] == s[0]) {
        cout << s[0] << ' ' << s[1] << ' ' << s.substr(2, n - 2) << endl;
        return;
    }

    for (ll i = 1; i < 10; i++) {
        for (ll j = 1; 1 + i + j <= n; j++) {
            string s1 = string{s[0]};
            string s2 = s.substr(1, i);
            string s3 = s.substr(1 + i, n - 1 - i);
            if (s1 <= s2 && s2 >= s3 || ) {
                cout << s1 << ' ' << s2 << ' ' << s3 << endl;
            }
        }
    }

    fail: cout << ":(" << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

