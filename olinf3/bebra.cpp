#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAX_N = 2 * 1e5;

ll a[MAX_N];

int main() {
    ll T;
    cin >> T;
    for (ll rep = 0; rep < T; rep++) {
        ll N;
        cin >> N;
        for (ll i = 0; i < N; i++) cin >> a[i];
        ll mmx = a[(N / 2) - 1];
        ll mpx = (N / 2) - 1;
        ll mmn = a[(N / 2) - 1];
        ll mpn = (N / 2) - 1;
        ll prev = a[(N / 2) - 1];
        for (int i = (N / 2) - 2; i >= 0; i--) {
            ll X = a[i] * prev;
            if (mmx < X) {
                mmx = X;
                mpx = i;
            }
            if (mmn > X) {
                mmn = X;
                mpn = i;
            }
        }
        ll mmx2, mmn2, prev2, mpx2, mpn2;
        mmx2 = mmn2 = prev2 = a[N / 2];
        mpx2 = mpn2 = N / 2;

        for (int i = N / 2 + 1; i < N; ++i) {
            ll X = a[i] * prev2;
            if (mmx2 < X) {
                mmx2 = X;
                mpx2 = i;
            }
            if (mmn2 > X) {
                mmn2 = X;
                mpn2 = i;
            }
        }

        ll ans = 0;
        ll aaa = INT32_MIN;

        if (mmx2 * mmx > aaa) { ans = 0; aaa = mmx2 * mmx;}
        if (mmn * mmn2 > aaa) { ans = 1; aaa = mmn * mmn2; }
        if (mmx > aaa) { ans = 2; aaa = mmx; }
        if (mmx2 > aaa) { ans = 3; aaa = mmx2; }
        if (aaa <= 0) ans = 4;

        if (ans == 0) cout << mpx << " " << N - mpx2 - 1 << "\n";
        if (ans == 1) cout << mpn << " " << N - mpn2 - 1 << "\n";
        if (ans == 2) cout << mpx << " " << N - (N / 2) << "\n";
        if (ans == 3) cout << N / 2 << " " << N - mpx2 - 1 << "\n";
        if (ans == 4) cout << N << " 0\n";

        next_rep:;
    }
}