// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <atomic>
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

#ifdef DBG
#define inv(x)                                                       \
    if (!(x)) {                                                      \
        cerr << "invariant " #x " violated at " << __LINE__ << endl; \
        __builtin_trap();                                            \
        exit(-1);                                                    \
    }
#else
#define inv(x)
#endif

struct piece {
    ll len, cnt, to_end, to_first;
};

struct edge {
    ll v, ix;
};

vector<piece> input;
unordered_map<ll, vector<edge>> g;
unordered_map<ll, ll> ins;

ll N, used;
vector<ll> euler_res;

void dfs_euler(ll v, ll ix) {
    while (!g[v].empty()) {
        auto e = g[v].back();
        g[v].pop_back();
        dfs_euler(e.v, e.ix);
    }

    euler_res.push_back(ix);
}

bool solve_for(ll dist) {
    g.clear();
    ins.clear();

    for (ll i = 0; i < N; i++) {
        g[input[i].to_first].push_back({dist - input[i].to_end, i});
        ins[dist - input[i].to_end]++;
        if (!ins.count(input[i].to_first)) ins[input[i].to_first] = 0;
    }

    vector<ll> in_bad, out_bad;
    for (auto &[vx, in_c]: ins) {
        switch (in_c - ll(g[vx].size())) {
            case 0: continue;
            case 1:
                in_bad.push_back(vx);
                break;
            case -1:
                out_bad.push_back(vx);
                break;
            break;
            default:
                return false;
        }
    }

    if (in_bad.size() + out_bad.size() > 2) {
        return false;
    }

    if (out_bad.empty()) {
        out_bad.push_back(g.begin()->first);
    }

    dfs_euler(out_bad[0], -1);

    euler_res.pop_back();

    reverse(euler_res.begin(), euler_res.end());

    if (euler_res.size() < N) exit(-1);

    cout << "Yes" << '\n';
    for (ll i: euler_res) {
        cout << i + 1 << ' ';
    }
    cout << endl;

    return true;
}

void solve() {
    cin >> N;

    input.resize(N);

    ll dist = -1, shit_data = 0;
    for (ll i = 0; i < N; i++) {
        ll cnt, len;
        cin >> cnt >> len;

        vector<ll> curr(cnt);
        for (ll &i: curr) cin >> i;

        for (ll i = 1; i < cnt; i++) {
            if (dist == -1) {
                dist = curr[i] - curr[i-1];
            } else if (dist != curr[i] - curr[i-1]) {
                shit_data = 1;
            }
        }

        input[i].cnt = cnt;
        input[i].to_first = curr[0];
        input[i].to_end = len - curr.back();
        input[i].len = len;
    }

    if (shit_data) {
        cout << "No" << endl;
        return;
    }

    if (N == 1) {
        cout << "Yes" << '\n' << 1 << endl;
        return;
    }

    if (dist == -1) {
        // exit(-1);
        cout << "No" << endl;
        return;
    }

    if (!solve_for(dist)) {
        cout << "No" << endl;
        return;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

