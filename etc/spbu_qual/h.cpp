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

// string token = "aboba";
string token = "0111101011101011000001101110101101110101010110110001101000000001111110111011011010111010101001011101";

void send() {
    ll n;
    string s;
    cin >> n >> s;

    cout << s + token << endl;
}

void receive() {
    ll n;
    string s;
    cin >> n >> s;

    s += s;

    vector<ull> p(s.size()), h(s.size());
    const ull P = 1e9 + 7;

    p[0] = 1;
    for (ll i = 1; i < s.size(); i++) {
        p[i] = p[i - 1] * P;
    }

    h[0] = p[s.size() - 1] * s[0];
    for (ll i = 1; i < s.size(); i++) {
        h[i] = h[i-1] + s[i] * p[s.size() - i - 1];
    }

    ull ht = token[0] * p[s.size()-1];
    for (ll i = 1; i < token.size(); i++) {
        ht += token[i] * p[s.size() - i - 1];
    }

    ll ans = -1;
    for (ll i = 0; i < n; i++) {
        ull h1 = h[i + token.size() - 1];
        if (i > 0) h1 -= h[i - 1];
        h1 *= p[i];

        if (h1 == ht) {
            if (ans == -1) ans = i;
            else {
                exit(-1);
            }
        }
    }

    if (ans == -1) {
        exit(-1);
    }

    string s1 = s.substr(0, n);
    rotate(s1.begin(), s1.begin() + ans, s1.end());

    for (ll i = token.size(); i < s1.size(); i++) {
        cout << s1[i];
    }

    cout << endl;
}

void solve() {
    string t;
    cin >> t;

    if (t == "send") send();
    else if (t == "receive") receive();
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
