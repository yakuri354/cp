// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <exception>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <ostream>
#include <random>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <optional>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

#ifdef DBG
#define inv(x)                                                       \
    if (!(x)) {                                                      \
        cerr << "invariant " #x " violated at " << __LINE__ << endl; \
        exit(-1);                                                    \
    }
#else
#define inv(x)
#endif

#include "geom.hpp"

int main() {
    pt a, b, p_c;
    cin >> a >> b >> p_c;

    fl r;
    cin >> r;
    
    circle cc = {p_c, r};
    
    if (dist(segment(a, b), p_c) - r > -eps) {
        cout << a.to(b).len() << endl;
        return 0;
    }
    
    pair<pt, pt> ts_a, ts_b;

    if (!zero(dist(a, cc))) {
        ts_a = cc.tangents(a).value();
    } else {
        ts_a = {a, a};
    }

    if (!zero(dist(b, cc))) {
        ts_b = cc.tangents(b).value();
    } else {
        ts_b = {b, b};
    }
    
    auto [at1, at2] = ts_a;
    auto [bt1, bt2] = ts_b;
                                        
    fl ans = min(
        abs(p_c.to(at1).angle(p_c.to(bt2))) * r + a.to(at1).len() + b.to(bt2).len(),
        abs(p_c.to(at2).angle(p_c.to(bt1))) * r + a.to(at2).len() + b.to(bt1).len()
    );
    
    cout << ans << endl;
}