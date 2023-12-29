//
// Created by yakuri354 on 06.03.2022.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

//const ll MAX_N = 100;

//ll a[MAX_N];

//int main() {
//    ll T;
//    cin >> T;
//    for (ll rep = 0; rep < T; rep++) {
//        ll N;
//        cin >> N;
//        for (ll i = 0; i < N; i++) cin >> a[i];
//        ll firstz = -1, lastz = -1;
//        for (int i = 0; i < N; ++i)
//            if (a[i] == 0) { firstz = i; break; }
//        if (firstz == -1) {
//            cout << 0 << "\n";
//            continue;
//        }
//        for (int i = 0; i < N; ++i)
//            if (a[N - 1 - i] == 0) { lastz = N - i - 1; break; }
//
//        cout << lastz - firstz + 2 << "\n";
//    }
//}

int main() {
    ll T;
    cin >> T;
    for (ll rep = 0; rep < T; rep++) {
        ll N, pool = 0;
        bool inc = true, nonz = false;
        cin >> N;
        for (ll i = 0; i < N; i++) {
            ll X;
            cin >> X;
            if (X != 0) nonz = true;
            if (inc) {
                pool += X;
            } else {
                pool -= X;
            }
            inc = !inc;
        }
        if (!nonz) cout << 0 << "\n";
        else if (pool == 0) cout << 1 << "\n";
        else cout << abs(pool) << "\n";
    }
}