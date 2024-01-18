// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <regex>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

void solve() {
    ll l;
    cin >> l;

    string t;
    getline(cin, t);
    getline(cin, t);

    ll all_sz = t.size();

    regex link_r(R"((http\:\/\/[\S]*))");

    auto link_b = sregex_iterator(t.begin(), t.end(), link_r);
    auto link_e = sregex_iterator();

    vector<string> links;

    for (auto it = link_b; it != link_e; it++) {
        links.push_back(it->str());
    }

    for (ll i = 0; i < links.size(); i++) {
        ll shrink = min(all_sz - l, ll(links[i].size()) - 3);

        if (shrink > 0) {
            for (ll j = 0; j < shrink + 3; j++) links[i].pop_back();
            links[i] += "...";
        }

        all_sz -= shrink;
    }

    auto link_b_1 = sregex_iterator(t.begin(), t.end(), link_r);
    auto link_e_1 = sregex_iterator();

    ll curr = 0, ctr = 0;
    for (auto it = link_b_1; it != link_e_1; it++, ctr++) {
        if (it->position() > curr) {
            cout << t.substr(curr, it->position() - curr);
        }
        cout << links[ctr];
        curr = it->position() + it->length();
    }

    if (t.size() > curr) {
        cout << t.substr(curr, t.size() - curr);
    }

    cout << '\n' << max(0ll, all_sz - l) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
