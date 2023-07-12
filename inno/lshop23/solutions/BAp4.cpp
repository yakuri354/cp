#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct Query {
    ll l, r, id;
};

const ll SZ = 318;
const ll MAX_N = 131072;

vector<ll> resolve(ll n, const vector<ll>& src, const vector<pair<ll, ll>>& queries) {
    vector<vector<Query>> blocks(SZ);
    for (ll i = 0; i < ll(queries.size()); ++i) {
        blocks[queries[i].first / SZ].push_back({queries[i].first, queries[i].second, i});
    }

    for (auto& block : blocks) {
        sort(block.begin(), block.end(), [&](const Query& a, const Query& b) {
            return a.r < b.r;
        });
    }

    vector<ll> prefXor(n + 1);
    for (ll i = 1; i <= n; ++i) {
        prefXor[i] = prefXor[i - 1] ^ src[i];
    }

    vector<ll> res(queries.size());
    for (ll i = 0; i < SZ; ++i) {
        ll l = i * SZ;
        ll r = l - 1;
        ll cur = 0;
        vector<int> cntL(MAX_N);
        vector<int> cntR(MAX_N);
        if (l == 0) {
            l = 1;
            r = 0;
        }

        if (l > n) {
            break;
        }

        for (const auto& query : blocks[i]) {
            while (r < query.r) {
                ++r;
                ++cntL[prefXor[r - 1]];
                cur += cntL[prefXor[r]];
                ++cntR[prefXor[r]];
            }

            while (l < query.l) {
                cur -= cntR[prefXor[l - 1]];
                --cntL[prefXor[l - 1]];
                --cntR[prefXor[l]];
                ++l;
            }

            while (l > query.l) {
                --l;
                ++cntR[prefXor[l]];
                cur += cntR[prefXor[l - 1]];
                ++cntL[prefXor[l - 1]];
            }

            res[query.id] = (query.r - query.l + 1) * (query.r - query.l + 2) / 2 - cur;
        }
    }

    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n;
    cin >> n;
    vector<ll> src(n + 1);
    for (ll i = 1; i <= n; ++i) {
        cin >> src[i];
    }

    ll q;
    cin >> q;
    vector<pair<ll, ll>> queries(q);
    for (auto& item : queries) {
        cin >> item.first >> item.second;
    }

    vector<ll> res = resolve(n, src, queries);
    for (const auto& item : res) {
        cout << item << '\n';
    }

    return 0;
}
