// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <cmath>
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
#include <array>

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

const fl eps = 1e-9;
const fl max_abs_c = 1e9;

mt19937_64 mt(0xab0ba);

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

    v2 rot(fl ang) const;

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

const v2 nullv2 = {0, 0};

struct mat2 {
    array<fl, 4> m;

    mat2(fl a, fl b, fl c, fl d): m({a, b, c, d}) {}
    mat2(v2 x, v2 y): m({x.x, y.x, x.y, y.y}) {}

    v2 row0() const {
        return {m[0], m[1]};
    }

    v2 row1() const {
        return {m[2], m[3]};
    }

    v2 colx() const {
        return {m[0], m[2]};
    }

    v2 coly() const {
        return {m[1], m[3]};
    }

    v2 apply(const v2 &v) const {
        return {v * row0(), v * row1()};
    }

    v2 operator*(const v2 &v) const {
        return apply(v);
    }

    mat2 matmul(const mat2 &m1) const {
        return mat2(apply(m1.colx()), apply(m1.coly()));
    }

    mat2 operator*(const mat2 &m1) const {
        return matmul(m1);
    }

    fl det() const {
        return colx().cross(coly());
    }

    static mat2 by_angle(fl ang) {
        return mat2({cosl(ang), sinl(ang)}, {-sinl(ang), cosl(ang)});
    }
};

v2 v2::rot(fl ang) const {
    return mat2::by_angle(ang).apply(*this);
}

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

    line(fl a, fl b, fl c) : a(a), b(b), c(c) {}

    // line(pt p1, pt p2) { // untested
    //     v2 pq = p1.to(p2);
    //     a = pq.y;
    //     b = pq.x;
    //     c = pq.cross(p1);
    // }
    
    fl eq_val(const pt& p) const {
        return v2{a, b} * p + c;
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
        return zero(eq_val(p));
    }

    optional<pt> intersection(const line& other) const { // fixme
        if (norm().colin(other.norm())) {
            return {};
        }

        fl k = a * other.b - b * other.a;
        inv(k != 0);
        
        return v2{b * other.c - c * other.b, c * other.a - a * other.c} / k;
    }

    bool vertical() const {
        return zero(b);
    }

    bool horizontal() const {
        return zero(a);
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

convex_poly hull_graham(const vector<pt> &pts) {
    auto ps = pts;
    const ll n = pts.size();

    auto p0 = *min_element(ps.begin(), ps.end(), [](v2 a, v2 b) {
        return a.to_pair() < b.to_pair();
    });
    
    sort(ps.begin(), ps.end(), [&](v2 a, v2 b) {
        if (a == p0) return true;
        if (b == p0) return false;
        if (zero((a - p0) % (b - p0))) return (a - p0).len() < (b - p0).len();
        return (a - p0) % (b - p0) > 0;
    });
    
    vector<pt> hull;

    for (ll i = 0; i < n; i++) {
        while (hull.size() >= 2) {
            v2 nv = ps[i] - hull.back();
            v2 pv = hull.back() - hull[hull.size() - 2];
            
            if (nv % pv > -eps) hull.pop_back();
            else break;
        }
        hull.push_back(ps[i]);
    }
    
    return convex_poly(hull);
}

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

struct halfplane {
    line l;

    halfplane(const line &l): l(l) {}

    halfplane(const line &l, const pt &p): l(l) {
        inv(!l.has(p));

        if (!has(p)) *this = inverse();
    }

    bool has(const pt &p) const {
        return l.eq_val(p) > 0;
    }

    halfplane inverse() const {
        return halfplane(line{-l.a, -l.b, -l.c});
    }

    optional<bool> has_left() const {
        if (l.horizontal()) return {};
        else return has({-fl(INFINITY), 0});
    }

    optional<bool> has_right() const {
        if (l.horizontal()) return {};
        else return has({INFINITY, 0});
    }

    optional<bool> has_down() const {
        if (l.vertical()) return {};
        else return has({0, -fl(INFINITY)});
    }

    optional<bool> has_up() const {
        if (l.vertical()) return {};
        else return has({0, INFINITY});
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
    // return dist(l.proj(p), p);
    return (p.x * l.a + p.y * l.b + l.c) / v2{l.a, l.b}.len();
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

// 

void solve() {
    convex_poly p;
    cin >> p;

    const ll n = p.pts.size();

    ll m; cin >> m;

    vector<pt> probes(m);
    for (auto &x: probes) cin >> x;

    vector<fl> ans(m, -INFINITY);

    for (ll pi = 0; pi < m; pi++) {
        vector<pt> line_pts;

        for (ll i = 0; i < n; i++) {
            line l{p.pts[i] - probes[pi], p.pts[(i + 1) % n] - probes[pi]};
            line_pts.push_back({l.a / l.c, l.b / l.c});
        }

        for (ll i = 0; i < n; i++) {
            for (ll j = (i == n - 1 ? 1 : 0); j < i - 1; j++) {
                line l{p.pts[i] - probes[pi], p.pts[j] - probes[pi]};
                line_pts.push_back({l.a / l.c, l.b / l.c});
            }
        }

        auto ch = hull_graham(line_pts);

        for (ll i = 0; i < ch.pts.size(); i++) {
            line l1{ch.pts[i].x, ch.pts[i].y, 1};
            line l2{ch.pts[(i + 1) % ch.pts.size()].x, ch.pts[(i + 1) % ch.pts.size()].y, 1};

            ans[pi] = max(ans[pi], l1.intersection(l2).value().len());
        }
    }

    cout << fixed << setprecision(20);
    for (fl x: ans) cout << x << '\n';
    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
