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

void solve() {
    string s, t;
    cin >> s >> t;

    const ll n = s.size(), m = t.size();

    if (n == 1) {
        cout << 1 << ' ' << t[0] << endl;
        return;
    }

    vector<ll> posl(n, m), posr(n, -1);

    for (ll i = 0, j = 0; i < n && j < m; i++, j++) {
        while (j < m && s[i] != t[j]) j++;
        posl[i] = j;
    }

    for (ll i = n - 1, j = m - 1; i >= 0 && j >= 0; i--, j--) {
        while (j >= 0 && s[i] != t[j]) j--;
        posr[i] = j;
    }

    for (ll i = 0; i < n - 2; i++) {
        for (ll j = posl[i] + 1; j < posr[i + 2]; j++) {
            if (t[j] != s[i+1]) {
                cout << i + 2 << ' ' << t[j] << endl;
                return;
            }
        }
    }

    for (ll j = posl[n - 2] + 1; j < m; j++) {
        if (t[j] != s[n-1]) {
            cout << n << ' ' << t[j] << endl;
            return;
        }
    }

    for (ll j = 0; j < posr[1]; j++) {
        if (t[j] != s[0]) {
            cout << 1 << ' ' << t[j] << endl;
            return;
        }
    }

    cout << "KAL" << endl;
    exit(-1);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

