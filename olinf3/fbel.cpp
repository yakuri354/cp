//
// Created by yakuri354 on 13.05.22.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAX_N = 100;

ll d[1000];
ll p[1000];
vector<tuple<ll, ll, ll>> e;

int main() {
    ll N;
    cin >> N;
    e.reserve(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ll w;
            cin >> w;
            if (w != 100000) {
                e.emplace_back(i, j, w);
            }
        }
    }
    ll x;
    for (int i = 0; i < N; ++i) {
        x = -1;
        for (auto & j : e) {
            ll a = get<0>(j), b = get<1>(j), w = get<2>(j);
            d[b] = min(d[b], d[a] + w);
            p[b] = a;
            x = b;
        }
    }
    if (x == -1) {
        cout << "NO\n";
        return 0;
    }
    ll r = x;
    while ()

}