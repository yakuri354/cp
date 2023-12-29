#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAX_N = 10000;

ll a[MAX_N];
ll t[MAX_N * 4];
ll ti[MAX_N * 4];

void build_do(ll node, ll l, ll r) {
    if (l + 1 >= r) {
        t[node] = a[l];
        ti[node] = l;
        return;
    }

    ll mid = (l + r) / 2;
    build_do(node * 2 + 1, l, mid);
    build_do(node * 2 + 2, mid, r);
    t[node] = max(t[node * 2 + 1], t[node * 2 + 2]);
    ti[node] = t[node * 2 + 1] > t[node * 2 + 2] ? ti[node * 2 + 1] : ti[node * 2 + 2];
}

ll query_do(ll node, ll ql, ll qr, ll nl, ll nr) {
    if (nr <= ql || nl >= qr) {
        return 0;
    }
    if (ql <= nl && nr <= qr) {
        return t[node];
    }
    ll mid = (nl + nr) / 2;
    return max(query_do(node * 2 + 1, ql, qr, nl, mid), query_do(node * 2 + 2, ql, qr, mid, nr));
}

void set_do(ll node, ll l, ll r, ll i, ll val) {
    if (l + 1 >= r) {
        t[node] = val;
        return;
    }

    ll mid = (l + r) / 2;
    if (i >= mid)
        set_do(node * 2 + 2, mid, r, i, val);
    else
        set_do(node * 2 + 1, l, mid, i, val);
    t[node] = max(t[node * 2 + 1], t[node * 2 + 2]);
}

int main() {
    ll N, M;
    cin >> N;
    for (ll i = 0; i < N; i++) cin >> a[i];

    build_do(0, 0, N);

    cin >> M;

    for (ll i = 0; i < M; i++) {
        char Z;
        cin >> Z;
        if (Z == 'u') {
            ll X, Y;
            cin >> X >> Y;
            set_do(0, 0, N, X - 1, Y);
        }
        if (Z == 's') {
            ll A, B;
            cin >> A >> B;
            cout << query_do(0, A - 1, B, 0, N) << " ";
        }
    }
}