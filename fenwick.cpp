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

// Basic FenwickTree for Point Update and Range Query.
class FenwickTree {
 public:
  FenwickTree(const vector<int>& in) {
    n_ = sz(in);
    bit_.resize(n_ + 1, 0);
    for (int ii = 0; ii < n_; ++ii) {
      Add(ii + 1, in[ii]);
    }
  }

  // Add val at 1-based index idx.
  void Add(int idx, const int val) {
    for (; idx <= n_; idx += idx & -idx) {
      bit_[idx] += val;
    }
  }

  // Returns sum at interval [1, idx].
  int Sum(int idx) const {
    int ret = 0;
    for (; idx >= 1; idx -= idx & -idx) {
      ret += bit_[idx];
    }
    return ret;
  }

  // Returns sum at interval [l, r].
  int Sum(int l, int r) const {
    return Sum(r) - Sum(l - 1);
  }

  friend ostream& operator<<(ostream& os, const FenwickTree& ft) {
    os << "Size=" << ft.n_ << endl;
    for (int ii = 1; ii <= ft.n_; ++ii) {
      os << ft.bit_[ii] << " ";
    }
    os << endl;
    return os;
  }

 private:
  vector<int> bit_;
  int n_;
};

// FenwickTree RangeUpdate PointQuery
class FenwickTreeRUPQ : public FenwickTree {
 public:
  FenwickTreeRUPQ(const int sz) :
    FenwickTree(vector<int>(sz, 0)) {
  }

  int Get(const int idx) const {
    return Sum(idx);
  }

  void RangeAdd(const int l, const int r, const int val) {
    Add(l, val);
    Add(r + 1, -val);
  }

 private:
  // Hide Add and Sum.
  using FenwickTree::Add;
  using FenwickTree::Sum;
};

// FenwickTree RangeUpdate RangeQuery
class FenwickTreeRURQ {
 public:
  FenwickTreeRURQ(const int sz) : n_(sz) {
    b1_.resize(n_ + 1, 0);
    b2_.resize(n_ + 1, 0);
  }

  FenwickTreeRURQ(const vector<int>& v) {
    n_ = sz(v);
    b1_.resize(n_ + 1, 0);
    b2_.resize(n_ + 1, 0);
    for (int ii = 0; ii < n_; ++ii) {
      // Update just one at the time.
      RangeAdd(ii + 1, ii + 1, v[ii]);
    }
  }

  // Add val to all elements on interval [l, r].
  void RangeAdd(const int l, const int r, const int val) {
    Add(b1_, l, val);
    Add(b1_, r + 1, -val);
    Add(b2_, l, val * (l - 1));
    Add(b2_, r + 1, -val * r);
  }

  // Prefix Sum [1, idx].
  // After update (l, r, x):
  // 3 cases for sum query:
  // 1) i < l => Sum[1, i] = i * 0 - 0.
  // 2) l <= i <= r => Sum[1, i] = val * i - val * (l - 1) = val * (i - l - 1).
  // 3) r < i => Sum[1, i] = val * i + (-val) * i - val * (l - 1) -
  //                         (-val) * r = val * (r - l + 1).
  int Sum(const int idx) const {
    return Sum(b1_, idx) * idx - Sum(b2_, idx);
  }

  // Range Sum [l, r].
  int Sum(const int l, const int r) const {
    return Sum(r) - Sum(l - 1);
  }

  friend ostream& operator<<(ostream& os, const FenwickTreeRURQ& ft) {
    os << "Size=" << ft.n_ << endl;
    for (int ii = 1; ii <= ft.n_; ++ii) {
      os << ft.b1_[ii] << " ";
    }
    os << endl;
    for (int ii = 1; ii <= ft.n_; ++ii) {
      os << ft.b2_[ii] << " ";
    }
    os << endl;
    return os;
  }

 private:
  void Add(vector<int>& vec, int idx, const int val) {
    for (; idx <= n_; idx += idx & -idx) {
      vec[idx] += val;
    }
  }

  int Sum(const vector<int>& vec, int idx) const {
    int ret = 0;
    for (; idx >= 1; idx -= idx & -idx) {
      ret += vec[idx];
    }
    return ret;
  }

 private:
  vector<int> b1_;
  vector<int> b2_;
  int n_;
};

int main() {
  sync_cin;
  
  cout << "===============" << endl;
  cout << "Test: Point Update + Range Query" << endl;
  vector<int> a{1, 3, 4, 8, 6, 1, 4, 2};
  int n = sz(a);
  FenwickTree ft(a);
  cout << ft;

  for (int ii = 1; ii <= n; ++ii) {
    cout << ft.Sum(ii) << endl;
  }

  cout << ft;
  cout << ft.Sum(4) - ft.Sum(3) << endl;
  cout << ft.Sum(5) - ft.Sum(4) << endl;
  cout << ft;

  cout << "===============" << endl;
  cout << "Test: Range Update + Point Query" << endl;
  FenwickTreeRUPQ ft2(10 /* size */);
  ft2.RangeAdd(3, 6, 11);
  cout << ft2;
  cout << ft2.Get(4) << endl;
  ft2.RangeAdd(5, 7, 5);
  cout << ft2.Get(6) << endl;
  cout << ft2;
  ft2.RangeAdd(6, 6, -1);
  cout << ft2.Get(6) << endl; 

  cout << "===============" << endl;
  cout << "Test: Range Update + Range Query" << endl;
  vector<int> v{1, 3, 2, 7, 3, 4}; // S = 20
  FenwickTreeRURQ ft3(v);

  cout << ft3;
  cout << ft3.Sum(1, 1) << endl;
  cout << ft3.Sum(2, 2) << endl;
  cout << ft3.Sum(3, 3) << endl;
  cout << ft3.Sum(4, 4) << endl;
  cout << ft3.Sum(5, 5) << endl;
  cout << ft3.Sum(6, 6) << endl;
  cout << ft3.Sum(1, 6) << endl;

  ft3.RangeAdd(2, 4, -1);
  cout << ft3.Sum(3, 3) << endl;
  cout << ft3.Sum(1, 6) << endl;

  return 0;
}
