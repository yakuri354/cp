#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <random>
#include <iomanip>
#include <chrono>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const ll INF = 2e18;
const ll MAXN = 2e5 + 5;
const ll MOD = 998244353;
const ll logn = 20;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int count(const vector<set<int>> &c, const vector<int> &deg, int n) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if ((int)c[i].size() != deg[i]) {
            ++cnt;
        }
    }

    return cnt;
}


void solve(bool ret) {
    int n, m, k;
    cin >> n >> m >> k;

    vector<pair<int, int>> edges(m);
    vector<int> deg(n);
    for (auto &[u, v] : edges) {
        cin >> u >> v;
        --u, --v;
        ++deg[u];
        ++deg[v];
    }

    if (ret) return;

    vector<int> a(m);
    vector<set<int>> c(n);
    vector<vector<int>> kek(n, vector<int>(k + 2));
    for (int i = 0; i < m; ++i) {
        a[i] = uniform_int_distribution<int>(1, k + 1)(rnd);
        auto [u, v] = edges[i];
        c[u].insert(a[i]);
        c[v].insert(a[i]);
        ++kek[u][a[i]];
        ++kek[v][a[i]];
    }

    int ans = count(c, deg, n);
    ld temp = 0.1;

    for (int it = 0;; ++it) {
        if (it % 100000 == 0) {
            cerr << count(c, deg, n) << ' ' << temp << '\n';
        }
        int i = uniform_int_distribution<int>(0, m - 1)(rnd), j = uniform_int_distribution<int>(1, k + 1)(rnd);
        int old = a[i];
        auto [u, v] = edges[i];
        if (kek[u][old] == 1) {
            c[u].erase(old);
        }
        if (kek[v][old] == 1) {
            c[v].erase(old);
        }
        --kek[u][old], --kek[v][old];

        a[i] = j;
        ++kek[u][j];
        ++kek[v][j];
        c[u].insert(j);
        c[v].insert(j);


        int cur = count(c, deg, n);

        if (uniform_real_distribution<ld>()(rnd) < exp((ans - cur) / temp)) {
            ans = cur;
            if (!ans) {
                break;
            }
        } else {
            if (kek[u][j] == 1) {
                c[u].erase(j);
            }
            if (kek[v][j] == 1) {
                c[v].erase(j);
            }
            --kek[u][j], --kek[v][j];

            a[i] = old;

            ++kek[u][old];
            ++kek[v][old];
            c[u].insert(old);
            c[v].insert(old);
        }

        temp *= 0.999999999;
    }

    if (count(c, deg, n) != 0) {
        cout << "GOVNOOOOOOOO\n";
    } else {
        for (int i = 0; i < m; ++i) {
            cout << a[i] << ' ';
        }
    }
    cout << '\n';
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

// #ifdef LOCAL
    freopen("d2.txt", "r", stdin);
    freopen("d2ans.txt", "a", stdout);
// #endif

    int T = 1;
    cin >> T;
    ll from = stoll(string(argv[1]));
    for (ll i = 0; i < T; i++) {
        solve(i < from);
    }

    return 0;
}