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

//-----------------------------------------------------------------------------

int main() {
  sync_cin;

  int n; cin >> n;
  vector<string> grid(n);
  cin >> grid;

  vector<vector<int>> dp(n, vector<int>(n, 0));
  dp[0][0] = 1;
  if (grid[0][0] == '*') {
    cout << 0 << endl;
    return 0;
  }

  for (int ii = 0; ii < n; ++ii) {
    for (int jj = 0; jj < n; ++jj) {
      if (grid[ii][jj] == '*') {
        continue;
      }
      if (ii > 0 && grid[ii - 1][jj] != '*') {
        dp[ii][jj] += dp[ii - 1][jj];
        dp[ii][jj] %= MOD;
      }
      if (jj > 0 && grid[ii][jj - 1] != '*') {
        dp[ii][jj] += dp[ii][jj - 1];
        dp[ii][jj] %= MOD;
      }
    }
  }

  cout << dp[n - 1][n - 1] << endl;
  return 0;
}
