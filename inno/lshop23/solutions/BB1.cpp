#include <iostream>
#include <map>
#include <set>

using namespace std;
using ll = long long;

void resolve() {
    ll n, len;
    cin >> n >> len;
    map<string, ll> cnt;
    for (ll i = 0; i < n; ++i) {
        string src;
        cin >> src;
        ++cnt[src];
    }

    ll q;
    cin >> q;
    while (q--) {
        ll res = 0;
        string target;
        cin >> target;
        set<string> checked;
        res += cnt[target.substr(1)];
        checked.insert(target.substr(1));
        if (checked.find(target.substr(0, len)) == checked.end()) {
            res += cnt[target.substr(0, len)];
            checked.insert(target.substr(0, len));
        }

        for (ll i = 1; i < len; ++i) {
            if (checked.find(target.substr(0, i) + target.substr(i + 1)) == checked.end()) {
                res += cnt[target.substr(0, i) + target.substr(i + 1)];
                checked.insert(target.substr(0, i) + target.substr(i + 1));
            }
        }

        cout << res << '\n';
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    resolve();
    return 0;
}
