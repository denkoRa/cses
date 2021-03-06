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

const int INF = 1e9;
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

  int n, x; cin >> n >> x;
  vector<int> c(n + 1);
  for (int jj = 1; jj <= n; ++jj) {
    cin >> c[jj];
  }
  sort(c.begin(), c.end());

  vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));
  dp[0][0] = 1;
  for (int ii = 1; ii <= n; ++ii) {
    for (int jj = 0; jj <= x; ++jj) {
      dp[ii][jj] = dp[ii - 1][jj];
      if (jj - c[ii] >= 0) {
        dp[ii][jj] += dp[ii][jj - c[ii]];
        dp[ii][jj] %= MOD;
      }
    }
  }
 
  cout << dp[n][x] << endl;
  return 0;
}
