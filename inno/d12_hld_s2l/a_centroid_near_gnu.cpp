#include <type_traits>
#pragma GCC optimize("Ofast")
#ifndef DBG
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif
#include <algorithm>
#include <cstdint>
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#include <memory>
#include <new>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
// #include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using ll = int;
using rll = long long;
using ull = unsigned long long;
using fl = long double;

using namespace __gnu_pbds;

namespace __gnu_pbds {
#define PB_DS_CLASS_T_DEC                                                      \
  template <typename Node_CItr, typename Node_Itr, typename Cmp_Fn,            \
            typename _Alloc>

#define PB_DS_CLASS_C_DEC multi_stats<Node_CItr, Node_Itr, Cmp_Fn, _Alloc>

#define PB_DS_BRANCH_POLICY_BASE                                               \
  detail::branch_policy<Node_CItr, Node_Itr, _Alloc>

/// Functor updating ranks of entrees.
template <typename Node_CItr, typename Node_Itr, typename Cmp_Fn,
          typename _Alloc>
class multi_stats : private PB_DS_BRANCH_POLICY_BASE {
private:
  typedef PB_DS_BRANCH_POLICY_BASE base_type;

public:
  typedef Cmp_Fn cmp_fn;
  typedef _Alloc allocator_type;
  typedef typename allocator_type::size_type size_type;
  typedef typename base_type::key_type key_type;
  typedef typename base_type::key_const_reference key_const_reference;

  typedef size_type metadata_type;
  typedef Node_CItr node_const_iterator;
  typedef Node_Itr node_iterator;
  typedef typename node_const_iterator::value_type const_iterator;
  typedef typename node_iterator::value_type iterator;


  /// Returns the order of a key within a sequence. For exapmle, if
  /// r_key is the smallest key, this method will return 0; if r_key
  /// is a key between the smallest and next key, this method will
  /// return 1; if r_key is a key larger than the largest key, this
  /// method will return the size of r_c.
  inline size_type order_of_key(key_const_reference) const;

private:
  /// Const reference to the container's value-type.
  typedef typename base_type::const_reference const_reference;

  /// Const pointer to the container's value-type.
  typedef typename base_type::const_pointer const_pointer;

  /// Const metadata reference.
  typedef typename detail::rebind_traits<_Alloc, metadata_type>::const_reference
      metadata_const_reference;

  /// Metadata reference.
  typedef typename detail::rebind_traits<_Alloc, metadata_type>::reference
      metadata_reference;

  /// Returns the node_const_iterator associated with the tree's root node.
  virtual node_const_iterator node_begin() const = 0;

  /// Returns the node_iterator associated with the tree's root node.
  virtual node_iterator node_begin() = 0;

  /// Returns the node_const_iterator associated with a just-after leaf node.
  virtual node_const_iterator node_end() const = 0;

  /// Returns the node_iterator associated with a just-after leaf node.
  virtual node_iterator node_end() = 0;

  /// Access to the cmp_fn object.
  virtual cmp_fn &get_cmp_fn() = 0;

protected:
  /// Updates the rank of a node through a node_iterator node_it;
  /// end_nd_it is the end node iterator.
  inline void operator()(node_iterator, node_const_iterator) const;


  virtual ~multi_stats();
};
} // namespace __gnu_pbds

PB_DS_CLASS_T_DEC
inline typename PB_DS_CLASS_C_DEC::size_type
PB_DS_CLASS_C_DEC::order_of_key(key_const_reference r_key) const {
  node_const_iterator it = node_begin();
  node_const_iterator end_it = node_end();

  const cmp_fn &r_cmp_fn = const_cast<PB_DS_CLASS_C_DEC *>(this)->get_cmp_fn();
  size_type ord = 0;
  while (it != end_it) {
    node_const_iterator l_it = it.get_l_child();

    if (r_cmp_fn(r_key, this->extract_key(*(*it))))
      it = l_it;
    else if (r_cmp_fn(this->extract_key(*(*it)), r_key)) {
      ord += (*it)->second;
      ord += (l_it == end_it) ? 0 : l_it.get_metadata();
      it = it.get_r_child();
    } else {
      ord += (l_it == end_it) ? 0 : l_it.get_metadata();
      it = end_it;
    }
  }
  return ord;
}

PB_DS_CLASS_T_DEC
inline void PB_DS_CLASS_C_DEC::operator()(node_iterator node_it,
                                          node_const_iterator end_nd_it) const {
  node_iterator l_it = node_it.get_l_child();
  const size_type l_rank = (l_it == end_nd_it) ? 0 : l_it.get_metadata();

  node_iterator r_it = node_it.get_r_child();
  const size_type r_rank = (r_it == end_nd_it) ? 0 : r_it.get_metadata();

  const_cast<metadata_reference>(node_it.get_metadata()) =
      (**node_it).second + l_rank + r_rank;
}

PB_DS_CLASS_T_DEC
PB_DS_CLASS_C_DEC::~multi_stats() {}

struct gt : tree<int, int, less<>, rb_tree_tag, multi_stats> {
  void update_vertex(point_iterator it) {
    update_to_top(it.m_p_nd, (node_update*)this);
  }
};

// using gt = tree<int, int, less<>, rb_tree_tag, multi_stats>;

void insert(gt &t, int x) {
  auto [it, ins] = t.insert({x, 1});
  if (!ins) {
    it->second++;
    t.update_vertex(it);
  }
}

ll less_than(gt &t, int x) { return t.order_of_key(x); }

struct edge {
  ll v, w;

  edge(ll v, ll w) : v(v), w(w) {}
};

class pt2d {
  vector<gt> pts;

public:
  explicit pt2d(ll s) : pts(s + 1) {}

  void add(ll l, ll w) {
    if (l <= 0) {
      return;
    }
    for (; l < pts.size(); l += l & (-l)) {
      insert(pts[l], w);
    }
  }

  ll count(ll l, ll w) {
    ll ans = 0;
    l = min(l, ll(pts.size())) - 1;
    for (; l > 0; l -= l & (-l)) {
      ans += less_than(pts[l], w);
    }
    return ans;
  }
};

vector<vector<edge>> g;
vector<ll> sz;
vector<bool> used;
ll n, max_l, max_w;

void sizes(ll v, ll p) {
  sz[v] = 1;

  for (auto [u, w] : g[v]) {
    if (u == p || used[u]) {
      continue;
    }
    sizes(u, v);
    sz[v] += sz[u];
  }
}

ll centroid(ll v, ll s, ll p) {
  for (auto [u, w] : g[v]) {
    if (u == p || used[u]) {
      continue;
    }
    if (sz[u] > s / 2) {
      return centroid(u, s, v);
    }
  }

  return v;
}

void add_paths(ll v, ll p, ll pl, ll pw, pt2d &s) {
  if (pl > max_l || pw > max_w) {
    return;
  }
  s.add(pl, pw);

  for (auto [u, w] : g[v]) {
    if (u == p || used[u]) {
      continue;
    }

    add_paths(u, v, pl + 1, pw + w, s);
  }
}

ll count_paths(ll v, ll p, ll pl, ll pw, pt2d &all, pt2d &here) {
  if (pl > max_l || pw > max_w) {
    return 0;
  }
  // 2 because we divide by 2 later :(
  ll ans = 2 + all.count(max_l - pl + 1, max_w - pw + 1) -
           here.count(max_l - pl + 1, max_w - pw + 1);

  for (auto [u, w] : g[v]) {
    if (u == p || used[u]) {
      continue;
    }

    ans += count_paths(u, v, pl + 1, pw + w, all, here);
  }

  return ans;
}

ll decompose(ll v) {
  sizes(v, -1);
  ll cs = sz[v];
  ll c = centroid(v, cs, -1);
  used[c] = true;

  ll ans = 0;

  {
    pt2d all(cs);

    add_paths(c, -1, 0, 0, all);

    ll paths = 0;

    for (auto [u, w] : g[c]) {
      if (used[u]) {
        continue;
      }
      pt2d here(cs / 2 + 2);

      add_paths(u, c, 1, w, here);

      paths += count_paths(u, c, 1, w, all, here);
    }

    ans += paths / 2;
  }

  for (auto [u, w] : g[c]) {
    if (used[u]) {
      continue;
    }

    ans += decompose(u);
  }

  return ans;
}

void solve() {
  cin >> n >> max_l >> max_w;
  g.resize(n);
  sz.resize(n);
  used.resize(n);
  
  for (ll i = 0; i < n - 1; i++) {
    ll pi, wi;
    cin >> pi >> wi;

    g[i + 1].emplace_back(pi - 1, wi);
    g[pi - 1].emplace_back(i + 1, wi);
  }

  cout << decompose(0) << endl;
}

int main() {
#ifndef DBG
  freopen("close-vertices.in", "r", stdin);
  freopen("close-vertices.out", "w", stdout);
#endif
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  // ll t; cin >> t; while (t --> 0)
  solve();
}
