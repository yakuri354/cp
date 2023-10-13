// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <ostream>
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

void solve() {
    ll k;
    cin >> k;

    ull f;
    cin >> f;

    ull sign_mask = 1ull << 63ull;
    ll sign = (f & sign_mask) > 0ull;

    ull mantissa_mask = (1ull << k) - 1ull;
    ll mantissa = f & mantissa_mask;
    
    ull p_mask = ~(mantissa_mask) & ~(sign_mask);
    ll p = (f & p_mask) >> k;
    
    // cerr << endl;
    // cerr << "f        " << bitset<64>(f) << endl;
    // cerr << "sign     " << sign << endl;
    // cerr << "mantissa " << bitset<64>(mantissa) << " -> " << mantissa << endl;
    // cerr << "p        " << bitset<64>(p << k) << " -> " << p << endl;
    
    if (p == (p_mask >> k)) {
        cout << "NaN" << endl;
        return;
    }
    
    ll pwr = 0, fac = 0;
    
    if (p == 0) {
        pwr = 1ll - k - (1ll << (62 - k));
        fac = ll(mantissa);
    } else {
        ll x = p + 1ll - (1ll << (62 - k));
        
        pwr = x - k;
        
        fac = mantissa + (1ll << k);
    }

    if (fac == 0) {
        cout << 0 << endl;
        return;
    }

    while ((fac & 1) == 0 && fac > 0) {
        pwr++;
        fac >>= 1;
    }

    if (sign == 1) {
        cout << "-";
    }
    
    
    cout << fac;

    if (pwr == 0) {
        cout << endl;
        return;
    }
    
    if (pwr < 0) {
        cout << "/";
    } else {
        cout << "*";
    }
    
    cout << "2**" << abs(pwr) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
