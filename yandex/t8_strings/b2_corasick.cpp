// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
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

const ll sigma = 26;

template<typename T, void *arr, ll *sz>
struct ap {
    typedef ap<T, arr, sz> self;

    int i;

    ap(): i(-1) {}
    ap(T* ptr): i(ptr - (T*)arr) {}
    ap(int i): i(i) {}

    // T operator*() const {
    //     #ifdef DBG
    //     if (i == -1) exit(-1);
    //     #endif
    //     return *((T*)arr + i);
    // }

    T* operator->() const {
        #ifdef DBG
        if (i == -1) exit(-1);
        #endif
        return (T*)arr + i;
    }

    explicit operator bool() const {
        return i != -1;
    }

    bool operator!() const {
        return i == -1;
    }

    bool operator==(const self &other) const {
        return i == other.i;
    }

    bool operator!=(const self &other) const {
        return i != other.i;
    }

    template <typename ...Args>
    static self alloc(Args ...args) {
        (*sz)++;
        new((T*)arr + (*sz - 1ll)) T(args...);
        return self(*sz - 1ll);
    }
};

template<void* arr, ll *sz>
struct node {
    typedef node<arr, sz> Self;
    typedef ap<Self, arr, sz> np;

    int c;
    vector<int> term{};
    np suff = 0, exit = 0, p{};

    array<np, sigma> fail{}, nx{};

    node(Self &_) = delete;
    node(Self &&_) = delete;

    node(int c, np par) : c(c) {
        if (!par) {
            p = this;
            exit = this;
            suff = this;
        } else {
            p = par;
        }
    }

    np link() {
        if (!suff) {
            if (p->p == p) { // 1 char string
                suff = p;
            } else {
                suff = p->link()->go(c);
            }
        }
        return suff;
    }

    np go(ll x) {
        if (!fail[x]) {
            if (nx[x]) {
                fail[x] = nx[x];
            } else if (p == this) {
                fail[x] = this;
            } else {
                fail[x] = link()->go(x);
            }
        }

        return fail[x];
    }

    np next_term() {
        if (!exit) {
            if (!link()->term.empty()) {
                return link();
            } else {
                return link()->next_term();
            }
        }
        
        return exit;
    }

    void add(string& s, ll idx) {
        np t = this;

        for (char _c : s) {
            int c = _c - 'a';
            if (!t->nx[c]) {
                t->nx[c] = np::alloc(c, t);
            }

            t = t->nx[c];
        }

        t->term.push_back(idx);
    }
};

const ll maxn = 1e6 + 2;

char mem[maxn * sizeof(node<nullptr, nullptr>)];

ll sz = 0;

using cn = node<(void*) mem, &sz>;
using cnp = cn::np;

void solve() {
#ifdef DBG
#define fin cin
#define fout cout
#else
    fstream fin("inputik.txt");
    fstream fout("outputik.txt");
#endif

    string t;
    fin >> t;

    ll n;
    fin >> n;

    cnp root = cnp::alloc(-1, cnp());

    vector<ll> sz(n);

    for (ll i = 0; i < n; i++) {
        string s;
        fin >> s;

        sz[i] = s.size();

        root->add(s, i);
    }

    vector<vector<ll>> ans(n);

    volatile cn _rt(-1, cnp());

    cnp curr = root;
    for (ll i = 0; i < t.size(); i++) {
        curr = curr->go(t[i] - 'a');

        cnp top = curr;
        while (top->p != top) {
            for (ll x: top->term) {
                ans[x].push_back(i - sz[x] + 1);
            }
            top = top->next_term();
        }
    }

    for (ll i = 0; i < n; i++) {
        fout << ans[i].size() << ' ';
        for (ll j : ans[i]) {
            fout << j + 1 << ' ';
        }
        fout << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
