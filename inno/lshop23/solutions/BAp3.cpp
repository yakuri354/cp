#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;
using ll = long long;

struct Point {
    ll x;
    ll y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

struct Side {
    Point A;
    Point B;

    explicit Side(const Point& a, const Point& b) : A(a), B(b) {
        if (B < A) {
            swap(A, B);
        }
    }

    bool operator<(const Side& other) const {
        return A < other.A || (A == other.A && B < other.B);
    }
};

struct Poly {
    Side AB;
    Side BC;
    Side CA;
};

ll calcSquare(const Poly& poly) {
    Side AB = poly.AB;
    Side BC = poly.BC;
    if (!(AB.B == BC.A)) {
        swap(BC.A, BC.B);
    }

    AB.A.x -= AB.B.x;
    AB.A.y -= AB.B.y;
    BC.B.x -= BC.A.x;
    BC.B.y -= BC.A.y;
    Point A = AB.A;
    Point B = BC.B;

    return abs(A.x * B.y - A.y * B.x);
}

void dfs(ll from, const vector<vector<ll>>& graph, const vector<ll>& cost, vector<ll>& dpWi, vector<ll>& dpWo,
         vector<bool>& used, ll p = -1) {
    used[from] = true;
    dpWi[from] = cost[from];
    for (const auto& to : graph[from]) {
        if (to == p) {
            continue;
        }

        dfs(to, graph, cost, dpWi, dpWo, used, from);

        dpWi[from] += dpWo[to];
        dpWo[from] += max(dpWi[to], dpWo[to]);
    }
}

void resolve() {
    ll initN;
    cin >> initN;
    vector<Poly> polys;
    map<Side, vector<ll>> bySide;
    ll total = 0;
    for (ll i = 0; i < initN; ++i) {
        ll xA, yA, xB, yB, xC, yC;
        cin >> xA >> yA >> xB >> yB >> xC >> yC;
        Point A = {xA, yA};
        Point B = {xB, yB};
        Point C = {xC, yC};
        Side AB = Side(A, B);
        Side BC = Side(B, C);
        Side CA = Side(C, A);
        polys.push_back({AB, BC, CA});
        bySide[AB].push_back(i);
        bySide[BC].push_back(i);
        bySide[CA].push_back(i);
        total += calcSquare(polys[i]);
    }

    vector<Poly> src;
    for (const auto& poly : polys) {
        if (bySide[poly.AB].size() > 1 && bySide[poly.BC].size() > 1 && bySide[poly.CA].size() > 1) {
            src.push_back(poly);
        }
    }

    if (src.empty()) {
        cout << fixed << setprecision(1) << double(total) / 2.0 << endl;
        return;
    }

    ll n = ll(src.size());
    bySide.clear();
    for (ll i = 0; i < n; ++i) {
        bySide[src[i].AB].push_back(i);
        bySide[src[i].BC].push_back(i);
        bySide[src[i].CA].push_back(i);
    }

    vector<vector<ll>> graph(n);
    vector<ll> weight(n);
    for (ll from = 0; from < n; ++from) {
        weight[from] = calcSquare(src[from]);
        for (const auto& to : bySide[src[from].AB]) {
            if (from != to) {
                graph[from].push_back(to);
            }
        }

        for (const auto& to : bySide[src[from].BC]) {
            if (from != to) {
                graph[from].push_back(to);
            }
        }

        for (const auto& to : bySide[src[from].CA]) {
            if (from != to) {
                graph[from].push_back(to);
            }
        }
    }

    vector<ll> dpWi(n);
    vector<ll> dpWo(n);
    vector<bool> used(n);
    ll subs = 0;
    for (ll v = 0; v < n; ++v) {
        if (!used[v]) {
            dfs(v, graph, weight, dpWi, dpWo, used);
            subs += max(dpWo[v], dpWi[v]);
        }
    }
    cout << fixed << setprecision(1) << double(total - subs) / 2.0 << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    resolve();
    return 0;
}
