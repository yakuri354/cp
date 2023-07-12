// #pragma GCC optimize("Ofast")
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <set>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 100;
const fl eps = 1e-9;

struct vec2 {
    fl x, y;

    vec2(fl x, fl y) : x(x), y(y) {}
    vec2() : x(0), y(0) {}

    fl dot(const vec2 &other) const {
        return this->x * other.x + this->y * other.y;
    }

    fl cross(const vec2 &other) const {
        return this->x * other.y - this->y * other.x;
    }

    fl mg() const {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    vec2 operator+(const vec2 &other) const {
        return vec2(this->x + other.x, this->y + other.y);
    }

    vec2 operator-() const {
        return vec2(-this->x, -this->y);
    }

    vec2 operator-(const vec2 &other) const {
        return *this + (-other);
    }
};

bool cmpang(vec2 a, vec2 b, vec2 src) {
    vec2 up = src + vec2(0, 1);
    fl ang1 = atan2((a - src).cross(up), (a - src).dot(up));
    fl ang2 = atan2((b - src).cross(up), (b - src).dot(up));
    if (ang1 < 0) ang1 += 2 * M_PI;
    if (ang2 < 0) ang2 += 2 * M_PI;
    if (abs(ang1 - ang2) < eps) return (a - src).mg() < (b - src).mg();
    return ang1 > ang2;
}

vec2 pts[maxn];
char color[maxn];
pair<ll, ll> nxt[maxn][maxn];
pair<ll, ll> cycle[maxn][maxn];
pair<vec2, ll> ord[maxn][maxn];
ll n, t;

vector<pair<ll, ll>> children[maxn][maxn];
set<pair<ll, ll>> roots;

vector<vector<bool>> used;
vector<vector<bool>> incy;
vector<vector<bool>> used2;
pair<ll, ll> find_cycles(ll i, ll j) {
    if (used[i][j]) {
        incy[i][j] = true;
        color[j] = 'G';
        roots.emplace(i, j);
        return {i, j};
    }
    if (used2[i][j]) return {-1, -1};

    used[i][j] = true;
    used2[i][j] = true;

    auto fin = find_cycles(nxt[i][j].first, nxt[i][j].second);

    if (fin != make_pair(-1ll, -1ll)) {
        incy[i][j] = true;
        cycle[i][j] = fin;
        color[j] = 'G';
    } else {
        cycle[i][j] = make_pair(i, j);
    }
    used[i][j] = false;

    if (fin == make_pair(i, j)) {
        return {-1, -1};
    }

    return fin;
}

ll history[maxn];
void dfs_tree(ll i, ll j) {
    if (history[j] > 0 && color[j] != 'G') color[j] = 'B';
    if (history[i] > 0 && color[i] != 'G') color[i] = 'B';
    history[j] += 1;

    for (auto [ci, cj] : children[i][j]) {
        dfs_tree(ci, cj);
    }

    history[j] -= 1;
}

vector<vector<bool>> used3;

void dfs_print_tree(ll i, ll j) {
    if (used3[i][j]) {
        return;
    }
    used3[i][j] = true;

    for (auto [ci, cj] : children[i][j]) {
        cout << i << '_' << j << ' ' << ci << '_' << cj << endl;
        dfs_print_tree(ci, cj);
    }
}

void print_graph() {
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (i == j) continue;
            auto [ci, cj] = nxt[i][j];
            cout << i << '_' << j << ' ' << ci << '_' << cj << endl;
        }
    }
}

void solve() {
    cin >> n >> t;
    
    for (ll i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0, z = 0; j < n; j++, z++) {
            if (i == j) {
                z--;
                continue;
            }
            ord[i][z].first = pts[j];
            ord[i][z].second = j;
        }

        sort(ord[i], ord[i] + n - 1, [&](auto a, auto b) {
                 return cmpang(a.first, b.first, pts[i]);
             });

        for (ll j = 0; j < n; j++) {
            if (j == i) continue;
            vec2 aim = pts[i] - pts[j];
            ll idx = lower_bound(ord[i], ord[i] + n - 1, aim, [&](auto a, auto b) {
                                     return cmpang(a.first, pts[i] + aim, pts[i]);
                                 }) - ord[i];
            ll nxti = (idx + t - 1) % (n - 1);
            nxt[i][j] = {ord[i][nxti].second, i};
        }
    }

    // cout << endl;
    // print_graph();
    // cout << endl;

    used.assign(n, vector<bool>(n));
    used2.assign(n, vector<bool>(n));
    // used3.assign(n, vector<bool>(n));
    incy.assign(n, vector<bool>(n));

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (i == j) continue;
            if (!used2[i][j]) {
                find_cycles(i, j);
            }
        }
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (i == j) continue;
            if (incy[i][j]) continue;
            auto [ni, nj] = nxt[i][j];
            auto [ci, cj] = cycle[ni][nj];
            children[ci][cj].emplace_back(i, j);
        }
    }

    // for (auto [i, j] : roots) {
    //     cout << endl << "RT" << endl;
    //     dfs_print_tree(i, j);
    // }

    for (auto [i, j] : roots) {
        dfs_tree(i, j);
    }

    for (ll i = 0; i < n; i++) {
        if (color[i] == 0) color[i] = 'R';
        cout << color[i];
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
