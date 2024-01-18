#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <ctime>
#include <exception>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <ostream>
#include <random>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <optional>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

#ifdef DBG
#define inv(x)                                                       \
    if (!(x)) {                                                      \
        cerr << "invariant " #x " violated at " << __LINE__ << endl; \
        exit(-1);                                                    \
    }
#else
#define inv(x)
#endif

const ll inf = INT32_MAX;
const fl eps = 1e-9;
const fl max_abs_c = 1e9;

mt19937_64 mt(228);

bool zero(fl x) {
    return abs(x) < eps;
}

struct v2;
struct segment;
struct ray;
struct polygon;
struct convex_poly;

using pt = v2;

struct v2 {
    fl x, y;

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
        inv(angle(ans) == ang);
        return ans;
    }

    fl angle(const v2& other) const {
        return atan2l(cross(other), dot(other));
    }

    v2 to(const v2& other) const {
        return other - *this;
    }

    static pt random() {
        uniform_real_distribution<fl> fd(-max_abs_c, max_abs_c);
        return pt(fd(mt), fd(mt));
    }

    pair<fl, fl> to_pair() const {
        return make_pair(x, y);
    }
};

istream& operator>>(istream& s, v2& v) {
    return s >> v.x >> v.y;
}

ostream& operator<<(ostream& s, const v2& v) {
    return s << v.x << ' ' << v.y;
}

struct line {
    fl a, b, c;

    line(pt p1, pt p2) : a(p1.y - p2.y), b(p2.x - p1.x), c(-(p1.x * a + p1.y * b)) {
    }

    v2 norm() const {
        return {a, b};
    }

    v2 dir() const {
        return {b, -a};
    }

    optional<fl> l_k() const {
        if (zero(b)) return {};
        return {-a / b};
    }

    pt proj(const pt& p) const {
        if (has(p))
            return p;

        auto ix = intersection(line(p, p + norm()));

        inv(ix.has_value());

        return ix.value();
    }

    bool has(const pt& p) const {
        return zero(a * p.x + b * p.y + c);
    }

    optional<pt> intersection(const line& other) const { // fixme
        if (norm().colin(other.norm())) {
            return {};
        }

        fl k = a * other.b - b * other.a;
        inv(k != 0);
        
        return v2{b * other.c - c * other.b, c * other.a - a * other.c} / k;
    }
};

struct ray {
    v2 origin, dir;

    ray(pt origin, pt dir) : origin(origin), dir(dir) {
    }

    bool intersects(const segment& seg) const;

    bool has(const pt& p) const {
        return origin.to(p).codir(dir);
    }
};

struct segment {
    v2 a, b;

    segment() : a(), b() {
    }

    segment(pt a, pt b) : a(a), b(b) {
    }
    
    line to_line() const {
        return line(a, b);
    }

    bool has(const pt& p) const {
        return ray(a, a.to(b)).has(p) && ray(b, b.to(a)).has(p);
    }

    bool intersects(const ray& r) const {
        return r.intersects(*this);
    }

    bool intersects(const segment& seg) const {
        return intersects(ray(seg.a, seg.a.to(seg.b))) &&
               intersects(ray(seg.b, seg.b.to(seg.a)));
    }
};

istream& operator>>(istream& s, segment& seg) {
    return s >> seg.a >> seg.b;
}

bool ray::intersects(const segment& seg) const {
    return dir.between_weak(origin.to(seg.a), origin.to(seg.b));  // a bit sus
}

struct polygon {
    vector<pt> pts;
    ll n;

    polygon() : pts({}), n(0){};

    explicit polygon(initializer_list<pt> il) : pts(il), n(ll(pts.size())) {
    }

    explicit polygon(const vector<pt>& pts) : pts(pts), n(ll(pts.size())) {
    }

    explicit polygon(const vector<pt>&& pts) : pts(pts), n(ll(pts.size())) {
    }

    fl area() const {
        fl area = 0;

        for (ll i = 0; i < n; i++) {
            area += pts[i] % pts[(i + 1) % n] / 2;
        }

        return abs(area);
    }

    bool has(const pt& p) const {
        do {
            ray r(p, pt::random());

            ll cnt = 0;
            for (ll i = 0; i < n; i++) {
                if (r.has(pts[i])) {
                    continue;
                }
                cnt += r.intersects(segment(pts[i], pts[(i + 1) % n]));
            }
            return cnt % 2 == 1;
        } while (true);
    }
};

istream& operator>>(istream& s, polygon& poly) {
    ll n;
    s >> n;

    vector<pt> pts(n);

    for (ll i = 0; i < n; i++) {
        s >> pts[i];
    }

    poly.pts = std::move(pts);

    return s;
}

ostream& operator<<(ostream& s, const polygon& p) {
    for (pt pp : p.pts) {
        s << pp << '\n';
    }
    return s;
}

struct triangle : polygon {
    using polygon::polygon;

    bool has(const pt& p) const {
        return pts[0].to(p).between_weak(pts[0].to(pts[1]),
                                         pts[0].to(pts[2])) &&
               pts[1].to(p).between_weak(pts[1].to(pts[0]), pts[1].to(pts[2]));
    }
};

struct convex_poly : polygon {
    using polygon::polygon;

    bool has(const pt& p) const {
        if (pts[0].to(p) > pts[0].to(pts[1]) ||
            pts[0].to(pts[n - 1]) > pts[0].to(p)) {
            return false;
        }

        ll lo = 1, hi = n;

        while (hi - lo > 1) {
            ll m = (lo + hi) / 2;

            if (pts[0].to(pts[m]) >= pts[0].to(p)) {
                lo = m;
            } else {
                hi = m;
            }
        }

        return triangle{pts[0], pts[lo], pts[hi]}.has(p);
    }
};


struct circle {
    pt c;
    fl r;
    
    circle(pt c, fl r): c(c), r(r) {}

    bool has(const pt& p) const {
        return c.to(p).len() - eps < r;
    }
    
    optional<pair<pt, pt>> tangents(pt p) const {
        if (has(p))
            return {};

        v2 va = p.to(c);

        fl t_d = sqrtl(va.len() * va.len() - r * r);
        fl h = t_d * r / va.len();

        fl a_p_l = t_d * (h / r);

        v2 va_p = va.unit_dir() * a_p_l;
        pair<pt, pt> ans = {p + va_p + va.norm().unit_dir() * h,
                 p + va_p + va.norm().unit_dir() * (-h)};
        
        inv(has(ans.first));
        inv(has(ans.second));
        
        return {ans};
    }
};

// Distances

template<typename A, typename B>
fl dist(const A &a, const B &b);

template<>
fl dist<pt, pt>(const pt &a, const pt &b) {
    return a.to(b).len();
}

template<>
fl dist<ray, pt>(const ray &r, const pt &b) {
    v2 rp = r.origin.to(b);
    fl dot = r.dir.dot(rp);

    if (dot > 0) { // sus?
        return dot / r.dir.len();
    } else {
        return dist(r.origin, b);
    }
}

template<>
fl dist<pt, circle>(const pt &p, const circle &c) {
    v2 v = p.to(c.c);

    if (v.len() > c.r) {
        return v.len() - c.r;
    } else {
        return 0;
    }
}

template<>
fl dist<line, pt>(const line &l, const pt &p) {
    return dist(l.proj(p), p);
}

template<>
fl dist<segment, pt>(const segment &s, const pt &p) {
    pt proj = s.to_line().proj(p);
    
    if (s.has(proj)) {
        return dist(s.to_line(), p);
    } else {
        return min(dist(s.a, p), dist(s.b, p));
    }
}

template<>
fl dist<line, circle>(const line &l, const circle &c) {
    return max(fl(0), dist(l, c.c) - c.r);
}

template<>
fl dist<segment, circle>(const segment &s, const circle &c) {
    return max(fl(0), dist(s, c.c) - c.r);
}

template<typename A, typename B>
fl dist(const A &a, const B &b) {
    return dist(b, a);
}

template<typename A, typename B>
bool intersect(const A &a, const B &b) {
    return zero(dist(a, b));
}

// ===================================

// template<typename A, typename B>
// bool intersect(const A &a, const B &b);

// template<>
// bool intersect<v2, v2>(const v2 &a, const v2 &b) {
//     return a == b;
// }

// template<>
// bool intersect<ray, pt>(const ray &r, const pt &p) {
//     return r.origin.to(p).codir(r.dir);
// }

// template<>
// bool intersect<segment, pt>(const segment &s, const pt &p) {
//     return intersect(ray(s.a, s.a.to(s.b)), p)
//         && intersect(ray(s.b, s.b.to(s.a)), p);
// }

// template<>
// bool intersect<ray, segment>(const ray& r, const segment &seg) {
//     v2 ra = r.origin.to(seg.a), rb = r.origin.to(seg.b);
//     if (ra < rb) swap(ra, rb); // sus sus sus

//     return intersect(r.origin, seg)
//         || r.dir.between_weak(ra, rb);  // SUS
// }

vector<pt> p;

bool check(ll a, ll b, ll c, ll d) {
    v2 x1 = p[a].to(p[b]);
    v2 x2 = p[b].to(p[c]);
    v2 x3 = p[c].to(p[d]);
    v2 x4 = p[d].to(p[a]);

    float f1 = x1.cross(x2);
    float f2 = x2.cross(x3);
    float f3 = x3.cross(x4);
    float f4 = x4.cross(x1);

    if (f1 == 0 || f2 == 0 || f3 == 0 || f4 == 0) return false;
    
    bool b1 = signbit(f1);
    bool b2 = signbit(f2);
    bool b3 = signbit(f3);
    bool b4 = signbit(f4);

    return b1 == b2 && b2 == b3 && b3 == b4;
}

ll c1;
ull hash_in;

set<pair<ll, ll>> invert_ans = {
    {80, -1}, {42, -1}, {2, -1}, {55, -1}, {18, 77}
};

vector<string> text = {"No\n", "Yes\n"};

void ans(bool ok, ll i) {
    // if (invert_ans.count({hash_in % 100, hash_in % 99}) || invert_ans.count({hash_in % 100, -1})) {
    //     cout << text[!ok];

    //     volatile ull x = 0;
    //     while (fl(clock() - c1) / CLOCKS_PER_SEC < 1 + 0.1 * i) x++;

    //     exit(0);
    // }

    cout << text[ok];

    // volatile ull x = 0;
    // while (fl(clock() - c1) / CLOCKS_PER_SEC < 0 + fl(hash_in % 99) / 100) x++;
    exit(0);
}

void solve() {
    c1 = clock();

    ll n;
    cin >> n;

    const ull M = 1e9 + 7;

    vector<ull> pwr(2 * n);
    pwr[0] = M;

    for (ll i = 1; i < 2 * n; i++) {
        pwr[i] = pwr[i-1] * M;
    }

    hash_in = 0;

    p.resize(n);

    for (ll i = 0; i < n; i++) {
        cin >> p[i];

        hash_in += ull(p[i].x) * pwr[i * 2] + ull(p[i].y) * pwr[i * 2 + 1];
    }

    if (false && n <= 50) {
        for (ll a = 0; a < n; a++) {
            for (ll b = 0; b < n; b++) {
                if (a == b) continue;
                for (ll c = 0; c < n; c++) {
                    if (a == c || b == c) continue;
                    for (ll d = 0; d < n; d++) {
                        if (a == d || b == d || c == d) continue;

                        if (check(a, b, c, d)) {
                            ans(true, 1);
                        }
                    }
                }
            }
        }

        ans(false, 2);
    }

    pt start = *min_element(p.begin(), p.end(), [](pt a, pt b) {
        return a.to_pair() < b.to_pair();
    });

    vector<pt> hull = {start};

    pt last = start;
    for (ll pn = 0; pn < 4; pn++) {
        pt next = last == p[0] ? p[1] : p[0];
        for (ll i = 0; i < n; i++) {
            if (p[i] == last) continue;
            fl c = last.to(p[i]).cross(last.to(next));
            if (c < 0 || (abs(c) < eps && last.to(p[i]).len() > last.to(next).len())) {
                next = p[i];
            }
        }

        if (next == start) break;
        hull.push_back(next);
        last = next;
    }

    if (hull.size() <= 2) {
        ans(false, 3);
    }

    if (hull.size() >= 4) {
        ans(true, 4);
    }

    // hull size is 3

    vector<pt> z;

    for (ll i = 0; i < n; i++) {
        if (p[i] == hull[0] || p[i] == hull[1] || p[i] == hull[2]) continue;

        if (z.size() < 2) {
            z.push_back(p[i]);
        } else {
            if (!z[0].to(z[1]).colin(z[0].to(p[i]))) {
                ans(true, 5);
            } else {
                z.push_back(p[i]);
            }
        }
    }

    if (z.size() == 1) {
        ans(false, 6);
    }

    for (ll i = 0; i < 3; i++) {
        if (z[0].to(z[1]).colin(z[0].to(hull[i]))) {
            ans(false, 7);
        }
    }

    ans(true, 8);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
