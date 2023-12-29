// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

template<class T, ll N>
class SegmentTree {
    ll t[N * 2];
    ll n;

    void init(ll n) {  // build the tree
        this->n = n;
        for (ll i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
    }

    void modify(ll p, ll value) {  // set value at position p
        for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
    }

    ll query(ll l, ll r) {  // sum on ll [l, r)
        ll res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += t[l++];
            if (r&1) res += t[--r];
        }
        return res;
    }
}

template <class T, ll V>
class HeavyLight {
  ll parent[V], heavy[V], depth[V];
  ll root[V], treePos[V];
  SegmentTree<T, V> tree;

  template <class G>
  ll dfs(const G& graph, ll v) {
    ll size = 1, maxSubtree = 0;
    for (ll u : graph[v]) if (u != parent[v]) {
      parent[u] = v;
      depth[u] = depth[v] + 1;
      ll subtree = dfs(graph, u);
      if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
      size += subtree;
    }
    return size;
  }

  template <class BinaryOperation>
  void processPath(ll u, ll v, BinaryOperation op) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) swap(u, v);
      op(treePos[root[v]], treePos[v] + 1);
    }
    if (depth[u] > depth[v]) swap(u, v);
    op(treePos[u] + 1, treePos[v] + 1);
  }

public:
  template <class G>
  void init(const G& graph) {
    ll n = graph.size();
    fill_n(heavy, n, -1);
    parent[0] = -1;
    depth[0] = 0;
    dfs(graph, 0);
    for (ll i = 0, currentPos = 0; i < n; ++i)
      if (parent[i] == -1 || heavy[parent[i]] != i)
        for (ll j = i; j != -1; j = heavy[j]) {
          root[j] = i;
          treePos[j] = currentPos++;
        }
    tree.init(n);
  }

  void set(ll v, const T& value) {
    tree.set(treePos[v], value);
  }

  // void modifyPath(ll u, ll v, const T& value) {
  //   processPath(u, v, [this, &value](ll l, ll r) { tree.modify(l, r, value); });
  // }

  T queryPath(ll u, ll v) {
    T res = T();
    processPath(u, v, [this, &res](ll l, ll r) { res.add(tree.query(l, r)); });
    return res;
  }
};

void solve() {
    ll n;
    cin >> n;
    
    for (ll i = 0; i < n-1; i++) {
        
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
