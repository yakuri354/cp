// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <string>
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

const ll maxh = 50 + 1;
const ll maxk = (1 << 5) + 1;

unordered_map<string, ll> d[maxh];

string m2s(ll m, ll sz) {
    string s(sz, 'a');

    for (ll i = 0; i < sz; i++) {
        s[i] = 'a' + ((m >> (sz - i - 1)) & 1);
    }

    return s;
}

void solve() {
    ll n;
    string S;

    cin >> S >> n;

    for (char &c: S) {
        if (c == 'A') c = 'a';
        if (c == 'B') c = 'b';
    }

    string Sr = S;
    reverse(Sr.begin(), Sr.end());

    ll pwr = S.size();

    ll h = n / 2;

    if (n <= 18) {
        ll ans = 0;

        for (ll m = 0; m < (1 << n); m++) {
            auto z = m2s(m, n);
            auto zr = z;
            reverse(zr.begin(), zr.end());

            if (z == zr && z.find(S) == string::npos) {
                ans++;
            }
        }

        cout << ans << endl;
        return;
    }

    for (ll m = 0; m < (1 << pwr); m++) {
        auto z = m2s(m, pwr);
        if (z == S || z == Sr) continue;
        d[S.size()][z] = 1;
    }

    for (ll i = S.size() + 1; i <= h; i++) {
        for (ll m = 0; m < (1 << pwr); m++) {
            auto z = m2s(m, pwr);
            if (z == S || z == Sr) {
                d[i][z] = 0;
            } else {
                auto prev = z.substr(0, z.size() - 1);

                d[i][z] = d[i-1]["a" + prev] + d[i-1]["b" + prev];
            }
        }
    }

    ll ans = 0;
    for (ll m = 0; m < (1 << pwr); m++) {
        ans += d[h][m2s(m, pwr)];
    }

    if (n % 2 == 0) {
        for (ll m1 = 0; m1 < (1 << pwr); m1++) { // ? /= 2
            auto z = m2s(m1, pwr);
            auto zr = z;
            reverse(zr.begin(), zr.end());

            auto joint = z + zr;

            if (joint.find(S) != string::npos || joint.find(Sr) != string::npos) { // SUS
                ans -= d[h][z];
            }
        }
    } else {
        ans *= 2;

        for (char ctr = 'a'; ctr <= 'b'; ctr++) {
            for (ll m1 = 0; m1 < (1 << pwr); m1++) { // ? /= 2
                auto z = m2s(m1, pwr);
                auto zr = z;
                reverse(zr.begin(), zr.end());

                auto joint = z + ctr + zr;

                if (joint.find(S) != string::npos || joint.find(Sr) != string::npos) { // SUS
                    ans -= d[h][z];
                }
            }
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

