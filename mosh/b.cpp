// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<string> a;
ll n;

ll match(string x, string y) {
    ll ans = 0;
    for (ll i = 0; i < min(x.size(), y.size()); i++) {
        ans += x[i] == y[i];
    }
    return ans;
}

ll F() {
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != a[j + n][i]) {
                ++res;
            }
        }
    }
    return res;
}

fl P(fl t, fl delta) {
    cout << "t " << t << " d " << delta << " p " << expl(delta / t) << endl;
    return expl(delta / t);
}

random_device rd;
mt19937_64 mt(rd());

void solve() {
    cin >> n;

    for (ll i = 0; i < 2 * n; i++) {
        string s;
        cin >> s;
        a.push_back(s);
    }

    uniform_int_distribution<ll> dist(0, 2 * n - 1);
    uniform_real_distribution<fl> d2;
    fl temp = 10;
    for (ll it = 0;;it++) {
        if (it % 10000 == 0) {
            cerr << "ITER " << it << endl;
            cerr << "TEMP " << temp << endl;
            cerr << "STATE " << F() << endl;
        }
        ll s1 = dist(mt), s2 = dist(mt);
        while (s2 == s1) s2 = dist(mt);
        ll olds = F();
        swap(a[s1], a[s2]);
        ll news = F();

        if (news == 0) {
            cerr << "DONE" << endl;
            for (ll i = 0; i < n; i++) {
                cout << a[i] << '\n';
            }
            cout << endl;
        }

        if (d2(mt) < exp((olds - news) / temp)) {
            swap(a[s1], a[s2]);
        }

        temp *= 0.9999;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
        solve();
}
