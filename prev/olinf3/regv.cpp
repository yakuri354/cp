#include <bits/stdc++.h>

using ll = long long;

using namespace std;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

const ll maxn = 1e5;

ll a[maxn];
ll b[maxn];
ll c[maxn];
pair<ll, ll> cidx[maxn];

int main() {
    ll n, q;
    cin >> n >> q;

    unordered_map<ll, ll> map;
    map.rehash(q);

    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < q; ++i) {
        cin >> c[i];
        map[c[i]] = i;
    }

    sort(a, a + n);
    sort(b, b + n);
    sort(c, c + q);

    for (ll idx = 1, ai = 0, bi = n - 1;; idx++) {
        if (map.count(idx)) {
            cidx[map[idx]] = make_pair(a[ai], b[bi]);
        }

        if (bi == 0 || (ai < n && double(a[ai]) / double(b[bi - 1]) > double(a[ai]) / double(b[bi - 1]))) ai++;
        else bi--;
        if (bi == 0 && ai == n - 1) break;
        cerr << "next (" << ai << ") " << a[ai] << " / (" << bi << ") " << b[bi] << endl;
    }

    for (int i = 0; i < q; ++i) {
        ll h, l, gcdv;
        tie(h, l) = cidx[i];
        gcdv = gcd(h, l);
        cout << h / gcdv << ' ' << l / gcdv << '\n';
    }
}