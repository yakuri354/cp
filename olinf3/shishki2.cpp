#include <iostream>
#include <string>

using namespace std;
using ll = unsigned long long;

const ll K = 101;
const ll MAXN = 100010;


ll pow[MAXN];
ll h[MAXN];
ll hr[MAXN];

ll N;
string S;

ll hash_direct(ll l, ll r) {
    ll x = l == 0 ? 0 : h[l - 1];
    return (h[r] - x) * pow[N - r - 1];
}

ll hash_reverse(ll l, ll r) {
    ll x = l == 0 ? 0 : hr[l - 1];
    return (hr[r] - x) * pow[l];
}

int main() {
    cin >> S;
    N = S.length();

    pow[0] = 1;
    for (int i = 1; i <= N; ++i)
        pow[i] = pow[i - 1] * K;

    h[0] = S[0];
    for (int i = 1; i < N; ++i)
        h[i] = h[i - 1] + S[i] * pow[i];

    hr[0] = S[0] * pow[N - 1];
    for (int i = 1; i < N; ++i)
        hr[i] = hr[i - 1] + S[i] * pow[N - i - 1];

    ll counter = 0;

    for (ll i = 0; i < N; ++i) {
        ll low = 1;
        ll high = min(i + 2, N - i + 1);

        while (high > low + 1) {
            ll mid = (low + high) / 2;
            if (hash_direct(i - mid + 1, i + mid - 1) == hash_reverse(i - mid + 1, i + mid - 1))
                low = mid;
            else high = mid;
        }

        counter += low;
    }

    for (ll i = 0; i < N - 1; ++i) {
        ll low = 0;
        ll high = min(i + 2, N - i);

        while (high > low + 1) {
            ll mid = (low + high) / 2;
            if (hash_direct(i - mid + 1, i + mid) == hash_reverse(i - mid + 1, i + mid))
                low = mid;
            else high = mid;
        }

        counter += low;
    }

    cout << counter << endl;
}