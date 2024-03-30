#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <array>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

namespace pbds {
    using namespace __gnu_pbds;
};

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

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
    ull operator()(const T& x) {
        return splitmix64(ull(x));
    }
};

template <typename T>
struct fasthash<T, typename std::enable_if<std::is_integral<T>::value>::type> {
    ull operator()(T x) {
        return splitmix64(ull(x));
    }
};

template <class Tuple, class F>
constexpr decltype(auto) for_each(Tuple&& tuple, F&& f) {
    return for_each_impl(
        std::forward<Tuple>(tuple), std::forward<F>(f),
        std::make_index_sequence<
            std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
}

template <class Tuple, class F, std::size_t... I>
F for_each_impl(Tuple&& tuple, F&& f, std::index_sequence<I...>) {
    (f(std::get<I>(tuple)), ...);
    return f;
}

template <typename... Args>
struct fasthash<const tuple<Args...>&> {
    ull operator()(const tuple<Args...>& t) {
        ull h = 0;
        for_each(t, [&h](auto x) {
            h = fasthash<ull>()(fasthash<decltype(x)>()(x) + h ^
                                ull(0x6d9cf82ee60abe9f));
        });
        return h;
    }
};

template <typename T, typename K>
// using hashmap = pbds::gp_hash_table<T, K, fasthash<K>>;
using hashmap = pbds::gp_hash_table<T, K, hash<K>>;

ll k, n, m, q;

const ll maxv = 50000ll * 5;
const ll maxk = 5;
const ll inf = 1e15;
const ll sq = 400;

vector<pll> g[maxv];

// ll dp[maxv]; // todo optimize

const ll dpdelta = 1e10;
ll pref = dpdelta;

void clear_dp() {
    pref += dpdelta;
}

bool here(ll v) {
    return (v / dpdelta) * dpdelta >= pref;
}

ll dfs_dist(ll v, ll bound, hashmap<ll, ll> &dp) {
    if (v > bound) return inf;
    if (dp.find(v) != dp.find_end()) return dp[v];

    dp[v] = inf;

    for (auto [u, w]: g[v]) {
        dp[v] = min(dp[v], dfs_dist(u, bound, dp) + w);
    }

    return dp[v];
}

ll next_bl[maxv][maxk];

void answer(ll a) {
    if (a >= inf) {
        cout << "-1\n";
    } else {
        cout << a << '\n';
    }
}

void solve() {
    cin >> k >> n >> m >> q;

    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
    
        g[a].push_back({b, c});
    }

    for (ll i = sq * k; i + k <= n; i += sq * k) {
        ll prev = i - sq * k;

        for (ll z = 0; z < k; z++) {
            hashmap<ll, ll> dp;
            dp[i + z] = 0;

            for (ll j = 0; j < k; j++) {
                next_bl[prev + j][z] = dfs_dist(prev + j, i + k, dp);
            }
        }
    }

    for (ll qi = 0; qi < q; qi++) {
        ll u, v;
        cin >> u >> v;

        if (v < u || v / k == u / k) {
            answer(inf);
            continue;
        }

        if (v / (k * sq) == u / (k * sq)) {
            hashmap<ll, ll> dp;
            dp[v] = 0;
            answer(dfs_dist(u, v + k, dp));
            continue;
        }

        ll nx = (u / (k * sq) + 1) * k * sq;

        array<ll, maxk> dist0{};

        for (ll i = 0; i < k; i++) {
            hashmap<ll, ll> dp;
            dp[nx + i] = 0;
            dist0[i] = dfs_dist(u, nx + k + i, dp);
        }

        while (nx + (k * sq) < v) {
            array<ll, maxk> dist1;
            dist1.fill(inf);
            for (ll i = 0; i < k; i++) {
                for (ll j = 0; j < k; j++) {
                    dist1[i] = min(dist1[i], dist0[j] + next_bl[nx + j][i]);
                }
            }
            dist0 = dist1;
            nx += k * sq;
        }

        hashmap<ll, ll> dp;
        dp[v] = 0;
        ll ans = inf;
        for (ll i = 0; i < k; i++) {
            ans = min(ans, dist0[i] + dfs_dist(nx + i, v + k, dp));
        }

        answer(ans);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

