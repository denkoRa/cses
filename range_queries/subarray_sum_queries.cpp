#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <bitset>

#define endl '\n'
#define sync_cin                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define TYPEMAX(type)   std::numeric_limits<type>::max()
#define TYPEMIN(type)   std::numeric_limits<type>::min()

using namespace std;

const int MOD = 1e9 + 7;
const int N = 2e5 + 5;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;

//-----------------------------------------------------------------------------

template<typename T>
inline istream& operator>>(istream& is, vector<T>& v) {
  for (int ii = 0; ii < sz(v); ++ii) {
    is >> v[ii];
  }
  return is;
}

template<typename T>
inline ostream& operator<<(ostream& os, vector<T>& v) {
  for (int ii = 0; ii < sz(v); ++ii) {
    os << v[ii] << " ";
  }
  return os;
}

template<typename T1, typename T2>
inline istream& operator>>(istream& is, pair<T1, T2>& p) {
  is >> p.first >> p.second;
  return is;
}

template<typename T>
inline ostream& operator<<(ostream& os, vector<vector<T>>& mat) {
  for (int ii = 0; ii < sz(mat); ++ii) {
    for (int jj = 0; jj < sz(mat[0]); ++jj) {
      os << mat[ii][jj] << " ";
    }
    os << endl;
  }
  return os;
}

template<typename it>
void compress(it start, it end) {
  typedef typename remove_reference<decltype(*start)>::type T;
  map<T, vector<it>> m;
  for (it ii = start; ii != end; ii++) {
    m[*ii].push_back(ii);
  }
  int t = 0;
  for (auto& [x, v] : m) {
    for (auto& i : v) {
      *i = t;
    }
    ++t;
  }
}

//-----------------------------------------------------------------------------

class SegmentTree {
 public:
  SegmentTree(const vector<ll>& v) {
    arr_size_ = sz(v);
    tree_.resize(2 * arr_size_);
    for (int ii = arr_size_; ii < 2 * arr_size_; ++ii) {
      tree_[ii] = Node(v[ii - arr_size_]);
    }
    Build();
  }

  // Sum of array on interval [l, r).
  ll Query(int l, int r) {
    Node res_l(0), res_r(0);
    for (l += arr_size_, r += arr_size_; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        res_l = Combine(res_l, tree_[l++]);
      }
      if (r & 1) {
        res_r = Combine(tree_[--r], res_r);
      }
    }

    return Combine(res_l, res_r).max_subarray_sum;
  }

  void Modify(int ind, ll val) {
    for (tree_[ind += arr_size_] = Node(val), ind >>= 1; ind >= 1; ind >>= 1) {
      tree_[ind] = Combine(tree_[ind << 1], tree_[ind << 1 | 1]);
    }
  }

 private:
  void Build() {
    for (int ii = arr_size_ - 1; ii > 0; --ii) {
      tree_[ii] = Combine(tree_[ii << 1], tree_[ii << 1 | 1]);
    }
    // PrintTree();
  }

  struct Node;
  Node Combine(const Node& a, const Node& b) {
    Node ret;
    ret.max_subarray_sum =
      max(max(a.max_subarray_sum, b.max_subarray_sum),
          a.max_suffix_sum + b.max_prefix_sum);
    ret.max_prefix_sum = max(a.max_prefix_sum, a.total_sum + b.max_prefix_sum);
    ret.max_suffix_sum = max(b.max_suffix_sum, a.max_suffix_sum + b.total_sum);
    ret.total_sum = a.total_sum + b.total_sum;
    return ret;
  }

 private:
  struct Node {
    ll max_subarray_sum;
    ll max_prefix_sum;
    ll max_suffix_sum;
    ll total_sum;

    Node() {
    }
    Node(ll x) {
      max_subarray_sum = max_prefix_sum = max_suffix_sum = x;
      total_sum = x;
    }

    friend ostream& operator<<(ostream& os, const Node& n) {
      os   << n.total_sum << endl
           << n.max_prefix_sum << endl
           << n.max_suffix_sum << endl
           << n.max_subarray_sum << endl;
      return os;
    }
  };

  vector<Node> tree_;
  int arr_size_;
};

int main() {
  sync_cin;

  int n, m; cin >> n >> m;
  vector<ll> x(n);
  cin >> x;

  SegmentTree st(x);

  while (m--) {
    int k, val; cin >> k >> val;
    st.Modify(k - 1, 1LL * val);
    cout << st.Query(0, n) << endl;
  }
  return 0;
}
