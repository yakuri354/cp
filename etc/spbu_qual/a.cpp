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

ll w, h, x1, y_1, x2, y2;

ll f() {
    ll d1 = abs(x1 - x2) + abs(y_1 - y2);
    // x1 -> w - 1 ; y1 -> h - y1 - 1
    ll d2 = x1 + 1 + abs(w - 1 - x2) + abs(h - y_1 - 1 - y2);
    // x1 -> w - 1 - x1 ; y1 -> h - 1
    ll d3 = y_1 + 1 + abs(w - 1 - x1 - x2) + abs(h - 1 - y2);

    return min(d1, min(d2, d3));
}

void solve() {
    cin >> w >> h >> x1 >> y_1 >> x2 >> y2;

    x1--, y_1--, x2--, y2--;

    ll ans = f();
    swap(x1, x2);
    swap(y_1, y2);
    ans = min(ans, f());

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

