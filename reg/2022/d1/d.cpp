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

ll N, t;

vector<v2> ps;

struct state {
    ll ci, ni;

    bool operator<(const state &o) const {
        return make_pair(ci, ni) < make_pair(o.ci, o.ni);
    }

    bool operator==(const state &o) const {
        return make_pair(ci, ni) == make_pair(o.ci, o.ni);
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

template<typename T>
using st = set<T>;

template<typename K, typename V>
using mp = map<K, V>;

mp<ll, vector<v2>> arr_srt;

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

mp<state, state> nst;

void mark_cycle(state curr, state begin, st<state> &cycle) {
    if (curr == begin) return;
    cycle.insert(curr);
    mark_cycle(nst[curr], begin, cycle);
}

st<state> cyc_used;

void dfs_cycles(state c, st<state> &used, st<state> &cyc) {
    if (used.count(c)) {
        cyc = {state{c.ci, c.ni}};
        mark_cycle(nst[c], c, cyc);
        return;
    }
    used.insert(c);

    if (cyc_used.count(c)) return;
    cyc_used.insert(c);

    dfs_cycles(nst[c], used, cyc);
}

void dfs_once(state c, st<state> &used_st, st<ll> &used_init, st<ll> &ans) {
    if (used_st.count(c)) return;
    used_st.insert(c);

    if (used_init.count(c.ci)) {
        ans.insert(c.ci);
    }

    used_init.insert(c.ci);
    dfs_once(nst[c], used_st, used_init, ans);
}

void solve() {
    cin >> N >> t;
    t--;

    for (ll i = 0; i < N; i++) {
        ll x, y;
        cin >> x >> y;

        ps.push_back(pt(x, y));
        ps.back().ix = i;
    }

    // for (ll ci = 0; ci < n; ci++) {
    //     for (ll ni = 0; ni < n; ni++) {
    //         if (ci == ni) continue;

    //         nst[{ci, ni}] = nx_pt({ci, ni});
    //     }
    // }

    for (ll ni = 0; ni < N; ni++) {
        precalc(ni);
    }

    for (ll ci = 0; ci < N; ci++) {
        for (ll ni = 0; ni < N; ni++) {
            if (ci == ni) continue;

            nst[{ci, ni}] = fast_nx({ci, ni});
        }
    }

    st<ll> ans_cyc, ans_twice;

    for (ll ci = 0; ci < N; ci++) {
        for (ll ni = 0; ni < N; ni++) {
            if (ci == ni) continue;

            st<state> cyc, used;

            dfs_cycles({ci, ni}, used, cyc);

            for (state x: cyc) {
                ans_cyc.insert(x.ci);
            }
        }
    }

    for (ll ci = 0; ci < N; ci++) {
        for (ll ni = 0; ni < N; ni++) {
            if (ci == ni) continue;
            st<state> used;
            st<ll> used_init, res;

            dfs_once({ci, ni}, used, used_init, res);

            for (ll x: res) {
                if (!ans_cyc.count(x)) {
                   ans_twice.insert(x);
                }
            }
        }
    }

    for (ll i = 0; i < N; i++) {
        if (ans_cyc.count(i)) {
            cout << "G";
        } else if (ans_twice.count(i)) {
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
