// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

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

int ilg2(ll x) {
    return sizeof(ll) * 8 - __builtin_clzll(x | 1) - 1;
}

// Insert-only hashmap
template <typename K, typename V, K Sentinel>
struct hashmap0 {
    struct entry {
        K key;
        V value;
    };

    int psz;
    ll taken = 0;
    ull seed = 0;
    vector<entry> table;

    hashmap0(ll size) : psz(ilg2(size)), table(1 << psz, {Sentinel, {}}) {
    }

    optional<V> get(K k) {
        ull h = fasthash<K>()(k) & (~0ull << psz);

        while (table[h].key != k && table[h].key != Sentinel)
            h = (h + 1) & (~0ull << psz);

        if (table[h].key == Sentinel) {
            return {};
        } else {
            return table[h].value;
        }
    }

    V& operator[](K k) {
        ull h = fasthash<K>()(k) & ~(~0ull << psz);

        while (table[h].key != k && table[h].key != Sentinel)
            h = (h + 1) & ~(~0ull << psz);

        if (table[h].key == Sentinel) {
            table[h].key = k;
        }

        return table[h].value;
    }
};

template <typename K, typename V>
using opt_hashmap0 = hashmap0<optional<K>, V, optional<K>{}>;

void solve() {
    ll n;
    cin >> n;

    {
        vector<ll> mp0(n * 2 + 1);

        auto t0 = clock();
        for (ll j = 0; j < 1000; j++) {
            for (ll i = 0; i < n; i++) {
                mp0[n * 2 - i] = i;
            }
        }

        for (ll j = 0; j < 1000; j++) {
            for (ll i = 0; i < n; i++) {
                if (mp0[n * 2 - i] != i)
                    exit(-1);
            }
        }

        cout << "array finished in " << fl(clock() - t0) / CLOCKS_PER_SEC
             << endl;
    }

    {
        hashmap0<unsigned long, ll, 0> mp(n * 100);

        auto t0 = clock();
        for (ll j = 0; j < 1000; j++) {
            for (ll i = 0; i < n; i++) {
                mp[hash<ll>()(i * i)] = i;
            }
        }

        for (ll j = 0; j < 1000; j++) {
            for (ll i = 0; i < n; i++) {
                if (mp[hash<ll>()(i * i)] != i)
                    exit(-1);
            }
        }

        cout << "my map finished in " << fl(clock() - t0) / CLOCKS_PER_SEC
             << endl;
    }

    {
        unordered_map<ll, ll> mp2;

        auto t0 = clock();
        for (ll j = 0; j < 1000; j++) {
            for (ll i = 0; i < n; i++) {
                mp2[hash<ll>()(i * i)] = i;
            }
        }

        for (ll j = 0; j < 1000; j++) {
            for (ll i = 0; i < n; i++) {
                if (mp2[hash<ll>()(i * i)] != i)
                    exit(-1);
            }
        }

        cout << "std unordered map finished in "
             << fl(clock() - t0) / CLOCKS_PER_SEC << endl;
    }

    {
        std::map<ll, ll> mp3;

        auto t2 = clock();
        for (ll j = 0; j < 1000; j++) {
            for (ll i = 0; i < n; i++) {
                mp3[hash<ll>()(i * i)] = i;
            }
        }

        for (ll j = 0; j < 1000; j++) {
            for (ll i = 0; i < n; i++) {
                if (mp3[hash<ll>()(i * i)] != i)
                    exit(-1);
            }
        }

        cout << "std map finished in " << fl(clock() - t2) / CLOCKS_PER_SEC
             << endl;
    }

    cout << "ok" << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
