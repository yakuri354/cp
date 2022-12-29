//#include <vector>
//#include <iostream>
////#include "dbg.h"
//
//typedef long long ll;
//using namespace std;
//
//vector<ll> data{};
//vector<ll> prefix{};
//
//ll zeroes(ll l, ll r) {
//    return prefix[r+1] - prefix[l];
//}
//
//void prefix_init() {
//    prefix.assign(data.size()+1, 0);
//    for (int i = 1; i <= data.size(); ++i) {
//        prefix[i] = prefix[i - 1] + (data[i-1] == 0);
//    }
//}
//
//int main() {
//    ll n;
//    cin >> n;
//    data.resize(n);
//    for (ll i = 0; i < n; ++i)
//        cin >> data[i];
//    prefix_init();
//    ll k;
//    cin >> k;
//    for (ll i = 0; i < k; ++i) {
//        ll t,b;
//        cin >> t >> b;
//        cout << zeroes(t - 1, b - 1) << " ";
//    }
//}
