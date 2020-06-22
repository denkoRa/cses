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

class FenwickTree {
 public:
  FenwickTree(int n) {
    n_ = n;
    bit_.resize(n_ + 1, vector<int>(n_ + 1, 0));
  }

  // Add val at 1-based index idx.
  void Add(int xx, int yy, const int val) {
    for (int ii = xx; ii <= n_; ii += ii & -ii) {
      for (int jj = yy; jj <= n_; jj += jj & -jj) {
        bit_[ii][jj] += val;
      }
    }
  }

  // Returns sum at interval [1, idx].
  int Sum(int xx, int yy) const {
    int ret = 0;
    for (int ii = xx; ii >= 1; ii -= ii & -ii) {
      for (int jj = yy; jj >= 1; jj -= jj & -jj) {
        ret += bit_[ii][jj];
      }
    }
    return ret;
  }

 private:
  vector<vector<int>> bit_;
  int n_;
};

int main() {
  sync_cin;

  int n, q; cin >> n >> q;
  vector<string> grid(n);
  cin >> grid;
  FenwickTree ft(n);
  for (int ii = 0; ii < sz(grid); ++ii) {
    for (int jj = 0; jj < sz(grid); ++jj) {
      ft.Add(ii + 1, jj + 1, (grid[ii][jj] == '*' ? 1 : 0));
    }
  }

  while (q--) {
    int type; cin >> type;
    if (type == 1) {
      int y, x;
      cin >> x >> y;
      int upd = 1;
      if (grid[x - 1][y - 1] == '*') {
        upd = -1;
        grid[x - 1][y - 1] = '.';
      } else {
        upd = 1;
        grid[x - 1][y - 1] = '*';
      }
      ft.Add(x, y, upd);
    } else {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      cout << ft.Sum(x2, y2) - ft.Sum(x2, y1 - 1) - ft.Sum(x1 - 1, y2) +
              ft.Sum(x1 - 1, y1 - 1)
           << endl;
    }
  }
  return 0;
}
