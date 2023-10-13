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
#include <cmath>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

const fl pi = 3.14159265359;

void solve() {
    fl a, b, c;

    cout << "? 90" << endl;
    cin >> c;
    
    cout << "? 0" << endl;
    cin >> a;
    
    cout << "? 180" << endl;
    cin >> b;


    fl ac = hypotl(a, c);
    fl bc = hypotl(b, c);

    fl ang = acosl((ac * ac + bc * bc - (a + b) * (a + b)) / (2 * ac * bc));
    
    fl alpha;
    if (ang >= pi / 2) {
        alpha = (pi - ang) * 2;
    } else {
        alpha = ang * 2;
    }

    fl r = (a + b) / (2 * sinl(alpha / 2));
    
    cout << "! " << ll(roundl(r)) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
