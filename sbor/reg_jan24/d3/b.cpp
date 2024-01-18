// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <queue>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 100;

using si = basic_string<int>;

ll a[maxn], n;

vector<pair<ll, ll>> ans;

struct ent {
    si s;
    ll depth;
};

void solve_small() {
    si s0(a, a + n);

    queue<ent> q;
    q.push({s0, 0});
    map<si, pair<ll, ll>> parent;
    set<si> used;
    
    while (!q.empty()) {
        ent curr = q.front();
        q.pop();

        if (used.count(curr.s)) continue;
        used.insert(curr.s);

        if (curr.depth > 23000) {
            continue;
        }

        if (is_sorted(curr.s.begin(), curr.s.end(), greater<>())) {
            si s1 = curr.s;
            vector<pair<ll, ll>> ans;
            
            while (s1 != s0) {
                ans.push_back(parent[s1]);
                swap(s1[parent[s1].first], s1[parent[s1].second]);
            }

            reverse(ans.begin(), ans.end());

            cout << "YES" << '\n';
            cout << ans.size() << '\n';

            for (auto [a, b]: ans) {
                if (a > b) swap(a, b);
                cout << a + 1 << ' ' << b + 1 << '\n';
            }

            exit(0);
        }

        for (ll i = 0; i < n; i++) {
            if (i + 3 < n) {
                si s1 = curr.s;
                swap(s1[i], s1[i+3]);
                if (!parent.count(s1)) {
                    q.push({s1, curr.depth + 1});
                    parent[s1] = {i, i + 3};
                }
            }

            if (i + 4 < n) {
                si s1 = curr.s;
                swap(s1[i], s1[i+4]);
                if (!parent.count(s1)) {
                    q.push({s1, curr.depth + 1});
                    parent[s1] = {i, i + 4};
                }
            }
        }
    }

    cout << "NO" << endl;
    exit(0);
}

void solve_large() {
    while (!is_sorted(a, a + n, greater<>())) {
        for (ll i = 0; i < n; i++) {
            if (a[i] < a[i+1]) {
                if (i + 4 < n) {
                    ans.push_back({i, i + 4});
                    swap(a[i], a[i+4]);
                    ans.push_back({i+1, i+4});
                    swap(a[i+1], a[i+4]);
                    ans.push_back({i, i + 4});
                    swap(a[i], a[i+4]);
                } else if (i - 3 >= 0) {
                    ans.push_back({i+1, i - 3});
                    swap(a[i+1], a[i-3]);
                    ans.push_back({i, i-3});
                    swap(a[i], a[i-3]);
                    ans.push_back({i+1, i - 3});
                    swap(a[i+1], a[i-3]);
                } else {
                    exit(-1);
                }
            }
        }
    }

    if (ans.size() > 23000) {
        cout << "NO" << endl;
        return;
    } else {
        cout << "YES\n" << ans.size() << '\n';
        for (auto [a, b]: ans) {
            if (a > b) swap(a, b);
            cout << a + 1 << ' ' << b + 1 << '\n';
        }
    }
}

void solve() {
    cin >> n;
    
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n < 8) solve_small();
    else solve_large();
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
