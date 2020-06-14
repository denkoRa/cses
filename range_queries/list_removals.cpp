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
bool is_power_of_2(int num) {
  return (num & (num - 1)) == 0;
}


class SegmentTree {
 public:
  SegmentTree(const vector<int>& v) {
    arr_size_ = sz(v);
    tree_.resize(2 * arr_size_);
    for (int ii = arr_size_; ii < 2 * arr_size_; ++ii) {
      tree_[ii] = 1;
    }
    Build();
  }

  // Sum of array on interval [l, r).
  int Query(int r) {
    int l = 0;
    int res = 0;
    for (l += arr_size_, r += arr_size_; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        res += tree_[l++];
      }
      if (r & 1) {
        res += tree_[--r];
      }
    }
    return res;
  }

  // Set arr[ind] = val.
  void Modify(int ind, int val) {
    for (tree_[ind += arr_size_] = val; ind > 1; ind >>= 1) {
      tree_[ind >> 1] = tree_[ind] + tree_[ind ^ 1];
    }
  }

 private:
  void Build() {
    for (int ii = arr_size_ - 1; ii > 0; --ii) {
      tree_[ii] = tree_[ii << 1] + tree_[ii << 1 | 1];
    }
  }

 private:
  vector<int> tree_;
  int arr_size_;
};

int main() {
  sync_cin;

  int n; cin >> n;
  vector<int> x(n);
  cin >> x;

  SegmentTree st(x);

  int q = n;
  while (q--) {
    int pos; cin >> pos;
    int l = -1, r = n + 1;
    int ans = 0;
    while (r - l > 1) {
      int mid = (r + l) >> 1;
      int val = st.Query(mid);
      if (val >= pos) {
        ans = val == pos ? mid : ans;
        r = mid;
      } else {
        l = mid;
      }
    }
    cout << x[ans - 1] << endl;
    st.Modify(ans - 1, 0);
  }

  return 0;
}
 