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

vector<ull> neck = {0ll, 2ll, 3ll, 4ll, 6ll, 8ll, 14ll, 20ll, 36ll, 60ll, 108ll, 188ll, 352ll, 632ll, 1182ll, 2192ll, 4116ll, 7712ll, 14602ll, 27596ll, 52488ll, 99880ll, 190746ll, 364724ll, 699252ll, 1342184ll, 2581428ll, 4971068ll, 9587580ll, 18512792ll, 35792568ll, 69273668ll, 134219796ll, 260301176ll, 505294128ll, 981706832ll, 1908881900ll, 3714566312ll, 7233642930ll, 14096303344ll, 27487816992ll, 53634713552ll, 104715443852ll, 204560302844ll, 399822505524ll, 781874936816ll, 1529755490574ll, 2994414645860ll, 5864062367252ll, 11488774559636ll, 22517998808028ll, 44152937528384ll, 86607686432616ll, 169947155749832ll, 333599974893066ll, 655069036708592ll, 1286742755471400ll, 2528336632928152ll, 4969489253251428ll, 9770521225481756ll, 19215358428046176ll};

void solve() {
    ull a, b, c;
    cin >> a >> b >> c;
    ull g1 = __gcd(a, b);
    cout << neck[g1] - neck[__gcd(c, g1)] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
