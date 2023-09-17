// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<ll> pf(string_view s) {
    vector<ll> p(s.size(), 0);

    for (ll i = 1; i < s.size(); i++) {
        ll cur = p[i-1];

        while (s[i] != s[cur] && cur > 0) {
            cur = p[cur - 1];
        }

        p[i] = cur + (s[i] == s[cur]);
    }

    return p;
}

void solve() {
    string s, t;
    cin >> s >> t;

    string z = s + "#" + t;

    auto p = pf(z);

    vector<ll> ans;
    for (ll i = 0; i < z.size(); i++) {
        if (p[i] == s.size()) ans.push_back(i - s.size() * 2 + 1);
    }

    cout << ans.size() << endl;

    for (ll x : ans) cout << x << ' ';
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
