// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

const ll inf = INT32_MAX;
const ll maxn = 301;

string s;
ll d[maxn][maxn];
pair<ll, ll> p[maxn][maxn];

void solve() {
    ll n;
    cin >> n >> s;
    
    for (ll l = 1; l <= n; l++) {
        for (ll i = 0; i + l <= n; i++) {
            if (l == 1) {
                d[l][i] = 1;
                continue;
            }
            
            if (s[i] == s[i+1]) {
                if (d[i+1][l-1])
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
