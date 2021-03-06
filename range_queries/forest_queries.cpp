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

int main() {
  sync_cin;
  int n, q; cin >> n >> q;

  vector<vector<int>> count(n, vector<int>(n, 0));
  for (int ii = 0; ii < n; ++ii) {
    string row;
    cin >> row;
    int in_row_so_far = 0;
    for (int jj = 0; jj < n; ++jj) {
      if (row[jj] == '*') {
        ++in_row_so_far;
      }
      count[ii][jj] = in_row_so_far + (ii > 0 ? count[ii - 1][jj] : 0);
    }
  }

  while (q--) {
    int x, y, s, t;
    cin >> x >> y >> s >> t;
    --x; --y; --s; --t;
    cout << count[s][t] - (y > 0 ? count[s][y - 1] : 0) -
            (x > 0 ? count[x - 1][t] : 0) + 
            (x > 0 && y > 0 ? count[x - 1][y - 1] : 0)
         << endl;
  }

  return 0;
}
