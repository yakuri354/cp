// #pragma GCC optimize("Ofast")
#include <string_view>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll alphabet_sz = 128;

struct node {
    ll term = 0;
    char c;
    node *next[alphabet_sz];

    explicit node(char c) : c(c) {}

    node* &at(char c) {
        return next[c - '0'];
    }
};

void add(node *t, string_view s) {
    if (s.size() == 0) {
        t->term++;
        return;
    }

    if (t->at(s[0]) == nullptr) {
         t->at(s[0]) = new node(s[0]);
    }

    add(t->at(s[0]), s.substr(1));
}

void solve() {

}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
