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

const ll maxn = 1e5;

vector<ll> g[maxn];
ll p[maxn], val[maxn], ans[maxn];

ll count_subs(vector<ll> &s) {
    ll curr = 0;
    vector<ll> cons;
    ll ans = 0;

    cons.push_back(0);
    for (ll i: s) {
        curr += i;

        if (i > 0) {
            cons.push_back(0);
            continue;
        }

        if (curr >= 0) {
            cons.pop_back();
            cons.back()++;
            ans += cons.back();
        } else {
            cons = {0};
            curr = 0;
        }
    }

    return ans;
}

void dfs(ll v, ll curr, ll a_p, vector<ll> &cons) {
    ll i = val[v];

    curr += i;

    if (i > 0) {
        cons.push_back(0);
        for (ll u: g[v]) {
            dfs(u, curr, a_p, cons);
        }
        cons.pop_back();
        ans[v] = a_p;
        return;
    }

    if (curr >= 0) {
        ll bcp = cons.back();
        cons.pop_back();
        cons.back()++;
        ll curr_ans = a_p + cons.back();

        for (ll u: g[v]) {
            dfs(u, curr, curr_ans, cons);
        }

        ans[v] = curr_ans;

        cons.back()--;
        cons.push_back(bcp);
    } else {
        vector<ll> old_cons = cons;
        cons = {0};
        curr = 0;

        for (ll u: g[v]) {
            dfs(u, curr, a_p, cons);
        }

        cons = old_cons;
    }
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

    vector<ll> cons;

    cons.push_back(0);
    dfs(0, 0, 0, cons);

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

