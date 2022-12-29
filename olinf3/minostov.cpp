//
// Created by yakuri354 on 25.03.2022.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAX_N = 1e6;
ll p[MAX_N];
ll s[MAX_N];

ll leader(ll a) {
    return (p[a] == a) ? a : p[a] = leader(p[a]);
}

void unite(ll a, ll b) {
    ll la = leader(a), lb = leader(b);
    if (la == lb) return;
    s[la] += s[lb];
    p[lb] = la;
}

int main() {
    ll N, M;
    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        p[i] = i;
    }

    for (int i = 0; i < M; ++i) {
        ll A, X;
        cin >> A >> X;

        if (A == 1) {
            ll Y, W;
            cin >> Y >> W;
            unite(X, Y);
            s[leader(X)] += W;
        } else {
            cout << s[leader(X)] << '\n';
        }
    }
}