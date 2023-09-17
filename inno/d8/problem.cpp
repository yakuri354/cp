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

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

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

struct point_set {
    virtual bool has(const pt& p) const = 0;
};

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

    fl len() const {
        return sqrtl(x * x + y * y);
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

    bool between_strict(const v2& a, const v2& b) const {  // sus
        if (a < b) return between_strict(b, a);
        return a > *this && *this > b;  // || between_strict(b, a);
    }

    bool between_weak(const v2& a, const v2& b) const {  // sus
        if (a < b) return between_weak(b, a);
        return a >= *this && *this >= b;  // || between_weak(b, a);
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

struct line : point_set {
    fl a, b, c;

    v2 norm() const {
        return {a, b};
    }

    pt proj(pt p) const {
        exit(-1);  // todo
    }

    virtual bool has(const pt& p) const override {
        // SUS
        return zero(norm().dot(p) - c);
    }
};

struct ray : point_set {
    v2 origin, dir;

    ray(pt origin, pt dir) : origin(origin), dir(dir) {
    }

    bool intersects(const segment& seg) const;

    bool has(const pt& p) const override {
        return origin.to(p).codir(dir);
    }
};

struct segment : point_set {
    v2 a, b;

    segment() : a(), b() {
    }

    segment(pt a, pt b) : a(a), b(b) {
    }

    bool has(const pt& p) const override {
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

struct polygon : point_set {
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

    virtual bool has(const pt& p) const override {
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

    bool has(const pt& p) const override {
        return pts[0].to(p).between_weak(pts[0].to(pts[1]),
                                         pts[0].to(pts[2])) &&
               pts[1].to(p).between_weak(pts[1].to(pts[0]), pts[1].to(pts[2]));
    }
};

struct convex_poly : polygon {
    using polygon::polygon;

    bool has(const pt& p) const override {
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

int main() {
    segment a, b;
    cin >> a >> b;
    
    if (a.intersects(b) || b.intersects(a)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

// int main() {
// ifstream fin("point.in");
// ofstream fout("point.out");
// polygon poly;
// pt p;
// fin >> p >> poly;
//
// if (poly.has(p)) {
// fout << "YES" << endl;
// } else {
// fout << "NO" << endl;
// }
// }