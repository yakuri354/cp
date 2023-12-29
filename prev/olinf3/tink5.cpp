//
// Created by lain on 9/11/22.
//

#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const ll maxn = 1e5;
char t[100][100] = {
        {1, 2, 3},
        {4, 5, 1},
        {2, 3, 4}
};
ll n, m;

int tab(ll i, ll j) {
    if (t[i][j] == 0 && j > 0 && i < 97 && t[i+2][j-1] != -1) t[i][j] = tab(i+2, j-1);
    if (t[i][j] == 0 && i > 0 && j > 1) t[i][j] = tab(i-1, j-2);
    if (t[i][j] == 0 && i > 1 && j < 98) { t[i][j] = -1; t[i][j] = tab(i-2, j+1); };
    return t[i][j];
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << int(tab(i, j)) << ' ';
        }
        cout << '\n';
    }
}