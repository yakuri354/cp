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
using pll = pair<ll, ll>;

using bs = bitset<60>;

vector<bs> rows, cols;
ll n, x;

ll score() {
    // n in row & column is not an invariant
    ll e1 = 0, e2 = 0;
    for (ll i = 0; i < x; i++) {
        if (rows[i].count() != n) e2++;
        for (ll j = i + 1; j < x; j++) {
            ll c = (rows[i] & rows[j]).count();
            if (c != 0 && c != 2) e1++;
        }
    }

    for (ll i = 0; i < x; i++) {
        if (cols[i].count() != n) e2++;
        for (ll j = i + 1; j < x; j++) {
            ll c = (cols[i] & cols[j]).count();
            if (c != 0 && c != 2) e1++;
        }
    }

    return e1 + e2 * 100;
}

void print_state() {
    for (ll i = 0; i < x; i++) {
        for (ll j = 0; j < x; j++) {
            if (rows[i][j] != cols[j][i]) {
                cout << "PROLAPSE DETECTED" << endl;
                exit(-1);
            }
            cout << (rows[i][j] ? 'x' : '.');
        }
        cout << '\n';
    }
    cout << flush;
}

void solve() {
    cout << "n? ";
    cin >> n;
    cout << "x? ";
    cin >> x;

    rows.resize(x);
    cols.resize(x);

    fl temp = 100;

    uniform_int_distribution<ll> xd(0, x - 1);
    uniform_real_distribution<fl> fd;
    mt19937_64 mt(random_device{}());

    ll state = score();

    for (ll it = 1;; it++) {
        if (it % 100000 == 0) {
            cout << "it = " << it << endl << "t  = " << temp << endl << "s  = " << state << endl << endl;
            
            print_state();
            cout << endl;
        }

        ll ii = xd(mt), jj = xd(mt);

        rows[ii][jj].flip();
        cols[jj][ii].flip();

        ll ns = score();

        if (ns == 0) break;

        if (ns < state || exp(fl(state - ns) / temp) > fd(mt)) {
            state = ns;
        } else {
            rows[ii][jj].flip();
            cols[jj][ii].flip();
        }

        temp *= 0.9999999;
    }

    cout << "done" << endl;
    print_state();   
}

int main() {
    // ll t; cin >> t; while (t --> 0)
    solve();
}

