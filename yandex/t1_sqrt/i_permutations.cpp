#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cmath>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

ll hilbertOrder(ll x, ll y, ll pow, ll rotate) {
	if (pow == 0) {
		return 0;
	}
	ll hpow = 1 << (pow-1);
	ll seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const ll rotateDelta[4] = {3, 0, 0, 1};
	ll nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	ll nrot = (rotate + rotateDelta[seg]) & 3;
	ll subSquareSize = ll(1) << (2*pow - 2);
	ll ans = seg * subSquareSize;
	ll add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct qq {
    ll l, r, i;
    
    ll _co = -inf;

    inline pair<int, int> to_pair(ll k) const {
        return make_pair(l / k, ((l / k) & 1) ? -r : +r);
    }

    ll ord() {
        if (_co == -inf) return (_co = hilbertOrder(l, r, 21, 0));
        else return _co;
    }
};

vector<ll> add(const vector<ll> &x, const vector<ll> &y) {
    vector<ll> z(x.size());
    for (ll i = 0; i < x.size(); i++) {
        z[i] = y[x[i] - 1];        
    }
    return z;
}

vector<ll> inv(const vector<ll> &x) {
    vector<ll> z(x.size());
    for (ll i = 0; i < x.size(); i++) {
        z[x[i] - 1] = i + 1;
    }
    return z;
}

ll mass_c(const vector<ll> &x) {
    ll ans = 0;
    for (ll i = 0; i < x.size(); i++) {
        ans += x[i] * (i + 1);
    }
    return ans;
}

vector<ll> _id_perm(ll m) {
    vector<ll> z(m);
    iota(z.begin(), z.end(), 1);
    return z;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    
    const auto id_p = _id_perm(m);
    
    vector<vector<ll>> a(n, vector<ll>(m));

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    ll q;
    cin >> q;
    
    vector<qq> qs(q);
    vector<ll> qa(q);

    for (ll i = 0; i < q; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].i = i;
        qs[i].l--, qs[i].r--;
    }
    
    const static ll k = ll((fl(n) / sqrtl(q)) + 1);
    
    sort(qs.begin(), qs.end(), [](qq a, qq b) -> bool {
        // if (a.l / k == b.l / k) {
        //     return (a.r < b.r) ^ ((a.l / k) & 1);
        // } else {
        //     return a.l / k < b.l / k;
        // }
        
        return a.to_pair(k) < b.to_pair(k);

        // return a.ord() < b.ord();
    });
    
    ll l = 0, r = -1;
    vector<ll> perm = id_p;
    for (ll qi = 0; qi < q; qi++) {
        auto [ql, qr, qix, _co] = qs[qi];

        while (r < qr) perm = add(perm, a[++r]);
        while (l > ql) perm = add(a[--l], perm);
        
        while (r > qr) perm = add(perm, inv(a[r--]));
        while (l < ql) perm = add(inv(a[l++]), perm);
        
        qa[qix] = mass_c(perm);
    }
    
    for (ll i = 0; i < q; i++) {
        cout << qa[i] << '\n';
    }
    
    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}
