// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <bitset>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 2000;
const ull P = 1e6 + 3;

ull p[maxn], h[maxn];

ull hs(ll l, ll r) {
    ull v = 0;
    if (r > 0) v += h[r-1];
    if (l > 0) v -= h[l-1];

    return v * p[l];
}

void encode_hash(ll n) {
    vector<ll> a(n);

    for (ll &i: a) cin >> i;

    p[0] = 1;
    for (ll i = 1; i < n; i++) {
        p[i] = p[i-1] * P;
    }

    h[0] = a[0] * p[n - 1];
    for (ll i = 1; i < n; i++) {
        h[i] = h[i-1] + a[i] * p[n - i - 1];
    }

    cout << bitset<64>(h[n - 1]) << endl;
}

void decode_hash(ll n) {
    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    bitset<64> hb;
    cin >> hb;

    ull hash = hb.to_ullong();

    p[0] = 1;
    for (ll i = 1; i < n; i++) {
        p[i] = p[i-1] * P;
    }

    h[0] = a[0] * p[n - 1];
    for (ll i = 1; i < n; i++) {
        h[i] = h[i-1] + a[i] * p[n - i - 1];
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j < n; j++) {
            ull nh = h[n-1] - a[i] * p[n - i - 1] - a[j] * p[n - j - 1] + a[i] * p[n - j - 1] + a[j] * p[n - i - 1];
            if (nh == hash) {
                swap(a[i], a[j]);
                break;
            }
        }
    }

    for (ll i: a) cout << i << ' ';
    cout << endl;
}

void decode() {
    ll n;
    cin >> n;

    if (n <= 2000) {
        decode_hash(n);
        return;
    }

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    for (ll i = 0; i < n; i++) {
        bitset<20> x;
        cin >> x;
        a[i] = x.to_ullong();
    }

    for (ll i: a) cout << i << ' ';
    cout << endl;
}

void encode() {
    ll n;
    cin >> n;

    if (n <= 2000) {
        encode_hash(n);
        return;
    }

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    for (ll &i: a) {
        cout << bitset<20>(i);
    }

    cout << endl;
}

void solve() {
    ll ty;
    cin >> ty;

    if (ty == 1) {
        encode();
    } else {
        decode();
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

