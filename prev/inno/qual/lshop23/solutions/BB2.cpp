#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

ll calc(const string& src, string target) {
    ll need = ll(target.length());
    target += '#';
    target += src;
    ll n = ll(target.length());
    vector<ll> z(n);
    for (ll i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && target[z[i]] == target[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }

    ll res = 0;
    for (ll i = need + 1; i < target.length(); ++i) {
        res += z[i] >= need;
    }
    return res;
}

void resolveTest() {
    string src;
    string target;
    cin >> src >> target;
    pair<ll, ll> res = {0, 0};
    ll n = ll(src.length());
    for (ll k = 1; k <= n; ++k) {
        string have;
        for (ll i = 0; i < n; i += k) {
            have += src[i];
        }

        if (have.length() < target.length()) {
            break;
        }

        res = max(res, {calc(have, target), -k});
    }

    cout << -res.second << '\n';
}

void resolve() {
    ll testN;
    cin >> testN;
    while (testN--) {
        resolveTest();
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    resolve();
    return 0;
}
