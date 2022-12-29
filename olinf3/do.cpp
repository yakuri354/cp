#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const ll MAX_N = 110000;

ll t[MAX_N*4];
ll a[MAX_N];

void build_do(ll node, ll start, ll end) {
    if (end - 1 <= start) {
        t[node] = a[start];
        return;
    }

    ll mid = (start + end) / 2;
    build_do(node * 2 + 1, start, mid);
    build_do(node * 2 + 2, mid, end);
    t[node] = t[node * 2 + 1] + t[node * 2 + 2];
}

ll query_do(ll node, ll q_start, ll q_end, ll n_start, ll n_end) {
    if (q_end <= n_start || q_start >= n_end) {
        return 0;
    }

    if (q_start <= n_start && n_end <= q_end) {
        return t[node];
    }
    ll mid = (n_start + n_end) / 2;
    return query_do(node * 2 + 1, q_start, q_end, n_start, mid) + query_do(node * 2 + 2, q_start, q_end, mid, n_end);
}

int main() {
    ll N;
    cin >> N;

    for (ll i = 0; i < N; ++i) {
        cin >> a[i];
    }

    build_do(0, 0, N);

    ll K;
    vector<ll> ans;
    cin >> K;

    for (ll i = 0; i < K; ++i) {
        ll a, b;
        cin >> a >> b;
        ans.push_back(query_do(0, a - 1, b, 0, N));
    }

    for (auto a: ans) {
        cout << a << " ";
    }
}