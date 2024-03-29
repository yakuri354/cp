#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

pair<vector<ll>, vector<ll>> skuf_fast(string &s) {
    const ll n = s.size();
    vector<ll> p(n), c(n), cnt(max(256ll, n), 0);
    for (ll i = 0; i < n; i++)
        cnt[s[i]]++;
    for (ll i = 1; i < 256; i++)
        cnt[i] += cnt[i-1];
    for (ll i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    ll classes = 1;
    for (ll i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    vector<ll> pn(n), cn(n);
    for (ll h = 0; (1 << h) < n; ++h) {
        for (ll i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (ll i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (ll i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (ll i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (ll i = 1; i < n; i++) {
            pair<ll, ll> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<ll, ll> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return {p, c};
}

vector<ll> calc_lcp(string &s, vector<ll> &pos, vector<ll> &cls) {
    const ll n = s.size();
    vector<ll> lcp(n);
    ll curr = 0;
    for (ll i = 0; i < n; i++) {
        if (cls[i] == n - 1) {
            curr = 0;
            continue;
        }
        
        ll nxt = pos[cls[i] + 1];

        while (max(nxt, i) + curr < n && s[i + curr] == s[nxt + curr]) curr++;

        lcp[cls[i]] = curr;
        curr = max(0ll, curr - 1);
    }

    return lcp;
}

void dbg(string &t, vector<ll> &cls) {
    vector<pair<ll, string>> ss;

    for (ll i = 0; i < t.size(); i++) {
        ss.push_back({cls[i], t.substr(i)});
    }

    sort(ss.begin(), ss.end());

    for (auto [cl, s]: ss) {
        cout << s << endl;
    }

    cout << endl;

    // sort(ss.begin(), ss.end(), [](auto a, auto b) {
    //     return a.second < b.second;
    // });

    // for (auto [cl, s]: ss) {
    //     cout << s << endl;
    // }
}

void solve() {
    fstream fin("inputik.txt");
    fin.tie(nullptr);
    fstream fout("outputik.txt");

    string t;
    fin >> t;

    ll n;
    fin >> n;

    t.push_back('$');

    auto [perm, cls] = skuf_fast(t);   
    auto lcp = calc_lcp(t, perm, cls);

    // dbg(t, cls);

    for (ll i = 0; i < n; i++) {
        string s;
        fin >> s;

        s.push_back('#');

        ll lo = 0, hi = t.size();
        while (hi - lo > 1) {
            ll m = (lo + hi) / 2;

            if (lexicographical_compare(t.begin() + perm[m], t.end(), s.begin(), s.end())) {
                lo = m;
            } else {
                hi = m;
            }
        }
        
        if (hi >= t.size()) {
            fout << "0\n";
            continue;
        }

        ll curr_lcp = 0, curr_idx = perm[hi];
        while (curr_idx + curr_lcp < t.size() && curr_lcp < s.size() && t[curr_idx + curr_lcp] == s[curr_lcp]) curr_lcp++;

        vector<ll> ans;
        while (curr_lcp >= s.size() - 1) {
            ans.push_back(curr_idx);
            curr_lcp = min(curr_lcp, lcp[cls[curr_idx]]);
            if (cls[curr_idx] >= t.size() - 1) break;
            curr_idx = perm[cls[curr_idx] + 1];
        }

        sort(ans.begin(), ans.end());

        fout << ans.size() << ' ';
        for (ll i: ans) {
            fout << i + 1 << ' ';
        }
        fout << '\n';
    }

    fout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

