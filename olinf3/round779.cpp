////
//// Created by yakuri354 on 27.03.2022.
////
//
//#include <bits/stdc++.h>
//
//using namespace std;
//
//using ll = long long;
//
//const ll MAX_N = 100;
//
//char a[MAX_N];
//
//int main() {
//    ll T;
//    cin >> T;
//    for (ll rep = 0; rep < T; rep++) {
//        ll N;
//        cin >> N;
//        for (ll i = 0; i < N; i++) {
//            char X;
//            cin >> X;
//            a[i] = X - '0';
//        }
//
//        ll i = 0, end = N - 1, ans = 0;
//
//        while (a[i]) i++;
//        while (a[end]) end--;
//
//        vector<vector<int>> groups{};
//
//        while (i <= end) {
//            vector<int> x{};
//            auto tm = a[i];
//            while (a[i] == tm && i <= end) {
//                x.push_back(tm);
//                i++;
//            }
//            groups.push_back(x);
//        }
//
//        for (auto &v:groups) {
//            if (v[0] && v.size() == 1) ans += 1;
//            else if (!v[0]) ans += (v.size() - 1) * 2;
//        }
//
//        cout << ans << "\n";
//
//        next_rep:;
//    }
//}

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAX_N = 1e5;

ll a[MAX_N];

int main() {
    ll T;
    cin >> T;
    for (ll rep = 0; rep < T; rep++) {
        ll N, ipos = -1, pos2 = -1, last = -1;
        cin >> N;

        if (N == 1) {
            ll _x;
            cin >> _x;
            cout << "YES\n";
            continue;
        }

        for (ll i = 0; i < N; i++) {
            cin >> a[i];
            if (a[i] == 1) ipos = i;
            if (a[i] == 2) pos2 = i;
        }

        if (ipos == -1 || pos2 == -1) {
            cout << "NO\n";
            continue;
        }

        for (int _i = 0; _i < N; ++_i) {
            ll i = (ipos + _i) % N;
            if (last != -1 && a[i] - last > 1) {
                cout << "NO\n";
                goto next;
            }
            last = a[i];
        }

        cout << "YES\n";

        next:;
    }
}