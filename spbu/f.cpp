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

void solve() {
    ll h, w;
    cin >> h >> w;

    vector<string> a;

    for (ll i = 0; i < h; i++) {
        string s;
        cin >> s;

        a.push_back(s);
    }

    ll ans = 0;
    for (ll i = 0; i < h; i++) {
        for (ll j = 0; j < w; j++) {
            if (j % 2 == 0 && j < w - 1) {
                ans += ll(a[i][j] - '0') * ll(a[i][j+1] - '0');
            }
        }
    }

    cout << ans << endl;

    for (ll i = 0; i < h; i++) {
        for (ll j = 0; j < w; j++) {
            if (j % 2 == 0 && j < w - 1) {
                cout << 'L';
            } else {
                cout << 'R';
            }
        }

        cout << '\n';
    }
    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

