#include <iostream>
#include <vector>
#include <algorithm>
//#include <random>
//#include <unistd.h>
//#include "prettyprint.hpp"

#define ll unsigned long long

using namespace std;

ll sparse[15][25000];

ll rmq(ll l, ll r) {
    if (l == r) return sparse[0][l];
    ll _l = min(l, r);
    ll _r = max(l, r) + 1;
    if (_r - _l == 1) return sparse[1][_l];
    ll log = std::__lg(_r - _l);
    return min(sparse[log][_l], sparse[log][_r - (1 << log)]);
}

void init_sparse(ll len) {
    for (int i = 1; i < 15; ++i)
        for (int j = 0; j + (1 << i) <= len; j++)
            sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
}

int sp1main() {
    cin.tie(nullptr);
    vector<ll> results{};
    ll n, m, a, b;
    cin >> n >> m >> a >> b;
    while (n != 0 && m != 0 && a != 0 && b != 0) {

        ll sum = 0;
        for (ll i = 1; i <= n; ++i) {
            sparse[0][i - 1] = (unsigned) (a * i + b);
        }

        init_sparse(n);
        //cout << "\n\n";
        for (ll i = n + 1; i <= n + 2 * m; i += 2) {
            ll l = unsigned(a * i + b) % n;
            ll r = unsigned(a * (i + 1) + b) % n;
            //cout << l << " " << r << "\n";
            sum += rmq(l, r);
        }
        results.push_back(sum);
        cin >> n >> m >> a >> b;
    }
    for (auto &x: results)
        cout << x << "\n";
}

//int main() {
//    ll n = 500;
//    ll m = 1000;
////    for (int i = 0; i < 7; ++i) {
////        if (!fork()) break;
////    }
//    default_random_engine e{random_device{}()};
//    uniform_int_distribution<ll> u{0, 10000000};
//    for (ll ii = 0;; ii++) {
//        ll t = u(e);
//        ll b = u(e);
//        //cout << "[" << i << "] A=" << t << " B=" << b << endl;
//        for (ll i = 1; i <= n; ++i) {
//            sparse[0][i - 1] = (unsigned) (t * i + b);
//        }
//        init_sparse(n);
//        for (ll i = n + 1; i <= n + 2 * m; i += 2) {
//            ll l = unsigned(t * i + b) % n;
//            ll r = unsigned(t * (i + 1) + b) % n;
//            //cout << l << " " << r << "\n";
//            ll _l = min(l, r);
//            ll _r = max(l, r);
////            if (_r - _l > 10) continue;
//            ll curr = UINT64_MAX;
//            for (ll j = _l; j <= _r; ++j) {
//                curr = min(curr, sparse[0][j]);
//            }
//            ll s = rmq(_l, _r + 1);
//            if (s != curr) {
//                cout << "[ " << ii << " ] MISMATCH\n";
//                cout << "N=" << n << " M=" << m << " A=" << t << " B=" << b << "\n";
//                cout << "SPARSE=" << s << " DUMB=" << curr << "\n";
//                cout << "QUERY: l=" << l << " r=" << r << "\n";
//                if (n <= 1000)
//                    cout << "sparse[0]: " << pretty_print_array(sparse[0], n) << "\n";
//                if (_r - _l <= 1000) {
//                    cout << "RANGE: \n";
//                    for (ll j = _l; j <= _r; ++j)
//                        cout << "[" << j << "] " << sparse[0][j] << ", ";
//                }
//                return 0;
//            }
//        }
//    }
//}
