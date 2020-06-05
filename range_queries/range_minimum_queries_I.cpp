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

//-----------------------------------------------------------------------------

class SegmentTree {
 public:
  SegmentTree(const vector<int>& v) : arr_size_(sz(v)) {
    tree_.resize(2 * arr_size_);
    for (int ii = 0; ii < arr_size_; ++ii) {
      tree_[ii + arr_size_] = v[ii];
    }
    Build(0, arr_size_);
  }

  int Query(int l, int r) {
    int resl = int(1e9);
    int resr = int(1e9);
    for (l += arr_size_, r += arr_size_; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        resl = min(resl, tree_[l++]);
      }
      if (r & 1) {
        resr = min(resr, tree_[--r]);
      }
    }
    return min(resr, resl);
  }

 private:
  void Build(int l, int r) {
    for (l += arr_size_, r += arr_size_ - 1; l > 0; l >>= 1, r >>= 1) {
      for (int ii = l; ii <= r; ++ii) {
        Calculate(ii);
      }
    }
  }

  void Calculate(int index) {
    if (index < arr_size_) {
      tree_[index] = min(tree_[index << 1], tree_[index << 1 | 1]);
    }
  }

 private:
  vector<int> tree_;
  const int arr_size_;
};

int main() {
  sync_cin;

  int n, q; cin >> n >> q;
  vector<int> x(n);
  cin >> x;
  SegmentTree st(x);

  for (int ii = 0; ii < q; ++ii) {
    int a, b; cin >> a >> b;
    --a;
    cout << st.Query(a, b) << endl;
  }
  return 0;
}
