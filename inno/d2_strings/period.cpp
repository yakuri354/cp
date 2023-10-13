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
    string s;
    cin >> s;
    ll n = s.size();

    auto p = pf(s);

    ll z = s.size() - p.back();
    if (s.size() % z != 0) z = s.size();

    cout << z << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
