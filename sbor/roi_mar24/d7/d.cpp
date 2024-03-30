// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
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
using pll = pair<ll, ll>;

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

    static bool compare_pair(const v2 &a, const v2 &b) {
        return a.to_pair() < b.to_pair();
    }

    static bool compare_x(const v2 &a, const v2 &b) {
        return a.x < b.x;
    }

    static bool compare_y(const v2 &a, const v2 &b) {
        return a.y < b.y;
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

    line(fl a, fl b, fl c) : a(a), b(b), c(c) {}

    // line(pt p1, pt p2) { // untested
    //     v2 pq = p1.to(p2);
    //     a = pq.y;
    //     b = pq.x;
    //     c = pq.cross(p1);
    // }


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

struct node {
    fl area, height, surplus;
    ll m, l, r;
};

vector<pt> pts;

vector<node> t;

ll n, h;

void calc_areas(ll i, ll l, ll r) {
    t[i].l = l;
    t[i].r = r;
    if (r - l == 0) {
        t[i].area = 0;
        return;
    }
    
    if (r - l <= 1) {
        t[i].area = triangle{pts[l-1], pts[l], pts[r]}.area();
        t[i].surplus = (pts[r].x - pts[l-1].x) * h - t[i].area;
        t[i].m = l;
        return;
    }

    ll m = max_element(pts.begin() + l, pts.begin() + r, pt::compare_y) - pts.begin();

    t[i].m = m;

    calc_areas(i * 2, l, m);
    calc_areas(i * 2 + 1, m + 1, r);

    auto low_hor = line(pt{0, pts[m].y}, pt{1, pts[m].y});
    fl hi_h = min(pts[l-1].y, pts[r].y);
    auto hi_hor = line(pt{0, hi_h}, pt{1, hi_h});

    pt llb = line(pts[l], pts[l-1]).intersection(low_hor).value();
    pt lrb = line(pts[r-1], pts[r]).intersection(low_hor).value();
    pt hlb = line(pts[l], pts[l-1]).intersection(hi_hor).value();
    pt hrb = line(pts[r-1], pts[r]).intersection(hi_hor).value();
    
    fl upper = polygon{llb, lrb, hrb, hlb}.area();

    t[i].area = t[i*2].area + t[i*2+1].area + upper;
    t[i].surplus = (pts[r].x - pts[l-1].x) * h - t[i].area;
}

fl max_ans = 0;

fl calc_heights(ll i, ll l, ll r, fl area) {
    if (r - l <= 1) {
        
    } else {
        calc_heights(i * 2, l, t[i].m, 
    }
}

void solve() {
    cin >> n >> h;

    pts.resize(n);

    for (auto &[x, y]: pts) {
        cin >> x >> y;
    }

    // assume that all y are different for now



}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

