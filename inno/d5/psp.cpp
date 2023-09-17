// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll maxn = 101;

ll d[maxn][maxn], p[maxn][maxn];

unordered_map<char, char> pc = {
    {'[', ']'},
    {'{', '}'},
    {'(', ')'}
};
string s;
ll n;

void print_seg(ll l, ll i) {
    if (l < 2 || i < 0 || i > n) return;
    if (p[l][i] == -1) {
        cout << s[i];
        print_seg(l - 2, i + 1);
        cout << pc[s[i]];
    } else if (l > 1) {
        print_seg(p[l][i] - i, i);
        print_seg(i + l - p[l][i], p[l][i]);
    }
}

void solve() {
    cin >> s;
    n = s.size();
    
    for (ll len = 2; len <= n; len++) {
        for (ll i = 0; i + len <= n; i++) {
            d[len][i] = -inf;
            for (ll j = i + 1; j < i + len; j++) {
                ll sum = d[j - i][i] + d[i + len - j][j];
                if (sum > d[len][i]) {
                    d[len][i] = sum;
                    p[len][i] = j;
                }
            }

            if (s[i + len - 1] == pc[s[i]]) {
                ll ext = d[len - 2][i + 1] + 2;
                if (ext > d[len][i]) {
                    d[len][i] = ext;
                    p[len][i] = -1;
                }
            }
        }
    }
    
    print_seg(n, 0);
    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
