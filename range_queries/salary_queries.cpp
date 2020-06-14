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
      tree_[ii] = v[ii - arr_size_];
    }
    Build();
  }

  // Sum of array on interval [l, r).
  int Query(int l, int r) {
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

  void Modify(int ind, int val) {
    for (tree_[ind += arr_size_] += val; ind > 1; ind >>= 1) {
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

static const int bucket_size = 100;

int find_bucket_idx(int val) {
  if (val % 100 == 0) {
    --val;
  }
  return val / bucket_size;
}

int main() {
  sync_cin;

  int n, q; cin >> n >> q;
  vector<int> p(n);
  cin >> p;

  const int num_buckets = int(1e7);
  SegmentTree st(vector<int>(num_buckets, 0));
  map<int, vector<int>> bucket_map;

  for (int ii = 0; ii < sz(p); ++ii) {
    st.Modify(find_bucket_idx(p[ii]), 1);
    bucket_map[find_bucket_idx(p[ii])].push_back(p[ii]);
  }

  while (q--) {
    char type; cin >> type;
    if (type == '!') {
      int k, x; cin >> k >> x;
      --k;
      int prev_val = p[k];
      int bucket_idx = find_bucket_idx(prev_val);
      vector<int>::iterator it = bucket_map[bucket_idx].begin();
      for (; it != bucket_map[bucket_idx].end(); ++it) {
        if (*it == prev_val) {
          break;
        }
      }
      bucket_map[bucket_idx].erase(it);
      st.Modify(bucket_idx, -1);
      bucket_idx = find_bucket_idx(x);
      bucket_map[bucket_idx].push_back(x);
      st.Modify(bucket_idx, 1);
      p[k] = x;
    } else {
      int a, b; cin >> a >> b;
      int l = find_bucket_idx(a);
      int r = find_bucket_idx(b);
      int ll = l + 1, rr = r;
      int ans = st.Query(ll, rr);
      for (auto num : bucket_map[l]) {
        if (num >= a && num <= b) {
          ++ans;
        }
      }
      if (r <= num_buckets && r != l) {
        for (auto num : bucket_map[r]) {
          if (num <= b && num >= a) {
            ++ans;
          }
        }
      }
      cout << ans << endl;
    }
  }
  return 0;
}
