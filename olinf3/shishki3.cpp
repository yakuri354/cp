#include <iostream>

using namespace std;
using ll = unsigned long long;

const ll MAXN = 1000000;


ll pow[MAXN];
ll h[MAXN];
ll hr[MAXN];

ll N;
ll a[MAXN];

ll hash_direct(ll l, ll r) {
    ll x = l == 0 ? 0 : h[l - 1];
    return (h[r] - x) * pow[N - r - 1];
}

ll hash_reverse(ll l, ll r) {
    ll x = l == 0 ? 0 : hr[l - 1];
    return (hr[r] - x) * pow[l];
}

int main() {
    ll M, K;
    cin >> N >> M;

    K = M + 10;
    if (K % 2 == 0) K++;

    for (ll i = 0; i < N; i++) cin >> a[i];


    pow[0] = 1;
    for (int i = 1; i <= N; ++i)
        pow[i] = pow[i - 1] * K;

    h[0] = a[0];
    for (int i = 1; i < N; ++i)
        h[i] = h[i - 1] + a[i] * pow[i];

    hr[0] = a[0] * pow[N - 1];
    for (int i = 1; i < N; ++i)
        hr[i] = hr[i - 1] + a[i] * pow[N - i - 1];

    cout << N << " ";

    for (int i = 1; i <= N / 2; ++i) {
        if (hash_direct(0, 2*i - 1) == hash_reverse(0, 2*i - 1)) cout << N - i << " ";
    }
}