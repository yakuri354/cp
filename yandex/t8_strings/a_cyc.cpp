// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstddef>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <map>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

struct node {
    ll len = 0, cnt = 0;
    map<ll, node*> t{};
    node* suff = nullptr;
    vector<node *> pref;
};

node *root;
node *head;

const ll maxn = 100;
//const ll maxn = 2e7;

node arr[maxn * 2 + 1];
ll last = 0;

node *alloc() {
    return arr + (last++);
}

void sa_add(char c) {
    node *n = alloc();

    n->len = head->len + 1;
    n->cnt = 1;
    
    node *curr = head;
    while (curr && !curr->t.count(c)) {
        curr->t[c] = n;
        curr = curr->suff;
    }

    if (!curr) {
        head = n;
        n->suff = root;
        return;
    }

    node *s = curr->t[c];

    if (s->len == curr->len + 1) {
        head = n;
        n->suff = s;
        return;
    }

    node *cl = alloc();
    *cl = *s;
    cl->cnt = 0;
    cl->len = curr->len + 1;
    s->suff = cl;
    n->suff = cl;

    while (curr) {
        curr->t[c] = cl;
        curr = curr->suff;
    }

    head = n;
}

void dfs_cnt(node *v) {
    for (node *u: v->pref) {
        dfs_cnt(u);
        v->cnt += u->cnt;
    }
}

void solve() {
    string s;
    cin >> s;

    s += s;
    s.pop_back();

    root = alloc();
    root->len = 0;
    root->suff = nullptr;
    head = root;

    for (char c: s) {
        sa_add(c);
    }

    for (ll i = 1; i < last; i++) {
        arr[i].suff->pref.push_back(&arr[i]);
    }

    dfs_cnt(root);

    node *curr = root;

    for (ll i = 0; i < s.size() / 2 + 1; i++) {
        auto [k, v] = *curr->t.begin();
        curr = v;
    }

    cout << curr->cnt << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

