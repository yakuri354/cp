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
using pll = pair<ll, ll>;

ll mod(ll x, ll m) {
    return ((x % m) + m) % m;
}

const ll M = 'z' - 'a' + 1;

bool dumb(vector<ll> s, vector<ll> t) {
    for (ll i = 0; i < s.size() - 1; i++) {
        ll delta = mod(t[i] - s[i], M);
        s[i] = mod(s[i] + delta, M);
        s[i+1] = mod(s[i+1] + delta, M);
    }

    return s.back() == t.back();
}

bool dumb2(vector<ll> s, vector<ll> t) {
    ll sum = 0;
    for (ll i = 0; i < s.size(); i++) {
        if (((s.size() - 1) - i) % 2 == 0) {
            sum = mod(sum + t[i] - s[i], M);
        } else {
            sum = mod(sum - t[i] + s[i], M);
        }
    }

    return sum == 0;
}

void solve() {
    ll n, q;
    cin >> n >> q;

    string _s, _t;
    cin >> _s >> _t;

    vector<ll> s(n), t(n);
    for (ll i = 0; i < n; i++) {
        s[i] = _s[i] - 'a';
        t[i] = _t[i] - 'a';
    }

    ll sum = 0;
    for (ll i = 0; i < s.size(); i++) {
        if (((n - 1) - i) % 2 == 0) {
            sum = mod(sum + t[i] - s[i], M);
        } else {
            sum = mod(sum - t[i] + s[i], M);
        }
    }
    
    if (sum == 0) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }

    for (ll i = 0; i < q; i++) {
        ll p;
        string c;
        cin >> p >> c;
        p--;

        //sum = mod(sum - (t[p] - s[p]), M);
        // sum = mod(sum + (t[p] - s[p]), M);

        if (((n - 1) - p) % 2 == 0) {
            sum = mod(sum - t[p] + s[p], M);
        } else {
            sum = mod(sum + t[p] - s[p], M);
        }

        s[p] = c[0] - 'a';

        if (((n - 1) - p) % 2 == 0) {
            sum = mod(sum + t[p] - s[p], M);
        } else {
            sum = mod(sum - t[p] + s[p], M);
        }

        if (sum == 0) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

