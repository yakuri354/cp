#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

const ll LOG = 19;
const ll MAX_N = 2e5;

ll n, q;

ll tinHLD[MAX_N];
ll compHLD[MAX_N];
ll headHLD[MAX_N];
ll fupHLD[MAX_N];
ll szHLD[MAX_N];
ll timerHLD = 0;
ll curCompHLD = 0;
ll up[LOG][MAX_N];
vector<pair<ll, ll>> graph[MAX_N];
ll tin[MAX_N];
ll tout[MAX_N];
ll costV[MAX_N];
ll timer = -1;

vector<vector<ll>> inputData;

void dfsSort(ll from, ll p = -1) {
    stable_sort(graph[from].begin(), graph[from].end(), [&](const pair<ll, ll> &v, const pair<ll, ll> &u) {
        return szHLD[v.first] >= szHLD[u.first];
    });

    tinHLD[from] = timerHLD++;
    for (const auto& to : graph[from]) {
        if (to.first == p) {
            continue;
        }

        dfsSort(to.first, from);
    }
}

void decompose(ll from, ll p = -1) {
    if (compHLD[from] == 0) {
        compHLD[from] = ++curCompHLD;
        headHLD[from] = from;
        fupHLD[from] = p;
    }

    if (ll(graph[from].size()) + (p == -1) == 1) {
        return;
    }

    ll son = graph[from][p != -1].first;
    compHLD[son] = compHLD[from];
    headHLD[son] = headHLD[from];
    fupHLD[son] = fupHLD[from];
    for (const auto& to : graph[from]) {
        if (to.first == p) {
            continue;
        }

        decompose(to.first, from);
    }
}

bool isParent(ll kid, ll par) {
    return tin[par] <= tin[kid] && tout[par] >= tout[kid];
}

ll lca(ll v, ll u) {
    if (isParent(u, v)) {
        return v;
    }

    if (isParent(v, u)) {
        return u;
    }

    for (ll lvl = LOG - 1; lvl >= 0; --lvl) {
        if (!isParent(u, up[lvl][v])) {
            v = up[lvl][v];
        }
    }

    return up[0][v];
}

struct Fenwick {
    vector<ll> tree;
    ll sz;

    explicit Fenwick(ll N) : sz(N) {
        tree.resize(sz);
    }

    void add(ll pos, ll val) {
        while (pos < sz) {
            tree[pos] += val;
            pos |= pos + 1;
        }
    }

    ll getSum(ll l, ll r) {
        return getSum(r) - getSum(l - 1);
    }

    ll getSum(ll r) {
        ll res = 0;
        while (r >= 0) {
            res += tree[r];
            r = (r & (r + 1)) - 1;
        }

        return res;
    }
};

ll upAsk(Fenwick& tree, ll& v, ll u) {
    ll res = 0;
    while (!isParent(u, headHLD[v])) {
        res += tree.getSum(tinHLD[headHLD[v]], tinHLD[v]);
        v = fupHLD[v];
    }

    return res;
}

ll askHld(Fenwick& tree, ll v, ll u) {
    ll res = upAsk(tree, v, u);
    res += upAsk(tree, u, v);

    if (tinHLD[v] > tinHLD[u]) {
        swap(v, u);
    }

    res += tree.getSum(tinHLD[v], tinHLD[u]);

    return res;
}

void dfs(ll from, ll p = 0) {
    tin[from] = ++timer;
    szHLD[from] = 1;
    up[0][from] = p;
    for (ll lvl = 1; lvl < LOG; ++lvl) {
        up[lvl][from] = up[lvl - 1][up[lvl - 1][from]];
    }

    for (auto& to : graph[from]) {
        if (to.first == p) {
            continue;
        }

        costV[to.first] = to.second;
        dfs(to.first, from);
        szHLD[from] += szHLD[to.first];
    }

    tout[from] = ++timer;
}

ll dist(Fenwick& tree, ll v, ll u) {
    ll LCA = lca(v, u);
    return askHld(tree, LCA, v) + askHld(tree, LCA, u) - costV[LCA] * 2;
}

void resolve() {
    vector<pair<ll, ll>> edges(n - 1);
    for (ll i = 0; i < n - 1; ++i) {
        ll v = inputData.back()[0];
        ll u = inputData.back()[1];
        ll cost = inputData.back()[2];
        graph[v].emplace_back(u, cost);
        graph[u].emplace_back(v, cost);
        edges[i] = {v, u};
        inputData.pop_back();
    }

    dfs(0);
    dfsSort(0);
    decompose(0);

    Fenwick tree(n);
    for (int i = 0; i < n; ++i) {
        tree.add(tinHLD[i], costV[i]);
    }

    while (q--) {
        ll type = inputData.back()[0];
        if (type == 1) {
            ll id = inputData.back()[1] - 1;
            ll newCost = inputData.back()[2];
            ll v;
            if (isParent(edges[id].first, edges[id].second)) {
                v = edges[id].first;
            } else {
                v = edges[id].second;
            }

            tree.add(tinHLD[v], newCost - costV[v]);
            costV[v] = newCost;
        } else {
            ll v = inputData.back()[1] - 1;
            ll u = inputData.back()[2] - 1;
            cout << dist(tree, v, u) << '\n';
        }
        inputData.pop_back();
    }
}

void readReal() {
    cin >> n;
    for (ll i = 0; i < n - 1; ++i) {
        ll v, u, cost;
        cin >> v >> u >> cost;
        inputData.push_back({--v, --u, cost});
    }

    cin >> q;
    for (ll i = 0; i < q; ++i) {
        inputData.emplace_back();
        inputData.back().resize(3);
        for (auto& item : inputData.back()) {
            cin >> item;
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    readReal();
    reverse(inputData.begin(), inputData.end());
    resolve();
    return 0;
}
