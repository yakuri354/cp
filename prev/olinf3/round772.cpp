//
// Created by yakuri354 on 20.02.2022.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

//const ll MAX_N = 100;

const ll MAX_N = 2 * 1e5;

ll a[MAX_N];

//int main() {
//    ll T;
//    cin >> T;
//    for (ll rep = 0; rep < T; rep++) {
//        ll N;
//        cin >> N;
//        for (ll i = 0; i < N; i++) cin >> a[i];
//
//        for (int i = 0; i < N - 1; ++i) {
//            a[i + 1] = min(a[i + 1] | a[i], a[i + 1] + a[i]);
//            a[i] = 0;
//        }
//
//        cout << a[N - 1] << "\n";
//    }
//}

//int main() {
//    ll T;
//    cin >> T;
//    for (ll rep = 0; rep < T; rep++) {
//        ll N, op = 0;
//        cin >> N;
//        for (ll i = 0; i < N; i++) cin >> a[i];
//        for (int i = 0; i < N - 2; ++i) {
//            ll l = a[i], m = a[i + 1], r = a[i + 2];
//            if (m > l && m > r) {
//                if (i < N - 3 && a[i + 3] > r && a[i + 4] < a[i+3]) {
//                    a[i+2] = max(m, a[i+3]);
//                } else {
//                    a[i+1] = max(l, r);
//                }
//                op++;
//            }
//        }
//        cout << op << "\n";
//        for (int i = 0; i < N; ++i) {
//            cout << a[i] << " ";
//        }
//        cout << "\n";
//    }
//}

void print_arr(ll n) {
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main() {
    ll T;
    cin >> T;
    for (ll rep = 0; rep < T; rep++) {
        ll N;
        cin >> N;
        for (ll i = 0; i < N; i++) cin >> a[i];
        ll l = a[N-1],al=a[N-2];

        if (al > l) {
            cout << -1 << "\n";
            continue;
        }

        if (al - l > al) {
            if (is_sorted(a, a + N - 1)) {
                cout << 0 << "\n";
            } else {
                cout << -1 << "\n";
            }
            continue;
        }

        cout << N - 2 << "\n";

        for (int i = 0; i < N - 2; ++i) {
            cout << i + 1 << " " << N - 1 << " " << N << "\n";
        }
    }
}