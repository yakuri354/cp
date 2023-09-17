// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll n = 1 << 17;
ll q;

unsigned int a, b;
unsigned int cur = 0; // беззнаковое 32-битное число
unsigned int nextRand17() {
    cur = cur * a + b; // вычисляется с переполнениями
    return cur >> 15; // число от 0 до 217 −1.
}
unsigned int nextRand24() {
    cur = cur * a + b; // вычисляется с переполнениями
    return cur >> 8; // число от 0 до 224 − 1.
}

vector<ll> t[n * 2];
ll f[n];

void build() {
    for (ll i = n - 1; i > 0; i--) {
        t[i].resize(t[i*2].size() + t[i*2+1].size());
        merge(t[i*2].begin(), t[i*2].end(), t[i*2+1].begin(), t[i*2+1].end(), t[i].begin());
    }
}

ll between(vector<ll> &s, ll lo, ll hi) {
    return upper_bound(s.begin(), s.end(), hi) - lower_bound(s.begin(), s.end(), lo);
}

ll query(ll l, ll r, ll lo, ll hi) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += between(t[l++], lo, hi);
        if (r & 1) res += between(t[--r], lo, hi);
    }
    return res;
}

void solve() {
    cin >> q >> a >> b;

    for (int i = 0; i < n; i++)
        t[i + n] = {nextRand24()};

    build();
    
    unsigned int ans = 0;

    for (ll i = 0; i < q; i++) {
        ll l, r, x, y;
        l = nextRand17();
        r = nextRand17();
        if (l > r) swap(l, r); // получили отрезок [l..r]
        x = nextRand24();
        y = nextRand24();
        if (x > y) swap(x, y); // получили отрезок [x..y]
        unsigned int qa = query(l, r + 1, x, y);
        b += qa;
        ans += qa;
    }

    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
