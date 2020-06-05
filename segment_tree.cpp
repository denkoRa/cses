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

// SegmentTree implementation:
// - assignment range update
// - range sum query
class SegmentTree {
 public:
  SegmentTree(const vector<int>& arr) {
    arr_size_ = sz(arr);
    height_ = sizeof(int) * 8 - __builtin_clz(arr_size_);
    tree_.resize(2 * arr_size_);
    lazy_update_.resize(arr_size_);

    for (int ii = arr_size_; ii < 2 * arr_size_; ++ii) {
      Apply(ii, arr[ii - arr_size_], 1 /* interval_size */);
    }
    Build(0, arr_size_);
  }

  void Modify(int left, int right, const int value) {
    if (value == 0) {
      return;
    }

    // Propagate pending updates.
    Push(left, left + 1);
    Push(right - 1, right);

    bool changed_left_side = false, changed_right_side = false;
    int interval_size = 1;
    for (left += arr_size_, right += arr_size_; left < right;
         interval_size <<= 1, left >>= 1, right >>= 1) {

      if (changed_left_side) {
        Calculate(left - 1, interval_size);
      }
      if (changed_right_side) {
        Calculate(right, interval_size);
      }
      if (left & 1) {
        Apply(left++, value, interval_size);
        changed_left_side = true;
      }
      if (right & 1) {
        Apply(--right, value, interval_size);
        changed_right_side = true;
      }
    }

    for (--left; right > 0; left >>= 1, right >>= 1, interval_size <<= 1) {
      if (changed_left_side) {
        Calculate(left, interval_size);
      }

      // (!changed_left_side || left != right) is for corner case where right
      // and left end up right = left = 1. We must update the root in case
      // changed_left_side is false.
      if (changed_right_side && (!changed_left_side || left != right)) {
        Calculate(right, interval_size);
      }
    }
  }

  // Sum on interval [left, right).
  int Query(int left, int right) {
    cout << "Query l=" << left << " r=" << right << endl;
    Push(left, left + 1);
    Push(right - 1, right);
    cout << "After push " << endl;
    PrintTree(cout);

    int ret = 0;
    for (left += arr_size_, right += arr_size_; left < right;
         left >>= 1, right >>= 1) {

      if (left & 1) {
        ret += tree_[left++];
      }
      if (right & 1) {
        ret += tree_[--right];
      }
    }
    return ret;
  }

  friend ostream& operator<<(ostream& os, const SegmentTree& st) {
    st.PrintTree(os);
    return os;
  }

 private:
  void PrintTree(ostream& os) const {
    for (int ii = 1; ii < 2 * arr_size_; ++ii) {
      os << tree_[ii];
      if (ii < arr_size_) {
        os << "|" << lazy_update_[ii];
      }
      if (is_power_of_2(ii + 1)) {
        os << endl;
      } else {
        os << "\t";
      }
    }
  }

  void Calculate(const int index, const int interval_size) {
    if (lazy_update_[index] == 0) {
      tree_[index] = tree_[index << 1] + tree_[index << 1 | 1];
    } else {
      tree_[index] = lazy_update_[index] * interval_size;
    }
  }

  void Apply(const int index, const int value, const int interval_size) {
    tree_[index] = value * interval_size;
    if (index < arr_size_) {
      lazy_update_[index] = value;
    }
  }

  // Update all ancestors up the tree for interval [l, r).
  void Build(const int l, const int r) {
    int interval_size = 2;
    for (int left = l + arr_size_, right = r + arr_size_ - 1; left > 1;
         interval_size <<= 1) {

      left >>= 1;
      right >>= 1;
      for (int ii = right; ii >= left; --ii) {
        Calculate(ii, interval_size);
      }
    }
  }

  // Propagates updates down the tree for interval [l, r).
  void Push(const int l, const int r) {
    int curr_level = height_;
    int interval_size = 1 << (height_ - 1);
    for (int left = l + arr_size_, right = r + arr_size_ - 1; curr_level > 0;
         --curr_level, interval_size >>= 1) {

      for (int ii = left >> curr_level; ii <= right >> curr_level; ++ii) {
        if (lazy_update_[ii] != 0) {
          Apply(ii << 1, lazy_update_[ii], interval_size);
          Apply(ii << 1 | 1, lazy_update_[ii], interval_size);
          lazy_update_[ii] = 0;
        }
      }
    }
  }

 private:
  int arr_size_;
  int height_;

  vector<int> lazy_update_;
  vector<int> tree_;
};

int main() {
  sync_cin;

  vector<int> v{10, 8, 5, 11, 10, 8, 5, 11, 10, 8, 5, 11, 10, 8, 5, 11};

  SegmentTree st(v);
  cout << st;

  cout << st.Query(0, 4) << endl;

  st.Modify(0, 4, 1);
  cout << st;
  cout << st.Query(0, 4) << endl;

  st.Modify(0, 8, 2);
  cout << st;
  cout << st.Query(0, 8) << endl;

  st.Modify(4, 11, 3);
  cout << st;
  cout << st.Query(0, 16) << endl;
  return 0;
}
