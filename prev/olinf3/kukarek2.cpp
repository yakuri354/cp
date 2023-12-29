//#include <iostream>
//#include <vector>
//
//using namespace std;
//using ll = long long;
//
//const ll MAXN = 500;
//
//ll a[MAXN];
//
//int main() {
//    ll T;
//    cin >> T;
//
//    for (int i = 0; i < T; ++i) {
//        ll N, l = 0, r, curr = 1;
//        cin >> N;
//        for (int j = 0; j < N; ++j)
//            cin >> a[j];
//
//        for (int j = 0; j < N; ++j) {
//            if (a[j] == curr) {
//                r = j;
//                if (j == curr - 1 && j != N - 1) {
//                    curr++;
//                    l++;
//                }
//            }
//        }
//
//        ll x = l + r;
//        if (x % 2 == 1) x++;
//        x /= 2;
//        x -= l;
//
//        for (int j = 0; j < x; ++j) {
//            ll temp;
//            temp = a[l + j];
//            a[l + j] = a[r - j];
//            a[r - j] = temp;
//        }
//
//        for (int j = 0; j < N; ++j) {
//            cout << a[j] << " ";
//        }
//        cout << "\n";
//    }
//}