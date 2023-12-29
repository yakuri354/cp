//
// Created by yakuri354 on 23.02.2022.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

//int main() {
//    ll T;
//    cin >> T;
//    for (ll rep = 0; rep < T; rep++) {
//        ll N;
//        cin >> N;
//        unordered_set<int> exists(N);
//        for (ll i = 0; i < N; i++) {
//            int X;
//            cin >> X;
//            exists.insert(X);
//        }
//
//        for (int i = 1; i <= N; ++i) {
//            if (i <= exists.size()) cout << exists.size() << " ";
//            else cout << i << " ";
//        }
//        cout << "\n";
//    }
//}

//int main() {
//    ll T;
//    cin >> T;
//    for (ll rep = 0; rep < T; rep++) {
//        int x[3], y[3];
//
//        for (int i = 0; i < 3; ++i) {
//            cin >> x[i] >> y[i];
//        }
//
//        for (int i = 0; i < 3; ++i)
//            for (int j = 0; j < 3; ++j)
//                for (int k = 0; k < 3; ++k)
//                    if (y[i] == y[j] && y[k] < y[i] && i != j && k != i && k != j) {
//                        cout << abs(x[i] - x[j]) << "\n";
//                        goto next;
//                    }
//        cout << 0 << "\n";
//        next:;
//    }
//}

const ll MAXN = 2 * 1e5;

int main() {
    ll T;
    cin >> T;
    for (ll rep = 0; rep < T; rep++) {
        ll N, X;
        cin >> N >> X;
        map<ll, ll> set{};

        for (int i = 0; i < N; ++i) {
            int Z;
            cin >> Z;
            if (set.count(Z)) {
                set[Z]++;
            } else {
                set[Z] = 1;
            }
        }

        ll ans = N;

        while (!set.empty()) {
            auto el = set.begin()->first;
            if (set.count(el * X)) {
                if (--set[el * X] <= 0) set.erase(el * X);
                ans -= 2;
            }
            if (--set[el] <= 0) set.erase(el);
        }

        cout << ans << "\n";
    }
}