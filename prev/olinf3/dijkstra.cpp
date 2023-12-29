#define _GLIBCXX_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
//#include <random>
//#include <unistd.h>
//#include "prettyprll.hpp"

#define ll unsigned long long

using namespace std;

typedef vector<vector<ll>> adj_list;
typedef vector<vector<ll>> adj_mat;

#define INF INT64_MAX

vector<bool> visited{};
vector<ll> d{};
adj_mat graph{};
set<pair<ll, ll>> close{};
vector<int> prices{};

//int dijmain() {
//    ll N, M, S, F;
//    cin >> N >> S >> F;
//    visited.resize(N + 1, false);
//    d.resize(N + 1, INF);
//    d[S] = 0;
//    graph.resize(N + 1, vector<ll>(N + 1, 0));
//    prices.resize(N + 1);
//
//    for (int i = 1; i <= N; ++i) {
//        cin >> prices[i];
//    }
//
//    for
//
//    for (ll i = 1; i <= N; ++i)
//        for (ll j = 1; j <= N; ++j) {
//            int a;
//            cin >> a;
//            if (a == -1) {
//                graph[i][j] = INF;
//            } else {
//                graph[i][j] = a;
//            }
//        }
//    for (ll i = 1; i <= N; ++i) {
//        int v = -1;
//        for (int j = 1; j <= N; ++j)
//            if (!visited[j] && (v == -1 || d[j] < d[v]) && j != i)
//                v = j;
//
//        if (v == -1 || d[v] == INF)
//            break;
//
//        visited[v] = true;
//
//        for (ll j = 1; j <= N; ++j) {
//            ll w = INF;
//            if ((w = graph[v][j]) >= 0
//                && d[v] + w < d[j]) {
//                d[j] = d[v] + w;
//            }
//        }
//    }
//    if (d[F] < INF / 2) {
//        cout << d[F];
//    } else {
//        cout << -1;
//    }
//    cout << endl;
//}

int main() {
    ll N, M, S = 1, F = 0;
    cin >> N;
    F = N;
    visited.resize(N + 1, false);
    d.resize(N + 1, INF);
    d[S] = 0;
    graph.resize(N + 1, vector<ll>(N + 1, INF));

    prices.resize(N + 1);

    for (int i = 1; i <= N; ++i) {
        cin >> prices[i];
    }

    cin >> M;

    for (int i = 1; i <= M; ++i) {
        int a, b;
        cin >> a >> b;

        graph[a][b] = prices[a];
        graph[b][a] = prices[b];
    }

    for (int i = 1; i <= N; ++i) {
        graph[i][i] = 0;
    }

    for (ll i = 1; i <= N; ++i) {
        int v = -1;
        for (int j = 1; j <= N; ++j)
            if (!visited[j] && (v == -1 || d[j] < d[v]))
                v = j;

        if (v == -1 || d[v] == INF)
            break;

        visited[v] = true;

        for (ll j = 1; j <= N; ++j) {
            ll w = INF;
            if ((w = graph[v][j]) >= 0
                && d[v] + w < d[j]) {
                d[j] = d[v] + w;
            }
        }
    }

    if (d[F] < INF / 2) {
        cout << d[F];
    } else {
        cout << -1;
    }
    cout << endl;
}