// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <map>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

struct v2;

using pt = v2;

const fl eps = 1e-9;

bool zero(fl x) {
    return abs(x) < eps;
}

struct v2 {
    fl x, y;

    ll ix = 0;

    v2(fl x, fl y) : x(x), y(y) {
    }

    v2() : x(0), y(0) {
    }

    fl dot(const v2& other) const {
        return x * other.x + y * other.y;
    }

    fl operator*(const v2& other) const {
        return dot(other);
    }

    fl cross(const v2& other) const {
        return x * other.y - y * other.x;
    }

    fl operator%(const v2& other) const {
        return cross(other);
    }

    v2 operator-(const v2& other) const {
        return {x - other.x, y - other.y};
    }

    v2 operator+(const v2& other) const {
        return {x + other.x, y + other.y};
    }

    v2 operator*(fl k) const {
        return {x * k, y * k};
    }

    v2 operator/(fl k) const {
        return {x / k, y / k};
    }

    fl len() const {
        return hypotl(x, y);
    }

    bool operator==(const v2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const v2& other) const {
        return this->cross(other) > 0;
    }

    bool operator>(const v2& other) const {
        return this->cross(other) < 0;
    }

    bool operator<=(const v2& other) const {
        return *this < other || colin(other);
    }

    bool operator>=(const v2& other) const {
        return *this > other || colin(other);
    }

    bool colin(const v2& other) const {
        return zero(this->cross(other));
    }

    bool codir(const v2& other) const {
        return colin(other) && dot(other) > 0;
    }

    v2 unit_dir() const {
        return *this / len();
    }

    v2 norm() const {
        return {-y, x};
    }

    bool between_strict(const v2& a, const v2& b) const {  // sus
        if (a < b)
            return between_strict(b, a);
        return a > *this && *this > b;  // || between_strict(b, a);
    }

    bool between_weak(const v2& a, const v2& b) const {  // sus
        if (a < b)
            return between_weak(b, a);
        return a >= *this && *this >= b;  // || between_weak(b, a);
    }

    v2 rot(fl ang) const {  // really bad, rewrite + super sus
        fl alpha = v2{1, 0}.angle(*this);
        fl l = len();

        v2 ans = {l * cos(alpha + ang), l * sin(alpha + ang)};
        return ans;
    }

    fl angle(const v2& other) const {
        return atan2l(cross(other), dot(other));
    }

    fl angle360(const v2& other) const {
        fl ang = angle(other);
        if (ang < 0)
            ang += 360;
        return ang;
    }

    v2 to(const v2& other) const {
        return other - *this;
    }

    pair<fl, fl> to_pair() const {
        return make_pair(x, y);
    }
};

template<typename T>
using st = unordered_set<T>;

template<typename K, typename V>
using mp = unordered_map<K, V>;

ll N, t;

vector<v2> ps;

const ll maxn = 1001;

struct state {
    ll ci, ni;

    bool operator<(const state &o) const {
        return make_pair(ci, ni) < make_pair(o.ci, o.ni);
    }

    bool operator==(const state &o) const {
        return make_pair(ci, ni) == make_pair(o.ci, o.ni);
    }

    ll to_n() const {
        return ci * maxn + ni;
    }
};

template <>
struct std::hash<state>
{
  std::size_t operator()(const state& k) const
  {
    using std::size_t;
    using std::hash;
    using std::string;

    // Compute individual hash values for first,
    // second and third and combine them using XOR
    // and bit shifting:

    return ((hash<ll>()(k.ci)
             ^ (hash<ll>()(k.ni) << 1)) >> 1);
  }
};

vector<vector<v2>> arr_srt;

const v2 base_dir = {0, 1};

void precalc(ll ni) {
    auto nxt = ps[ni];
    auto ph = ps;

    auto dir = base_dir;

    ph.erase(find_if(ph.begin(), ph.end(), [&](v2 x) { return x.ix == ni; }));

    sort(ph.begin(), ph.end(), [&](v2 a, v2 b) {
        fl ad = dir.angle360(nxt.to(b)) - dir.angle360(nxt.to(a));

        if (zero(ad)) {
            return nxt.to(a).len() < nxt.to(b).len();
        } else {
            return ad > 0;
        }
    });

    arr_srt[ni] = ph;
}

state fast_nx(state s) {
    v2 curr = ps[s.ci], nxt = ps[s.ni];

    v2 dir = curr.to(nxt);
    auto &ar = arr_srt[s.ni];

    fl ad = base_dir.angle360(dir);

    ll first_idx = lower_bound(ar.begin(), ar.end(), 0, [&](v2 a, ll _) {
        return base_dir.angle360(nxt.to(a)) + eps < ad; // sus
    }) - ar.begin();

    return {s.ni, ar[(first_idx + t) % ar.size()].ix};
}

//mp<state, state> nst;

state edge[maxn][maxn];

state &nst(state x) {
    return edge[x.ci][x.ni];
}

struct zref;

struct vst {
    vector<ll> x;
    ll cnt = 0, gen = 1;

    vst(): x(maxn * maxn, 0) {};

    void set(const state &s, bool v) {
        if (v) {
            x[s.to_n()] = gen;
        } else {
            x[s.to_n()] = 0;
        }
    }

    bool get(const state &s) const {
        return x[s.to_n()] == gen;
    }

    bool empty() const {
        return find(x.begin(), x.end(), gen) == x.end();
    }

    void reset() {
        gen++;
    }
};

vst cyc_used{};
vector<bool> ans_cyc;

vector<state> cyc_begins;

void mark_cycle(state curr, state begin) {
    if (curr == begin) return;
    ans_cyc[curr.ci] = true;
    mark_cycle(nst(curr), begin);
}

void dfs_cycles(state c, vst &used) {
    if (used.get(c)) {
        // cyc = {state{c.ci, c.ni}};
        ans_cyc[c.ci] = true;
        cyc_begins.push_back(c);
        mark_cycle(nst(c), c);
        return;
    }

    used.set(c, true);

    if (cyc_used.get(c)) return;
    cyc_used.set(c, true);

    dfs_cycles(nst(c), used);
}

vector<state> adj[maxn * maxn];

vector<bool> ans_twice;

void dfs_twice(state c, vst &used_st, vector<ll> &used_init) {
    if (used_st.get(c)) return;
    used_st.set(c, true);

    if (used_init[c.ci] > 0) {
        ans_twice[c.ci] = true;
    }

    used_init[c.ci]++;

    for (const auto &st: adj[c.to_n()]) {
        dfs_twice(st, used_st, used_init);
    }

    used_init[c.ci]--;
}

void solve() {
    cin >> N >> t;
    t--;

    arr_srt.resize(N);
    ans_cyc.resize(N);
    ans_twice.resize(N);

    for (ll i = 0; i < N; i++) {
        ll x, y;
        cin >> x >> y;

        ps.push_back(pt(x, y));
        ps.back().ix = i;
    }

    for (ll ni = 0; ni < N; ni++) {
        precalc(ni);
    }

    for (ll ci = 0; ci < N; ci++) {
        for (ll ni = 0; ni < N; ni++) {
            if (ci == ni) continue;

            nst({ci, ni}) = fast_nx({ci, ni});
        }
    }

    vst used;

    for (ll ci = 0; ci < N; ci++) {
        for (ll ni = 0; ni < N; ni++) {
            if (ci == ni) continue;
            used.reset();

            dfs_cycles({ci, ni}, used);
        }
    }

    for (ll ci = 0; ci < N; ci++) {
        for (ll ni = 0; ni < N; ni++) {
            adj[nst({ci, ni}).to_n()].push_back({ci, ni});
        }
    }

    vector<ll> used_init(N);
    for (auto &cc : cyc_begins) {
        used.reset();
        dfs_twice(cc, used, used_init);
    }

    // for (ll ci = 0; ci < n; ci++) {
    //     for (ll ni = 0; ni < n; ni++) {
    //         if (ci == ni) continue;
    //         set<state> used;
    //         set<ll> used_init, res;

    //         dfs_once({ci, ni}, used, used_init, res);

    //         for (ll x: res) {
    //             if (!ans_cyc.count(x)) {
    //                ans_twice.insert(x);
    //             }
    //         }
    //     }
    // }

    for (ll i = 0; i < N; i++) {
        if (ans_cyc[i]) {
            cout << "G";
        } else if (ans_twice[i]) {
            cout << "B";
        } else {
            cout << "R";
        }
    }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
