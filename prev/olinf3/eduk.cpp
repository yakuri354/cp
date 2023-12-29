#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAX_N = 2 * 1e5;
ll a[MAX_N];
ll prefs[MAX_N];
int main() {
    ll T;
    cin >> T;
    for (ll rep = 0; rep < T; rep++) {
        ll N, ans = 0, max;
        cin >> N >> max;
        for (ll i = 0; i < N; i++) cin >> a[i];
        sort(a, a + N);
        prefs[0] = a[0];
        for (ll i = 1; i < N; ++i) {
            prefs[i] = a[i] + prefs[i-1];
        }
        for (ll i = N - 1; i >= 0; --i) {
           if (prefs[i] <= max) {
               ans += (max - prefs[i]) / (i + 1) + 1;
           }
        }
        cout << ans << '\n';
        next_rep:;
    }
}