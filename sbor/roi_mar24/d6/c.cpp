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
#include <fstream>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

struct pt {
    ll i, j;
};

struct nest {
    ll i, j, c;
};

const ll maxnm = 110;
bool st[maxnm][maxnm], is_n[maxnm][maxnm];
ll reach[maxnm][maxnm], want[maxnm][maxnm];
ll perfect = 0;
ll score = 0;

ll n, m, k, W;

ll sqr(ll x) {
    return x * x;
}

void toggle(pt p) {
    st[p.i][p.j] ^= 1;

    for (ll i = 0; i < n; i++) {
        if (is_n[i][p.j]) {
            if (reach[i][p.j] == want[i][p.j]) perfect--;
            score -= abs(want[i][p.j] - reach[i][p.j]);
        }
        reach[i][p.j] = 0;
    }

    for (ll j = 0; j < m; j++) {
        if (is_n[p.i][j]) {
            if (reach[p.i][j] == want[p.i][j]) perfect--;
            score -= abs(want[p.i][j] - reach[p.i][j]);
        }
        reach[p.i][j] = 0;
    }

    ll last = -1;
    for (ll i = 0; i < n; i++) {
        if (st[i][p.j]) last = i;
        if (is_n[i][p.j] != 0) reach[i][p.j] += abs(i - last - 1);
    }

    last = n;

    for (ll i = n - 1; i >= 0; i--) {
        if (st[i][p.j]) last = i;
        if (is_n[i][p.j] != 0) reach[i][p.j] += abs(last - i - 1);
    }

    last = -1;

    for (ll j = 0; j < m; j++) {
        if (st[p.i][j]) last = j;
        if (is_n[p.i][j] != 0) reach[p.i][j] += abs(j - last - 1);
    }

    last = m;

    for (ll j = m - 1; j >= 0; j--) {
        if (st[p.i][j]) last = j;
        if (is_n[p.i][j] != 0) reach[p.i][j] = abs(last - j - 1);
    }

    for (ll j = 0; j < m; j++) {
        if (is_n[p.i][j]) {
            if (reach[p.i][j] == want[p.i][j]) perfect++;
            score += sqr(reach[p.i][j] - want[p.i][j]); // mb square
        }
    }

    for (ll i = 0; i < n; i++) {
        if (is_n[i][p.j]) {
            if (reach[i][p.j] == want[i][p.j]) perfect++;
            score += sqr(reach[i][p.j] - want[i][p.j]); // mb square
        }
    }
}

void full_calc() {
    perfect = 0;
    score = 0;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            reach[i][j] = 1;

            if (is_n[i][j]) {
                st[i][j] = false;
            }
        }
    }

    for (ll i = 0; i < n; i++) {
        ll last = -1;
        for (ll j = 0; j < m; j++) {
            if (st[i][j]) last = j;
            reach[i][j] += j - last - 1;
        }

        last = m;

        for (ll j = m - 1; j >= 0; j--) {
            if (st[i][j]) last = j;
            reach[i][j] += last - j - 1;
        }
    }

    for (ll j = 0; j < m; j++) {
        ll last = -1;
        for (ll i = 0; i < n; i++) {
            if (st[i][j]) last = i;
            reach[i][j] += i - last - 1;
        }

        last = n;

        for (ll i = n - 1; i >= 0; i--) {
            if (st[i][j]) last = i;
            reach[i][j] += last - i - 1;
        }
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (is_n[i][j]) {
                score += sqr(reach[i][j] - want[i][j]);
                perfect += reach[i][j] == want[i][j];
            }
        }
    }
}

string testn;
ll best = 0, lb = 0;

void save_out() {
    ofstream fo(testn);

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (st[i][j]) fo << '#';
            else fo << '.';
        }
        fo << '\n';
    }
    fo << flush;

    ofstream bb("best/" + testn);
    bb << best << endl;
}

fl loss() {
    // return -(perfect * 1000000) + score;
    return score - 100 * perfect;
    // return -exp(perfect) + fl(score);
}

void solve() {
    cin >> n >> m >> k >> W;

    vector<nest> ns(k);
    for (auto &[i, j, c]: ns) {
        cin >> i >> j >> c;
        i--, j--;
    }

    for (auto x: ns) {
        reach[x.i][x.j] = n + m - 2;
        is_n[x.i][x.j] = true;
        want[x.i][x.j] = x.c;
    }

    full_calc();

    mt19937_64 mt{random_device()()};
    uniform_real_distribution<float> fd(0, 1);
    fl temp = 10;
    for (ll it = 0;perfect < W; it++) {
        if (perfect > lb) {
            cout << "-- best --" << endl << " -> " << perfect << endl << endl;
            if (perfect > best) {
                cout << "---------------- NEW BEST GLOBAL ------------------" << endl;
                save_out();
                best = perfect;
            }
            lb = perfect;
        }

        if (it % 40000 == 0) {
            cout << "temp " << temp << endl;
            cout << "s " << score << "; p " << perfect << "/" << W << "; l " << loss() << endl;
        }

        ll ii = uniform_int_distribution<ll>(0, n - 1)(mt);
        ll jj = uniform_int_distribution<ll>(0, m - 1)(mt);
        
        if (is_n[ii][jj]) continue;

        fl olds = loss();
        // toggle({ii, jj});
        st[ii][jj] ^= 1;
        full_calc();
        fl news = loss();

        // if (olds < news) {
        //     cout << "Bad transition: " << exp(fl(olds-news) / temp) << endl;
        // }

        if (news < olds || exp(fl(olds - news) / temp) > fd(mt)) {
            // todo
        } else {
            st[ii][jj] ^= 1;
            full_calc();
        }

        // temp = fl(100) / (1 + log(1 + fl(it) / 10));
        // temp = fl(1000) / (1 + pow(fl(it), 0.3));
        temp *= 0.9999999;
    }

    cout << "all perfect" << endl;
    save_out();

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (st[i][j]) cerr << '#';
            else cerr << '.';
        }
        cerr << '\n';
    }
    cerr << flush;
}

int main(int argc, char **argv) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    testn = string(argv[1]);
    ifstream bb("best/" + testn);
    if (!bb.good()) {
        best = 0;
    } else {
        bb >> best;
    }
    
    solve();
}

