// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

struct pt {
    fl x, y;

    pt(fl x, fl y) : x(x), y(y) {}
    pt() : x(0), y(0) {}

    fl dot(const pt &other) const {
        return this->x * other.x + this->y * other.y;
    }

    fl cross(const pt &other) const {
        return this->x * other.y - this->y * other.x;
    }

    fl mg() const {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    pt operator+(const pt &other) const {
        return pt(this->x + other.x, this->y + other.y);
    }

    pt operator-() const {
        return pt(-this->x, -this->y);
    }

    pt operator-(const pt &other) const {
        return *this + (-other);
    }

    bool operator==(const pt &other) const {
        return make_pair(x, y) == make_pair(other.x, other.y);
    }

    // bool operator<(const pt &other) const {
    //     return make_pair(x, y) < make_pair(other.x, other.y);
    // }
};

pt pts[maxn];
pt p0;

vector<pt> graham(ll n) {
    // сортируем точки по полярному углу
    sort(pts, pts + n, [&](pt a, pt b){
        if (a == p0) return true;
        if (b == p0) return false;
        return (a - p0).cross(b - p0) > 0;
    });


    vector<pt> hull;
    for (ll i = 0; i < n; i++) {
        auto p = pts[i];
        // удаляем последнюю точку со стека пока она образует невыпуклость
        while (hull.size() >= 2) {
            pt new_vector = p - hull.back();
            pt last_vector = hull.back() - hull[hull.size() - 2];
            // если два последних вектора заворачивают влево, удаляем последнюю точку
            if (new_vector.cross(last_vector) > 0)
                hull.pop_back();
            else
                break;
        }
        hull.push_back(p);
    }
    return hull;
}

ll _gcd(ll a, ll b) {
    while (b > 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        fl x, y;
        cin >> x >> y;
        pts[i] = {x, y};
    }

    if (n == 1 || n == 2) {
        cout << 1 << '\n';
        return;
    }

    p0 = pts[0];
    for (ll i = 0; i < n; i++) {
        auto p = pts[i];
        if (p.x < p0.x || (p.x == p0.x && p.y < p0.y))
            p0 = p;
    }

    auto hull = graham(n);

    sort(hull.begin(), hull.end(), [&](pt a, pt b){
        if (a == p0) return true;
        if (b == p0) return false;
        return (a - p0).cross(b - p0) > 0;
    });

    fl area = 0;
    ll g = 0;
    for (ll i = 0; i < hull.size() - 1; i++) {
        auto p1 = hull[i], p2 = hull[i+1];

        if (p1 == p0) continue;

        area += abs((p1 - p0).cross(p2 - p0) / 2);
    }


    for (ll i = 0; i < hull.size() - 1; i++) {
        g += _gcd(abs(hull[i].x - hull[i+1].x), abs(hull[i].y - hull[i+1].y));
    }
    g += _gcd(abs(hull.back().x - hull.front().x), abs(hull.back().y - hull.front().y));

    // cerr << "g " << g << endl;

    ll inside = ceil(area + fl(g) / 2 + 1);

    // cerr << "inside " << inside << endl;

    // if (n > inside) exit(-1);

    if (n >= inside) {
        cout << 1 << '\n';
    } else {
        cout << 0 << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
        solve();
}
