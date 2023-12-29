#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

bool check(const vector<ll>& src, ll len) {
    ll lst = -2;
    for (ll i = 0; i < ll(src.size()); ++i) {
        if (src[i] <= len) {
            continue;
        }

        if (lst == i - 1) {
            return false;
        }

        lst = i;
    }

    return true;
}

void resolve() {
    ll n;
    cin >> n;
    vector<ll> src(n);
    for ( auto& item : src) {
        string in;
        cin >> in;
        item = ll(in.length());
    }

    ll l = 0;
    ll r = 101;
    while (r - l > 1) {
        ll m = (l + r) >> 1;
        if (check(src, m)) {
            r = m;
        } else {
            l = m;
        }
    }

    cout << r;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    resolve();
    return 0;
}
