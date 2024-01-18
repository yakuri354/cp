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
    ll n;
    cin >> n;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    ll maxv = *max_element(a.begin(), a.end()) + 2;

    vector<ll> div(maxv, -1);

    for (ll i = 2; i < maxv; i++) {
        if (div[i] != -1) continue;
        for (ll j = i; j < maxv; j += i) {
            if (div[j] == -1) {
                div[j] = i;
            }
        }
    }

    unordered_map<ll, vector<ll>> ds;

    for (ll i: a) {
        ll last_d = -1;
        ll cnt = 0;
        while (div[i] != -1) {
            if (last_d != div[i]) {
                if (last_d != -1) {
                    if (!ds.count(last_d)) {
                        ds[last_d] = vector<ll>(30, 0);
                    }
                    ds[last_d][cnt]++;
                }
                last_d = div[i];
                cnt = 0;
            }

            i /= div[i];
            cnt++;
        }

        if (last_d != -1) {
            if (!ds.count(last_d)) {
                ds[last_d] = vector<ll>(30, 0);
            }
            ds[last_d][cnt]++;
        }
    }

    ll ans = 0;
    for (auto &[d, v]: ds) {
        ll s1 = accumulate(v.begin(), v.end(), 0ll);
        v[0] += n - s1;

        ll prev = 0, res = 0;
        for (ll i = 0; i < v.size(); i++) {
            if (prev + v[i] > n / 2) {
                res = i;
                break;
            } else {
                prev += v[i];
            }
        }

        for (ll i = 0; i < v.size(); i++) {
            ans += v[i] * abs(i - res);
        }
    }


    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

