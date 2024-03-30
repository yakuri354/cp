#pragma GCC optimize("Ofast")

#include <algorithm>
#include <cstddef>
#include <ctime>
#include <ios>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <random>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
const ll INF = 1e15 + 21;
const ll MAXN = 1e5 + 5;

ull splitmix64(ull s) {
    ull z = s + 0x9e3779b97f4a7c15;
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

template <typename T, typename = void>
struct fasthash;

template <typename T>
struct fasthash<const T&,
                typename std::enable_if<std::is_integral<T>::value>::type> {
    ull operator()(const T& x) const {
        return splitmix64(ull(x));
    }
};

template <typename T>
struct fasthash<T, typename std::enable_if<std::is_integral<T>::value>::type> {
    ull operator()(T x) const {
        return splitmix64(ull(x));
    }
};

typedef pair<ll, ll> pii;
typedef cc_hash_table<ll, ll, fasthash<ll>> ht;

ll N, Q;
ll V[MAXN];
ll C[MAXN];
ll dp[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
    for (ll i = 0; i < N; i++) {
        cin >> V[i];
    }
    for (ll i = 0; i < N; i++) {
        cin >> C[i];
    }
    ht curMax;
    for (int i = 0; i < N; i++) {
        curMax[C[i]] = -INF;
    }
    for (ll i = 0; i < Q; i++) {
        for (auto j : curMax) {
            curMax[j.first] = -INF;
        }
        ll a, b;
        cin >> a >> b;
        fill(dp, dp + N, -1);
        pii mx1 = {0, 1e5 + 5};
        pii mx2 = {0, 1e5 + 4};
        for (ll j = 0; j < N; j++) {
            if (mx1.second == C[j]) {
                dp[j] = mx2.first + b * V[j];
            } else {
                dp[j] = mx1.first + b * V[j];
            }
            dp[j] = max(dp[j], curMax[C[j]] + a * V[j]);
            if (dp[j] > mx1.first) {
                if (C[j] == mx1.second) {
                    mx1 = {dp[j], C[j]};
                } else {
                    mx2 = {mx1.first, mx1.second};
                    mx1 = {dp[j], C[j]};
                }
            } else if (dp[j] > mx2.first) {
                if (C[j] == mx1.second) {
                    continue;
                } else {
                    mx2 = {dp[j], C[j]};
                }
            }
            curMax[C[j]] = max(curMax[C[j]], dp[j]);
        }
        cout << mx1.first << endl;
    }
}
