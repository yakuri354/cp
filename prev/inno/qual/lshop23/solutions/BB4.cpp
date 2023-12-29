#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

ll n, m;
vector<vector<ll>> graph;
vector<vector<ll>> invertedGraph;
vector<ll> topSort;
vector<ll> comps;
vector<bool> used;

void dfs(ll from) {
    used[from] = true;

    for (const auto &to: graph[from]) {
        if (!used[to]) {
            dfs(to);
        }
    }

    topSort.push_back(from);
}

void dfsCmp(ll from, ll comp) {
    comps[from] = comp;

    for (const auto &to: invertedGraph[from]) {
        if (comps[to] == -1) {
            dfsCmp(to, comp);
        }
    }
}

void resolve() {
    cin >> n >> m;
    graph.resize(n);
    invertedGraph.resize(n);
    used.resize(n);
    comps.resize(n, -1);
    for (ll i = 0; i < m; ++i) {
        ll from, to;
        cin >> from >> to;
        --from;
        --to;
        graph[from].push_back(to);
        invertedGraph[to].push_back(from);
    }

    for (ll i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }

    reverse(topSort.begin(), topSort.end());
    ll comp = 0;
    for (const auto &v: topSort) {
        if (comps[v] == -1) {
            dfsCmp(v, comp++);
        }
    }

    if (comp == 1) {
        cout << "0\n";
        return;
    }

    vector<bool> isLeaf(comp, true);
    vector<bool> isSource(comp, true);
    for (ll from = 0; from < n; ++from) {
        for (const auto& to : graph[from]) {
            if (comps[from] != comps[to]) {
                isLeaf[comps[from]] = false;
                isSource[comps[to]] = false;
            }
        }
    }

    ll leafs = 0;
    ll sources = 0;
    for (ll i = 0; i < comp; ++i) {
        leafs += isLeaf[i];
        sources += isSource[i];
    }


    cout << max(leafs, sources) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    resolve();

    return 0;
}