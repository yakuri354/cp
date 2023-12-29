#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const ll MAX_N = 1e4;

//ll t[MAX_N*4];
//ll t2[MAX_N*4];
//ll a[MAX_N];
//
//void build_do(ll node, ll start, ll end) {
//    if (end - 1 <= start) {
//        t[node] = a[start];
//        return;
//    }
//
//    ll mid = (start + end) / 2;
//    build_do(node * 2 + 1, start, mid);
//    build_do(node * 2 + 2, mid, end);
//    t[node] = min(t[node * 2 + 1], t[node * 2 + 2]);
//}
//void build_do2(ll node, ll start, ll end) {
//    if (end - 1 <= start) {
//        t2[node] = a[start];
//        return;
//    }
//
//    ll mid = (start + end) / 2;
//    build_do2(node * 2 + 1, start, mid);
//    build_do2(node * 2 + 2, mid, end);
//    t2[node] = max(t2[node * 2 + 1], t2[node * 2 + 2]);
//}
//
//ll query_do(ll node, ll q_start, ll q_end, ll n_start, ll n_end) {
//    if (q_end <= n_start || q_start >= n_end) {
//        return UINT32_MAX;
//    }
//
//    if (q_start <= n_start && n_end <= q_end) {
//        return t[node];
//    }
//    ll mid = (n_start + n_end) / 2;
//    return min(query_do(node * 2 + 1, q_start, q_end, n_start, mid), query_do(node * 2 + 2, q_start, q_end, mid, n_end));
//}
//
//ll query_do2(ll node, ll q_start, ll q_end, ll n_start, ll n_end) {
//    if (q_end <= n_start || q_start >= n_end) {
//        return INT32_MIN;
//    }
//
//    if (q_start <= n_start && n_end <= q_end) {
//        return t2[node];
//    }
//    ll mid = (n_start + n_end) / 2;
//    return max(query_do2(node * 2 + 1, q_start, q_end, n_start, mid), query_do2(node * 2 + 2, q_start, q_end, mid, n_end));
//}
//
//int main() {
//    ll T;
//    cin >> T;
//    for (int rep = 0; rep < T; ++rep) {
//        ll N;
//        cin >> N;
//
//        for (int i = 0; i < 4 * N; ++i) {
//            t[i] = UINT32_MAX;
//            t2[i] = INT32_MIN;
//        }
//
//        for (ll i = 0; i < N; ++i) {
//            cin >> a[i];
//        }
//
//        build_do(0, 0, N);
//        build_do2(0, 0, N);
//
//        for (int l = 1; l < N; ++l) {
//            if (query_do2(0, 0, l, 0, N) > query_do(0, l, N, 0, N)) {
//                cout << "YES\n";
//                goto next;
//            }
//        }
//
//        cout << "NO\n";
//        next: ;
//    }
//}

ll a[100];

int main() {
    ll T;
    cin >> T;

    for (int rep = 0; rep < T; ++rep) {
        ll N;
        cin >> N;
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }

        ll counter = 0;

        for (int l = 0; l < N; ++l)
            for (int r = l; r < N; ++r) {
                counter += r - l + 1;
                for (int i = l; i <= r; ++i)
                    if (a[i] == 0) counter++;
            }
        cout << counter << "\n";
    }
}