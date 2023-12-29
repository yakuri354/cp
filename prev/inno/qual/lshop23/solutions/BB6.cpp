#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using ll = long long;

void resolve() {
    ll n;
    cin >> n;
    vector<ll> src(n);
    map<ll, ll> initPos;
    for (ll i = 0; i < n; ++i) {
        cin >> src[i];
        initPos[src[i]] = i;
    }

    sort(src.begin(), src.end());
    map<ll, ll> sortPos;
    for (ll i = 0; i < n; ++i) {
        sortPos[src[i]] = i;
    }

    ll wasOdd = 0;
    ll wasEven = 0;
    for (const auto& item : src) {
        if ((sortPos[item] & 1) == (initPos[item] & 1)) {
            continue;
        }

        if (sortPos[item] & 1) {
            ++wasEven;
        } else {
            ++wasOdd;
        }
    }

    cout << max(wasOdd, wasEven) << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    resolve();
    return 0;
}
