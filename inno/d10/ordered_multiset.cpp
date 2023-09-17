// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <functional>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

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
  auto fd = t.find(x);
  if (fd == t.end()) {
    t.insert({x, 1});
  } else {
    fd->second++;
    t.update_vertex(fd);
  }
}

ll less_than(gt &t, int x) { return t.order_of_key(x); }

void solve() {
    gt t;

    for (;;) {
        ll ty;
        cin >> ty;

        if (ty == 1) {
            ll x, y;
            cin >> x >> y;
            auto z = t.insert({x, y});
            
            // insert(t, x);
        }

        if (ty == 2) {
            ll x;
            cin >> x;

            cout << less_than(t, x) << endl;
        }

        if (ty == 3) {
            for (auto it = t.begin(); it != t.end(); it++) {
                cout << "{" << it->first << ", " << it->second << " -> " << it.m_p_nd->get_metadata() << "} ";
            }
            cout << endl;
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
