// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <chrono>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

ll t;

const ll maxn = 676;

ll C[maxn][maxn];
vector<ll> ord;

ll state = 0;

ll calc(ll i) {
    return C[ord[i]][ord[i+1]] * C[ord[i+1]][ord[i+2]] * C[ord[i]][ord[i+2]];
}

uniform_real_distribution<float> fld(0, 1);

// bool F(fl temp, ll olds, ll news, mt19937_64 &mt) {
//     return news < olds || exp(fl(olds - news) / temp) < fld(mt);
// }

bool F(fl temp, ll olds, ll news, mt19937_64 &mt) {
    return news > olds || pow(fl(news) / fl(olds), 1/temp) > fld(mt);
}

ll best_st = 0;
vector<ll> ans;

void solve() {
    ll n;
    cin >> n;

    cout << "==== STARTING TEST CASE " << t << " ====" << endl;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cin >> C[i][j];
        }
    }

    ord.resize(n);
    iota(ord.begin(), ord.end(), 0);
    
    for (ll i = 0; i < n; i += 3) {
        state += calc(i);
    }

    best_st = state;
    ans = ord;

    uniform_int_distribution<ll> nd(0, n - 1);

    ll seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937_64 mt(seed);

    cout << "seed " << seed << endl;

    cout << endl;
    fl temp = 10;
    for (ll its = 0;temp > 1e-5;its++) {
        if (its % 100000 == 0) {
            cout << "\33[2K\r";
            cout << setw(20) << temp << " " << setw(20) << best_st << " (" << setw(20) << state << ")" << flush;
            // for (ll i = 0; i < n; i++) {
            //     if (i % 3 == 0) cout << '\n';
            //     cout << ans[i] << ' ';
            // }
            // cout << endl;
        }

        ll aa = nd(mt), bb = aa;
        while (aa / 3 == bb / 3) bb = nd(mt);

        ll st_old = state;
        state -= calc(aa - aa % 3) + calc(bb - bb % 3);
        swap(ord[aa], ord[bb]);
        state += calc(aa - aa % 3) + calc(bb - bb % 3);

        if (!F(temp, st_old, state, mt)) {
            swap(ord[aa], ord[bb]);
            state = st_old;
        }

        if (state > best_st) {
            best_st = state;
            ans = ord;
        }

        temp *= 0.9999999;
    }

    cout << endl << endl;
    cout << "==== END ====" << endl;

    for (ll i = 0; i < n; i += 3) {
        cerr << ans[i] + 1 << ' ' << ans[i+1] + 1 << ' ' << ans[i+2] + 1 << '\n';
        cout << ans[i] + 1 << ' ' << ans[i+1] + 1 << ' ' << ans[i+2] + 1 << endl;
    }

    cerr << endl;
    cout << endl << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> t; while (t --> 0)
    solve();
}

