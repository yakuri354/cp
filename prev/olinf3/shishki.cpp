#include <iostream>
#include <string>

using namespace std;
using ll = long long;

const ll MAXN = 10100;
const ll K = 101;
const ll MOD = 1e9+7;

ll N;
ll M;
string S;
string T;

ll p[MAXN];
ll h[MAXN];
ll hT;

ll mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

ll hash_substr(ll l, ll r) {
    ll x = l == 0 ? 0 : h[l - 1];

    return mod(mod(h[r] - x) * p[N - l - 1]);
}

int main() {
    cin >> S >> T;
    S.append(S);
    N = S.length();
    M = T.length();

    p[0] = 1;
    for (int i = 1; i <= N; ++i)
        p[i] = mod(p[i-1] * K);

    h[0] = S[0];
    for (int i = 1; i < N; ++i)
        h[i] = mod(h[i - 1] + p[i] * S[i]);

    hT = T[0];
    for (int i = 1; i < M; ++i)
        hT = mod(hT + p[i] * T[i]);
    hT = mod(hT * p[N - 1]);

    for (int i = 0; i <= N - M; ++i)
        if (hash_substr(i, i + M - 1) == hT) {
            if (i == 0) cout << 0 << endl;
            else cout << M - i << endl;
            return 0;
        }
    cout << -1 << endl;
}