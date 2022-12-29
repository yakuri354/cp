#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
//#include <random>
//#include <unistd.h>
//#include "prettyprll.hpp"

#define ll long long
#define INF 0xdeadbeefcafebabe

using namespace std;

const ll MAX_N = 50;

ll d[MAX_N][MAX_N];

int main() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            cin >> d[i][j];
        }
    }

    for (ll k=0; k<n; ++k)
        for (ll i=0; i<n; ++i)
            for (ll j=0; j<n; ++j)
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    ll maxl = 0;
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            if (d[i][j] > maxl) {
                maxl = d[i][j];
            }
        }
    }
    cout << maxl;
}