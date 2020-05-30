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

  int a, b; cin >> a >> b;

  vector<vector<int>> dp(a, vector<int>(b, a * b));

  dp[0][0] = 0;
  for (int ii = 1; ii < max(a, b); ++ii) {
    if (ii < a) {
      dp[ii][0] = ii;
    }
    if (ii < b) {
      dp[0][ii] = ii;
    }
  }

  for (int ii = 1; ii < a; ++ii) {
    for (int jj = 1; jj < b; ++jj) {
      if (ii == jj) {
        dp[ii][jj] = 0;
      } else {
        for (int kk = 0; kk < jj; ++kk) {
          dp[ii][jj] = min(dp[ii][jj], dp[ii][jj - kk - 1] + dp[ii][kk] + 1);
        }
        for (int kk = 0; kk < ii; ++kk) {
          dp[ii][jj] = min(dp[ii][jj], dp[ii - kk - 1][jj] + dp[kk][jj] + 1);
        }
      }
    }
  }

  cout << dp[a - 1][b - 1] << endl;
  return 0;
}
