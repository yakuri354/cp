//#include <vector>
//#include <iostream>
//#include <cmath>
//#include <random>
////#include "dbg.h"
//
//typedef long long ll;
//using namespace std;
//
//ll c;
//
//vector<ll> root{};
//vector<ll> data{};
//
//ll max_on(ll l, ll r) {
//    ll ans = INT64_MIN;
//    while (l <= r)
//        if (l % c == 0 && l + c <= r) {
//            ans = max(root[l / c], ans);
//            l += c;
//        } else {
//            ans = max(data[l], ans);
//            l++;
//        }
//    return ans;
//}
//
//void sqrt_init() {
//    c = ll(ceil(sqrt(data.size())));
//    root.assign(c, INT64_MIN);
//    for (int i = 0; i < data.size(); ++i) {
//        root[i / c] = max(root[i / c], data[i]);
//    }
//}
//
//int _main() {
//    ll n;
//    cin >> n;
//    data.resize(n);
//    for (ll i = 0; i < n; ++i)
//        cin >> data[i];
//    sqrt_init();
//    ll k;
//    cin >> k;
//    for (ll i = 0; i < k; ++i) {
//        ll t,b;
//        cin >> t >> b;
//        cout << max_on(t - 1, b - 1) << " ";
//    }
//}