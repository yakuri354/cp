// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <chrono>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

#ifndef DBG
#define cerr if (0) cerr
#endif

using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

inline bool decide(fl t, mt19937_64 &mt, ll old_s, ll new_s) {
    if (new_s < old_s) return true;

    fl r = uniform_real_distribution<fl>()(mt);
    return r < exp(fl(old_s - new_s) / t);
    // return r < exp(-(fl(old_s) / fl(new_s)) / t);

    // return r < exp(fl(log(old_s) - log(new_s)) / t);
}

inline fl update_temp(fl t, ll it) {
    // return 50 / log(1 + it);
    return t * 0.999999999;
}

void solve(bool from_global) {
    const ll n = 312;

    ll global_len = 0;
    vector<ll> global(n);

    {
        ifstream inp("ans.txt");
        if (!inp.good()) exit(-1);
        for (ll i = 0; i < n; i++) {
            inp >> global[i];
        }
    }

    vector<vector<ll>> mat(n, vector<ll>(n));

    ifstream edges("mat.txt");

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            edges >> mat[i][j];
        }
    }

    for (ll i = 0; i < n - 1; i++) {
        global_len += mat[global[i]][global[i+1]];
    }

    cout << "STARTING WITH GL " << global_len << endl << endl;

    mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

    ll cur_l = 0;
    vector<ll> state(n);

    if (from_global) {
        state = global;
        cur_l = global_len;   
    } else {
        iota(state.begin(), state.end(), 0);
        shuffle(state.begin(), state.end(), mt);
        
        for (ll i = 0; i < n - 1; i++) {
            cur_l += mat[state[i]][state[i+1]];
        }
    }

    fl temp = 10;

    uniform_int_distribution<ll> nd(0, n - 1);

    for (ll it = 1;; it++) {
        if (it % 10000 == 0) {
            cout << "\33[2K\r" << "gl " << global_len << " t " << temp << " cur " << cur_l << flush;
        }

        ll i = nd(mt);
        ll j = nd(mt);
        while (j == i) j = nd(mt);

        if (i > j) swap(i, j);

        ll new_l = cur_l;

        if (j == i + 1) {
            new_l -= mat[state[i]][state[j]];
            new_l += mat[state[j]][state[i]];

            if (i > 0) new_l += -mat[state[i-1]][state[i]] + mat[state[i-1]][state[j]];
            if (j < n - 1) new_l += -mat[state[j]][state[j+1]] + mat[state[i]][state[j+1]];
        } else {
            if (i > 0) new_l += -mat[state[i-1]][state[i]] + mat[state[i-1]][state[j]];
            if (i < n - 1) new_l += -mat[state[i]][state[i+1]] + mat[state[j]][state[i+1]];

            if (j > 0) new_l += -mat[state[j-1]][state[j]] + mat[state[j-1]][state[i]];
            if (j < n - 1) new_l += -mat[state[j]][state[j+1]] + mat[state[i]][state[j+1]];
        }

        if (decide(temp, mt, cur_l, new_l)) {
            swap(state[i], state[j]);
            cur_l = new_l;
        }

        if (cur_l < global_len) {
            cout << "------ NEW GLOBAL ------" << endl;
            cout << global_len << endl << endl << endl;

            global = state;
            global_len = cur_l;

            system("touch ans.txt");

            ofstream of("ans.txt", ios::trunc);
            
            if (of.bad()) exit(-1);

            for (ll i = 0; i < n; i++) {
                of << global[i] << ' ';
            }

            of << flush;
        }

        temp = update_temp(temp, it);
    }

    cout << endl;
}

int main(int argc, char **argv) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    bool fg = false;
    for (ll i = 1; i < argc; i++) {
        if (string(argv[i]) == "--from-global") {
            fg = true;
        }
    }
    solve(fg);
}

