#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack>
#include <cmath>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <random>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <functional>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const ll INF = 1e9;
const ll MAXN = 2e5 + 5;
const ll MOD = 1e9 + 7;
const ll logn = 18;

//int a, b;
void solve() {
    map<char, ll> chars;
    chars['a'] = 1;
    chars['b'] = 5;
    chars['c'] = 10;
    chars['d'] = 50;
    chars['e'] = 100;
    chars['f'] = 200;
    chars['g'] = 500;
    chars['h'] = 1000;
    chars['i'] = 2500;
    chars['A'] = 500;
    chars['B'] = 1000;
    chars['C'] = 5000;
    chars['D'] = 10000;
    chars['E'] = 20000;
    chars['F'] = 50000;
    chars['G'] = 100000;
    chars['H'] = 200000;
    chars['I'] = 500000;

    int n;
    cin >> n;
    vector<ll> sums(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        ll cur = 0;
        for (int j = 0; j < (int)s.size(); ++j) {
            if ('0' <= s[j] && s[j] <= '9') {
                cur *= 10;
                cur += (s[j] - '0');
            } else {
                sums[i] += chars[s[j]] * cur;
                cur = 0;
            }
        }
    }

    ll mx = 0, itmx = 0, mn = 2e18, itmn = 0;
    for (int i = 0; i < n; ++i) {
        if (mx <= sums[i]) {
            mx = sums[i];
            itmx = i;
        }
        if (sums[i] <= mn) {
            mn = sums[i];
            itmn = i;
        }
    }

    cout << min(itmn, itmx) + 1 << '\n' << max(itmn, itmx) + 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef APPLE
    freopen("in", "r", stdin);
#endif

    ll T = 1;
//    cin >> T;
//    cin >> a >> b;
    while (T --> 0) {
        solve();
    }

    return 0;
}