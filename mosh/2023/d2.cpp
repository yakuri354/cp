// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <chrono>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <iomanip>
#include <fstream>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

const ll inf = 1e12;

string taskid;

uniform_real_distribution<float> fld(0, 1);

ll M;
string SS, A;
vector<pll> segs;
vector<pll> words;

template<typename It1, typename It2>
ll levenstein(It1 l1, It1 r1, It2 l2, It2 r2) {
    ll n = r1 - l1, m = r2 - l2;
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));
    for (ll i = 0; i <= n; i++) {
        dp[i][0] = i;
    }
    for (ll i = 0; i <= m; i++) {
        dp[0][i] = i;
    }
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1;
            if (*(l1 + i - 1) == *(l2 + j - 1)) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
            }
        }
    }

    return dp[n][m];
}

vector<ll> state;
vector<ll> dists;
ll score = 0;

vector<ll> best_state;
ll best_score;

ll getstart(ll x) {
    return accumulate(state.begin(), state.begin() + x, 0ll);
}

void recalc_score() {
    ll s2 = 0;
    ll l = 0;
    for (ll i = 0; i < M; i++) {
        dists[i] = levenstein(SS.begin() + words[l].second, SS.begin() + words[l + state[i] - 1].second, A.begin() + segs[i].first, A.begin() + segs[i].second);
        s2 += dists[i];
        l += state[i];
    }

    score = s2;
}

mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

// bool F(ll old_score, ll new_score, fl temp) {
//     return new_score < old_score || pow(fl(old_score) / fl(new_score), 1/temp) > fld(mt);
// }

inline bool F(ll old_score, ll new_score, fl temp) {
    return new_score < old_score || exp((new_score - old_score) / temp) > fld(mt);
}

void solve(ll t) {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        string w;
        cin >> w;
        ll l = SS.size();
        if (!SS.empty()) {
            SS.push_back(' ');
            l++;
        }
        SS += w;
        words.push_back({l, SS.size()});
    }

    cin >> M;
    for (ll i = 0; i < M; i++) {
        ll k;
        cin >> k;

        ll l = A.size();
        if (!A.empty()) {
            A.push_back(' ');
            l++;
        }

        for (ll i = 0; i < k; i++) {
            string s;
            cin >> s;
            A += s;
            if (i != k - 1) A.push_back(' ');
        }

        segs.push_back({l, A.size()});
    }

    cout << "==== STARTING TEST CASE " << t << " ====" << endl;

    // init

    state.resize(M, 0);
    dists.resize(M, 0);

    {   ll _sum = 0;
        for (ll i = 0; i < M - 1; i++) {
            state[i] = n / M;
            _sum += state[i];
        }
        state[M-1] = n - _sum; }

    
    recalc_score();

    best_score = score;
    best_state = state;

    uniform_int_distribution<ll> Md(0, M - 2);

    fl temp = 1;
    for (ll its = 0; temp > 1e-6 && best_score != 0; its++) {
        if (its % 10000 == 0) {
            cout << "\33[2K\r";
            cout << setw(20) << temp << " " << setw(20) << best_score << " (" << setw(20) << score << ")" << flush;
        }

        ll x = Md(mt);

        if (state[x] == 1 && state[x+1] == 1) continue;

        ll old_score = score;
        ll old_x = state[x];
        ll old_x1 = state[x+1];
        ll old_dist = dists[x];
        ll old_dist1 = dists[x+1];

        // auto old_st = state;
        // auto old_dist = dists;

        ll left = getstart(x);
        score -= dists[x] + dists[x+1];

        if (uniform_int_distribution<ll>(0, 1)(mt) && state[x] > 1) {
            state[x] -= 1;
            state[x+1] += 1;
        } else if (state[x+1] > 1) {
            state[x] += 1;
            state[x+1] -= 1;
        } else {
            score = old_score;
            continue;
        }

        dists[x] = levenstein(SS.begin() + words[left].first, SS.begin() + words[left + state[x] - 1].second, A.begin() + segs[x].first, A.begin() + segs[x].second);
        left += state[x];
        dists[x+1] = levenstein(SS.begin() + words[left].first, SS.begin() + words[left + state[x+1] - 1].second, A.begin() + segs[x+1].first, A.begin() + segs[x+1].second);

        score += dists[x] + dists[x+1];

        // recalc_score(); // todo remove

        if (!F(old_score, score, temp)) {
            score = old_score;
            // state = old_st;
            // dists = old_dist;
            state[x] = old_x;
            state[x+1] = old_x1;
            dists[x] = old_dist;
            dists[x+1] = old_dist1;
        }

        if (score < best_score) {
            best_score = score;
            best_state = state;
        }

        temp *= 0.99999;
    }

    cout << endl << endl;
    for (ll i = 0; i < M; i++) {
        cerr << best_state[i] << ' ';
        cout << best_state[i] << ' ';
    }

    cout << endl;
    cerr << endl;
}

int main(int argc, char **argv) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // taskid = string(argv[1]);
    ll t;
    cin >> t;
    for (ll i = 0; i < t; i++) {
        solve(i);
        // string a, b;
        // cin >> a >> b;
        // cout << levenstein(a.begin(), a.end(), b.begin(), b.end()) << endl;
    }
}


