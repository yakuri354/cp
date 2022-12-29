#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll maxn = 1e5*2;

pair<char, int> a[maxn];

bool cmp(const pair<char, int> &a, const pair<char, int> &b) {
    return a.first < b.first;
}

void solve() {
    string s;
    cin >> s;
    ll n = s.length();
    char fst = s[0], lst = s[n - 1];

    for (int i = 0; i < n; ++i) {
        a[i] = {s[i], i + 1};
    }

    sort(a, a + n, cmp);

    ll fp, lp;

    cout << abs(lst - fst) << ' ';

    if (lst >= fst) {
        fp = lower_bound(a, a + n, make_pair(fst, 0), cmp) - a;
        lp = upper_bound(a, a + n, make_pair(lst, 0), cmp) - a - 1;
        cout << lp - fp + 1 << endl;
        for (int i = fp; i <= lp; ++i) {
            cout << a[i].second << ' ';
        }
    }
    else {
        fp = upper_bound(a, a + n, make_pair(fst, 0), cmp) - a - 1;
        lp = lower_bound(a, a + n, make_pair(lst, 0), cmp) - a;
        cout << fp - lp + 1 << endl;
        for (int i = fp; i >= lp; --i) {
            cout << a[i].second << ' ';
        }
    }


    cout << endl;
}

int main() {
    ll t;
    cin >> t;

    while (t --> 0) solve();
}
