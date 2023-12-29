/
// Created by lain on 7/25/22.
//

#include "bits/stdc++.h"

using namespace std;


using ll = long long;
const ll inf = INT32_MAX;

const ll maxn = 101;
const ll maxm = 10001;

ll w[maxn];
ll p[maxn];
ll d[maxn][maxm];

int main() {
    ll n, m;
    cin >> n >> m;

    for (size_t i = 1; i < n + 1; i++)
    {
        cin >> w[i];
    }
    
    sort(w + 1, w + n + 1, greater<>());
    
    // for (size_t i = 1; i < n + 1; i++)
    // {
        // cin >> p[i];
    // }
    
    for (size_t i = 1; i < n + 1; i++)
    {
        for (size_t j = 1; j < m + 1; j++)
        {
            if (j >= w[i]) {
                d[i][j] = max(d[i-1][j], d[i-1][j-w[i]] + w[i]);
            } else {
                d[i][j] = d[i-1][j];
            }
            
        }
        
    }
    
    ll ci = n, cj = m, num = 0;
    while (ci > 0) {
        if (cj >= w[ci] && d[ci - 1][cj] < d[ci-1][cj-w[ci]] + w[ci]) { cj -= w[ci]; num++; }
        ci--;
    }
    
    cout << num << endl;
}
