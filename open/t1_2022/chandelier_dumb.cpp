// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <ctime>
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

ll n, m, k1;
vector<ll> a, b;

ll solve_dumb() {
    ll k = k1;
    ll ans = 0;

    for (ll i = 0, j = 0; k > 0; i = (i + 1) % n, j = (j + 1) % m) {
        if (a[i] != b[j]) k--;
        ans++;
    }

    return ans;
}

ll solve() {
    ll k = k1;
    k--;

    ll maxa = 2 * n;

    vector<ll> ainv(maxa), binv(maxa);
    vector<bool> in_b(maxa);
    for (ll i = 0; i < n; i++) {
        ainv[a[i]] = i;
    }

    for (ll i = 0; i < m; i++) {
        binv[b[i]] = i;
        in_b[b[i]] = true;
    }

    ll g = __gcd(ull(n), ull(m));
    ll P = (n * m) / g;

    vector<ll> from(n, m);

    for (ll i = 0; i < n; i++) {
        if (in_b[a[i]]) {
            from[mod(i-binv[a[i]], n)]--;
        }
    }

    ll period_cnt = 0;

    // for (ll i = 0; i < n; i += g) {
    //     period_cnt += from[i];
    // }

    {
        ll i = mod(m, n);
        period_cnt += from[0];
        while (i != 0) {
            period_cnt += from[i];
            i = mod(i + m, n);
        }
    }

    ll ans = 0;

    ans += P * (k / period_cnt);
    k %= period_cnt;

    // while (k >= period_cnt) {
    //     k -= period_cnt;
    //     ans += P;
    // }

    ll i = 0;
    while (k >= from[i]) {
        k -= from[i];
        ans += m;
        i = mod(i + m, n);
    }

    for (ll j = i, bj = 0; k > 0; j = mod(j + 1, n), bj++) {
        ans++;
        if (a[j] != b[bj]) k--;
    }

    return ans + 1;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    mt19937_64 mt(random_device{}());

    ll tot = 500;

    vector<ll> vs(tot);
    iota(vs.begin(), vs.end(), 0);

    for (ll it = 0;; it++) {
        if (it % 10000 == 0) {
            cout << it << endl;
        }
        a.resize(uniform_int_distribution<ll>(1, tot - 1)(mt));
        b.resize(tot - a.size());

        n = a.size();
        m = b.size();

        if (n < m) {
            swap(n, m);
            swap(a, b);
        }

        shuffle(vs.begin(), vs.end(), mt);
        copy(vs.begin(), vs.begin() + n, a.begin());
        copy(vs.begin() + n, vs.end(), b.begin());

        k1 = uniform_int_distribution<ll>(1, 100)(mt);

        if (solve_dumb() != solve()) {
            cout << "PROLAPS" << endl;
            cout << solve_dumb() << endl;
            cout << solve() << endl;
        }
    }
}

