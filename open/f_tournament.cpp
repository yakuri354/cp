// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

ll n;
ll queries;

map<pair<ll, ll>, bool> asked;
vector<set<ll>> out_known;
vector<set<ll>> in_known;
vector<ll> dir;

bool in_check;

bool ask(ll u, ll v) {
    if (asked.count({u, v})) {
        return asked[{u, v}];
    }
    if (asked.count({v, u})) {
        return !asked[{v, u}];
    }

    if (queries >= 2000) {
        if (in_check) exit(-1);
        #ifdef DBG
        cerr << "count exceeded" << endl;
        exit(-1);
        #endif
        volatile ull x = 0;
        while (true) {
            x++;
        }
    }

    cout << "? " << u + 1 << ' ' << v + 1 << endl;
    queries++;
    string ans;
    cin >> ans;
    ll res = ans == "forward";

    if (res) {
        dir[u] = v;
        out_known[u].insert(v);
        in_known[v].insert(u);
    } else {
        dir[v] = u;
        out_known[v].insert(u);
        in_known[u].insert(v);
    }

    asked[{u, v}] = res;

    return res;
}

void divide(vector<ll>& a, vector<ll>& b) {
    while (a.size() > b.size()) {
        b.push_back(a.back());
        a.pop_back();
    }

    for (ll i = 0; i < a.size(); i++) {
        if (!ask(a[i], b[i]))
            swap(a[i], b[i]);
    }
}

mt19937_64 mt(228);

pair<vector<ll>, vector<ll>> split(vector<ll>& vs) {
    vector<ll> left, right;

    shuffle(vs.begin(), vs.end(), mt);

    copy(vs.begin(), vs.begin() + vs.size() / 2, back_inserter(left));
    copy(vs.begin() + vs.size() / 2, vs.end(), back_inserter(right));

    divide(left, right);

    return {left, right};
}

void process(vector<ll>& vs) {
    auto [l1, r1] = split(vs);

    auto [l_from, l_to] = split(l1);
    auto [r_from, r_to] = split(r1);
    auto [_lt_from, lt_to] = split(l_to);
    auto [_rf_from, rf_to] = split(r_from);

    vs.clear();
    copy(lt_to.begin(), lt_to.end(), back_inserter(vs));
    copy(rf_to.begin(), rf_to.end(), back_inserter(vs));
    copy(r_to.begin(), r_to.end(), back_inserter(vs));
}

bool check(ll v) {
    if (out_known[v].size() > 1) return false;

    in_check = true;

    vector<ll> all(n);
    iota(all.begin(), all.end(), 0);
    shuffle(all.begin(), all.end(), mt);

    for (ll i = 0; i < n; i++) {
        if (all[i] == v)
            continue;
        ask(v, all[i]);
        if (out_known[v].size() > 1) {
            in_check = false;
            return false;
        }
    }
    in_check = false;
    return true;
}

void answer(const vector<ll> &a) {
    for (ll i : a) {
        if (check(i)) {
            cout << "! " << i + 1 << endl;
            return;
        }
    }
    cout << "! " << -1 << endl;
}

bool related(ll a, ll b) {
    return dir[a] == b || dir[b] == a;
}

void solve2() {
    cin >> n;
    queries = 0;

    out_known.assign(n, {});
    in_known.assign(n, {});
    dir.assign(n, -1);
    asked.clear();

    vector<ll> d0(n), d1;

    iota(d0.begin(), d0.end(), 0);

    // n
    while (d0.size() > 1) {
        ll v = d0.back();
        ll u = d0[d0.size() - 2];
        d0.erase(d0.end() - 2, d0.end());

        if (ask(v, u)) {
            d1.push_back(v);
            d0.push_back(u);
        } else {
            d1.push_back(u);
            d0.push_back(v);
        }
    }
    // ok

    // n
    set<ll> zlp;
    if (!d0.empty()) {
        ll v = d0.back();
        for (ll i = 0; i < n; i++) {
            if (i == v) continue;

            ll nprev = dir[i] != v;
            if (!ask(v, i) && nprev) {
                zlp.insert(i);
            }
        }

        if (check(d0[0])) {
            cout << "! " << d0[0] + 1 << endl;
            return;
        }
    }

    vector<ll> xxx;

    for (ll i: d1) {
        if (!zlp.count(i)) xxx.push_back(i);
    }

    d1 = xxx;

    while (d1.size() > 1) {
        sort(d1.rbegin(), d1.rend(), [&](ll a, ll b) {
            return in_known[a].size() < in_known[b].size();
        });

        ll f_i = -1, f_j = -1;
        for (ll i = 0; i < d1.size(); i++) {
            for (ll j = i + 1; j < d1.size(); j++) {
                if (!related(d1[i], d1[j])) {
                    f_i = i;
                    f_j = j;
                    goto cnt;
                }
            }
        }

        cnt: if (f_i == -1) {
            break;
        }

        auto v1 = d1[f_i], v2 = d1[f_j];

        d1.erase(d1.begin() + f_i);
        d1.erase(d1.begin() + f_j);

        if (ask(v1, v2)) {
            d1.push_back(v2);
        } else {
            d1.push_back(v1);
        }
    }

    while (!d1.empty()) {
        if (check(d1.back())) {
            cout << "! " << d1.back() + 1 << endl;
            return;
        }
        d1.pop_back();
    }

    cout << "! kal kall ksdjlfa" << endl;
}

void solve() {
    cin >> n;
    queries = 0;

    out_known.assign(n, {});
    in_known.assign(n, {});
    dir.assign(n, -1);
    asked.clear();

    vector<ll> all(n);
    iota(all.begin(), all.end(), 0);

    while (all.size() > 3) {
        process(all);
    }

    if (all.size() == 0) {
        //cerr << "0 left" << endl;
        answer({});
    } else if (all.size() == 1) {
        //cerr << "1 left: " << all[0] + 1 << endl;
        answer({all[0]});
    } else if (all.size() == 2) {
        //cerr << "2 left: " << all[0] + 1 << ' ' << all[1] + 1 << endl;
        if (!ask(all[0], all[1])) swap(all[0], all[1]);
        answer({all[0], all[1]});
    } else if (all.size() == 3) {
        //cerr << "3 left: " << all[0] + 1 << ' ' << all[1] + 1 << ' ' << all[2] + 1 << endl;
        bool ab = ask(all[0], all[1]), bc = ask(all[1], all[2]),
             ac = ask(all[0], all[2]);

        ll ad = ab + ac, bd = !ab + bc, cd = !ac + !bc;

        // cerr << "degs " << all[0] + 1 << " = " << ad << "; " << all[1] + 1 << " = " << bd << "; " << all[2] + 1 << " = " << cd << endl;

        vector<ll> ans;
        if (ad < 2) ans.push_back(all[0]);
        if (bd < 2) ans.push_back(all[1]);
        if (cd < 2) ans.push_back(all[2]);

        answer(ans);
    }

    string ans;
    cin >> ans;

    if (ans == "WRONG") {
        exit(0);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll g, t;
    cin >> g >> t;
    while (t-- > 0)
        solve2();
}
