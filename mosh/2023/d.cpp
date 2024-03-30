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
#include <iomanip>
#include <fstream>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

const ll inf = 1e12;

string taskid;

uniform_real_distribution<float> fld(0, 1);

bool F(fl temp, ll olds, ll news, mt19937_64 &mt) {
    return news > olds || pow(fl(news) / fl(olds), 1/temp) > fld(mt);
}

vector<string> S;
vector<string> A;

struct state {
    vector<ll> breaks;

    template<typename F>
    void write_out(F f) {
    }
};

ll curr_score = inf;
ll global_best = inf;
fl temp;

void print_msg() {
    cout << "\33[2K\r";
    cout << setw(20) << temp << " " << setw(20) << global_best << " (" << setw(20) << curr_score << ")" << flush;
}

ll read_global_best(ll t) {
    auto fname = "ans/" + taskid + "/" + to_string(t) + "_score.txt";
    fstream fin(fname);
    if (fin.good() || !fin.eof()) {
        fin >> global_best;
    }
    return global_best;
}

ll save(ll t) {
    auto fname1 = "ans/" + taskid + "/" + to_string(t) + "_score.txt";
    ofstream fsc(fname1);
    fsc << global_best;

}

void solve(ll t) {
    ll n;
    cin >> n;

    cout << "==== STARTING TEST CASE " << t << " ====" << endl;

    // init

    uniform_int_distribution<ll> nd(0, n - 1);

    ll seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937_64 mt(seed);

    cout << "seed " << seed << endl;

    cout << endl;
    temp = 10;
    for (ll its = 0;temp > 1e-5;its++) {
        if (its % 100000 == 0) {
        }

        ll aa = nd(mt), bb = aa;
        while (aa / 3 == bb / 3) bb = nd(mt);

        ll old_score = curr_score;

        if (!F(temp, old_score, curr_score, mt)) {
            
        }

        if () {
            best_st = state;
            ans = ord;
        }

        temp *= 0.9999999;
    }

    cout << endl << endl;
    cout << "==== END ====" << endl;

    for (ll i = 0; i < n; i += 3) {
        cerr << ans[i] + 1 << ' ' << ans[i+1] + 1 << ' ' << ans[i+2] + 1 << '\n';
        cout << ans[i] + 1 << ' ' << ans[i+1] + 1 << ' ' << ans[i+2] + 1 << endl;
    }

    cerr << endl;
    cout << endl << endl;
}

int main(int argc, char **argv) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    taskid = string(argv[1]);
    ll t;
    cin >> t;
    for (ll i = 0; i < t; i++) {
        solve();
    }
}


