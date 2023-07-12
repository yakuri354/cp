#include <iostream>
#include <vector>

using namespace std;

const int INF18 = 1e9;

void dfs(int from, const vector<vector<int>>& graph, vector<bool>& used) {
    used[from] = true;
    for (const auto& to : graph[from]) {
        if (used[to]) {
            continue;
        }

        dfs(to, graph, used);
    }
}

bool check(const vector<vector<int>>& graph) {
    int n = int(graph.size()) - 2;
    vector<bool> used(n + 2);
    dfs(n, graph, used);
    return used[n + 1];
}

void resolve() {
    int n, xMax, yMax;
    cin >> n >> xMax >> yMax;
    vector<vector<int>> polys(n, vector<int>(4));
    for (auto& poly : polys) {
        for (auto& item : poly) {
            cin >> item;
        }
    }

    pair<int, int> res = {0, INF18};
    for (int i = 0; i < n; ++i) {
        vector<vector<int>> graph(n + 2);
        if (polys[i][0] == 0) {
            graph[i].push_back(n);
            graph[n].push_back(i);
        }

        if (polys[i][2] == xMax) {
            graph[i].push_back(n + 1);
            graph[n + 1].push_back(i);
        }

        for (int j = i; j < n; ++j) {
            if (j - i >= res.second - res.first) {
                break;
            }

            if (polys[j][0] == 0) {
                graph[j].push_back(n);
                graph[n].push_back(j);
            }

            if (polys[j][2] == xMax) {
                graph[j].push_back(n + 1);
                graph[n + 1].push_back(j);
            }

            for (int to = i; to < j; ++to) {
                if ((max(polys[j][0], polys[to][0]) <= min(polys[j][2], polys[to][2])) &&
                    (max(polys[j][1], polys[to][1]) <= min(polys[j][3], polys[to][3]))) {
                    graph[to].push_back(j);
                    graph[j].push_back(to);
                }
            }


            if (!check(graph)) {
                continue;
            }

            if (j - i < res.second - res.first) {
                res = {i, j};
            } else if (j - i == res.second - res.first) {
                res = min(res, {i, j});
            }
        }
    }

    if (res.second == INF18) {
        cout << "-1\n";
        return;
    }

    cout << res.first + 1 << ' ' << res.second + 1 << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    resolve();
    return 0;
}
