// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int INF = 2e9;
const int MAXN = 1e5 + 5;
const int MOD = 1e9;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int count(const vector<string> &a) {
    int n = (int)a.size() / 2;

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


void solve() {
    int n;
    cin >> n;

    vector<string> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }
    shuffle(a.begin(), a.end(), rnd);

    int ans = count(a);
    ld temp = 1;

    for (int it = 0;; ++it) {
        if (it % 10000 == 0) {
            cerr << count(a) << ' ' << temp << '\n';
        }
        int i = uniform_int_distribution<int>(0, 2 * n - 1)(rnd), j = uniform_int_distribution<int>(0, 2 * n - 1)(rnd);
        swap(a[i], a[j]);

        int cur = count(a);
        ld per = -20.0;

        if (uniform_real_distribution<ld>()(rnd) < exp((ans - cur) / temp)) {
            ans = cur;
            if (!ans) {
                break;
            }
        } else {
            swap(a[i], a[j]);
        }

        temp *= 0.9999999;
    }

    if (count(a) != 0) {
        cout << "GOVNOOOOOOOO\n";
    } else {
        for (int i = 0; i < n; ++i) {
            cout << a[i] << '\n';
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    int T = 1;
    cin >> T;
    while (T --> 0) {
        solve();
    }

    return 0;
}
