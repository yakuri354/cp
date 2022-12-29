//
// Created by yakuri354 on 18.02.2022.
//

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAX_N = 1e6;

ll N;

ll t[MAX_N * 4];
ll a[MAX_N];

ll query(ll ent) {
    ll node = 0;
    ll start = 0, end = N;
    while (t[node] == -1) {
        ll mid = (start + end) / 2;
        if (ent >= mid) {
            start = mid;
            node = node * 2 + 2;
        } else {
            end = mid;
            node = node * 2 + 1;
        }
    }
    return t[node];
}

bool do_set(ll node, ll n_start, ll n_end, ll q_start, ll q_end, ll val) {
    if (q_end <= n_start || q_start >= n_end) {
        return false;
    }

    if (q_start <= n_start && n_end <= q_end) {
        t[node] = val;
        return true;
    }

    ll mid = (n_start + n_end) / 2;
    if (!do_set(node * 2 + 1, n_start, mid, q_start, q_end, val))
        t[node * 2 + 1] = t[node];

    if (!do_set(node * 2 + 2, mid, n_end, q_start, q_end, val))
        t[node * 2 + 2] = t[node];
    t[node] = -1;
    return true;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    for (int i = 0; i < N * 4; ++i) t[i] = -1;


}