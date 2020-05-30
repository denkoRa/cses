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

  string a, b; cin >> a >> b;

  vector<vector<int>> dp(sz(a) + 1, vector<int>(sz(b) + 1, (int)1e6));
  for (int ii = 0; ii <= sz(a); ++ii) {
    dp[ii][0] = ii;
  }
  for (int jj = 0; jj <= sz(b); ++jj) {
    dp[0][jj] = jj;
  }

  for (int ii = 1; ii <= sz(a); ++ii) {
    const char x = a[ii - 1];
    for (int jj = 1; jj <= sz(b); ++jj) {
      const char y = b[jj - 1];
      if (x == y) {
        dp[ii][jj] = dp[ii - 1][jj - 1];
      } else {
        dp[ii][jj] = min(dp[ii][jj], dp[ii][jj - 1] + 1);
        dp[ii][jj] = min(dp[ii][jj], dp[ii - 1][jj] + 1);
        dp[ii][jj] = min(dp[ii][jj], dp[ii - 1][jj - 1] + 1);
      }
    }
  }

  cout << dp[sz(a)][sz(b)] << endl;
  return 0;
}
