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
  SegmentTree(const vector<int>& x) {
    arr_size_ = sz(x);
    tree_.resize(2 * arr_size_);
    for (int ii = 0; ii < arr_size_; ++ii) {
      Modify(ii, ii + 1, x[ii]);
    }
  }

  void Modify(int l, int r, int val) {
    for (l += arr_size_, r += arr_size_; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        tree_[l++] += val;
      }
      if (r & 1) {
        tree_[--r] += val;
      }
    }
  }

  ll Query(int index) {
    ll ret = 0;
    index += arr_size_;
    while (index >= 1) {
      ret += tree_[index];
      index >>= 1;
    }
    return ret;
  }

 private:
  int arr_size_;

  vector<ll> tree_;
};

int main() {
  sync_cin;

  int n, q; cin >> n >> q;
  vector<int> x(n);
  cin >> x;
  SegmentTree st(x);

  for (int ii = 0; ii < q; ++ii) {
    int type; cin >> type;
    if (type == 1) {
      int a, b, val; cin >> a >> b >> val;
      st.Modify(--a, b, val);
    } else {
      int k; cin >> k;
      --k;
      cout << st.Query(k) << endl;
    }
  }
  return 0;
}
