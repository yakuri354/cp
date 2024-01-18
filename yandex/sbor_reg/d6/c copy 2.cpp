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

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 5e5;

vector<ll> g[maxn];
ll p[maxn], val[maxn], ans[maxn];

void advc(ll i, ll &curr, ll &acur, vector<ll> &cons) {
    curr += i;

    if (i > 0) {
        cons.push_back(0);
        return;
    }

    if (curr >= 0) {
        cons.pop_back();
        cons.back()++;
        acur += cons.back();
    } else {
        cons = {0};
        curr = 0;
    }
}

void dfs(ll v, ll &curr, ll &ac, vector<ll> &cons) {
    ll curr_old = curr, ac_old = ac;
    auto cons_old = cons;

    advc(val[v], curr, ac, cons);

    ans[v] = ac;

    for (ll u: g[v]) {
        dfs(u, curr, ac, cons);
    }

    curr = curr_old;
    ac = ac_old;
    cons = cons_old;
}

void solve() {
    ll n;
    cin >> n;

    string s;
    cin >> s;

    p[0] = 0;
    val[0] = s[0] == '(' ? 1 : -1;

    for (ll i = 1; i < n; i++) {
        ll pi;
        cin >> pi;
        pi--;

        g[pi].push_back(i);
        p[i] = pi;
        val[i] = s[i] == '(' ? 1 : -1;
    }

    ll curr = 0;
    vector<ll> cons;
    ll az = 0;

    cons.push_back(0);

    dfs(0, curr, az, cons);

    ll ans_xor = 0;
    for (ll i = 0; i < n; i++) {
        ans_xor ^= (i + 1) * ans[i];
    }

    cout << ans_xor << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
    // while (1) {
    //     string s;
    //     cin >> s;
    //     vector<ll> z;
    //     for (ll i = 0; i < s.size(); i++) {
    //         z.push_back(s[i] == '(' ? 1 : -1);
    //     }
    //     cout << count_subs(z) << endl;
    // }
}