// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll pow1 = 1e9;

vector<ll> skuf(string s) {
    ll n = s.size();
    vector<ll> cls(n);

    for (ll i = 0; i < n; i++) {
        cls[i] = s[i];
    }

    for (ll l = 1; l < n * 2; l *= 2) {
        vector<pair<ll, ll>> v;
        for (ll i = 0; i < n; i++) {
            v.push_back({cls[i] * pow1 + cls[(i + l) % n], i});
        }

        sort(v.begin(), v.end());

        ll prev = -1, c1 = -1;
        for (ll i = 0; i < n; i++) {
            if (v[i].first > prev) {
                prev = v[i].first;
                c1++;
            }
            cls[v[i].second] = c1;
        }
    }

    return cls;
}

vector<ll> skuf_fast(string &s) {
    const ll n = s.size();
    vector<int> p(n), c(n), cnt(max(256ll, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < 256; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
    
}

void solve() {
    string t;
    cin >> t;

    t.push_back('$');

    auto cls = skuf(t);   

    vector<pair<ll, string>> ss;

    for (ll i = 0; i < t.size(); i++) {
        ss.push_back({cls[i], t.substr(i)});
    }

    sort(ss.begin(), ss.end());

    for (auto [cl, s]: ss) {
        cout << s << endl;
    }

    cout << endl;

    sort(ss.begin(), ss.end(), [](auto a, auto b) {
        return a.second < b.second;
    });

    for (auto [cl, s]: ss) {
        cout << s << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
