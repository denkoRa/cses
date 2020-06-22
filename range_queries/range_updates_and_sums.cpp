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

bool is_power_of_2(int num) {
  return (num & (num - 1)) == 0;
}

// SegmentTree with LazyProp technique for task with following queries:
// 1. Increase each value in range [a,b] by x.
// 2. Set each value in range [a,b] to x.
// 3. Calculate the sum of values in range [a,b].
class SegmentTree {
 private:
  struct Node {
    ll assign_val;
    ll add_val;
    ll value;
    Node() {
      assign_val = 0;
      add_val = 0;
      value = 0;
    }
    Node(ll v) {
      value = v;
      assign_val = add_val = 0;
    }
  };

 public:

  SegmentTree(const vector<ll>& start_arr) {
    arr_size_ = sz(start_arr);
    tree_.resize(2 * arr_size_);
    height_ = sizeof(int) * 8 - __builtin_clz(arr_size_);
    for (int ii = 0; ii < arr_size_; ++ii) {
      tree_[ii + arr_size_] = Node(start_arr[ii]);
    }
    Build(0, arr_size_);
  }

  void Calc(int idx, int interval_size) {
    if (tree_[idx].assign_val) {
      tree_[idx].value = interval_size * tree_[idx].assign_val;
    } else {
      tree_[idx].value = tree_[idx << 1].value + tree_[idx << 1 | 1].value;
    }
    if (tree_[idx].add_val) {
      tree_[idx].value += interval_size * tree_[idx].add_val;
    }
  }

  void Apply(int idx, ll value, int interval_size, bool is_assign) {
    if (is_assign) {
      tree_[idx].value = interval_size * value;
      if (idx < arr_size_) {
        tree_[idx].assign_val = value;
        tree_[idx].add_val = 0;
      }
    } else {
      tree_[idx].value += interval_size * value;
      if (idx < arr_size_) {
        tree_[idx].add_val += value;
      }
    }
  }

  void Build(int l, int r) {
    int k = 2;
    for (l += arr_size_, r += arr_size_ - 1; l > 1; k <<= 1) {
      l >>= 1;
      r >>= 1;
      for (int ii = r; ii >= l; --ii) {
        Calc(ii, k);
      }
    }
  }

  void Push(int l, int r) {
    int s = height_;
    int k = 1 << (height_ - 1);
    for (l += arr_size_, r += arr_size_ - 1; s > 0; --s, k >>= 1) {
      for (int ii = l >> s; ii <= r >> s; ++ii) {
        if (tree_[ii].assign_val) {
          Apply(ii << 1, tree_[ii].assign_val, k, true);
          Apply(ii << 1 | 1, tree_[ii].assign_val, k, true);
          tree_[ii].assign_val = 0;
        }
        if (tree_[ii].add_val) {
          Apply(ii << 1, tree_[ii].add_val, k, false);
          Apply(ii << 1 | 1, tree_[ii].add_val, k, false);
          tree_[ii].add_val = 0;
        }
      }
    }
  }

  void Modify(int l, int r, ll value, bool is_assign) {
    Push(l, l + 1);
    Push(r - 1, r);
    int ll = l, rr = r;
    int k = 1;
    for (l += arr_size_, r += arr_size_; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l & 1) {
        Apply(l++, value, k, is_assign);
      }
      if (r & 1) {
        Apply(--r, value, k, is_assign);
      }
    }
    Build(ll, ll + 1);
    Build(rr - 1, rr);
  }

  ll Query(int l, int r) {
    Push(l, l + 1);
    Push(r - 1, r);
    ll res = 0;
    for (l += arr_size_, r += arr_size_; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        res += tree_[l++].value;
      }
      if (r & 1) {
        res += tree_[--r].value;
      }
    }
    return res;
  }

  void PrintTree() const {
    for (int ii = 1; ii < 2 * arr_size_; ++ii) {
      cout << tree_[ii].value;
      if (is_power_of_2(ii + 1)) {
        cout << endl;
      } else {
        cout << "\t";
      }
    }
  }

 private:
  vector<Node> tree_;
  int height_;
  int arr_size_;
};

int main() {
  sync_cin;

  int n, q;
  cin >> n >> q;

  vector<ll> arr(n);
  cin >> arr;

  SegmentTree st(arr);

  while (q--) {
    int t; cin >> t;
    if (t < 3) {
      int a, b, x;
      cin >> a >> b >> x;
      st.Modify(a - 1, b, x, (t == 2) /* is_assign */);
    } else {
      int a, b;
      cin >> a >> b;
      cout << st.Query(a - 1, b) << endl;
    }
  }

  return 0;
}
