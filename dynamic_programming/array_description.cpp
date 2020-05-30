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

void update_dp(const int cur_pos,
               const int cur_val,
               const int max_val,
               vector<vector<int>>& dp) {

 if (cur_val > 1) {
    dp[cur_pos][cur_val] += dp[cur_pos - 1][cur_val - 1];
    dp[cur_pos][cur_val] %= MOD;
  }
  if (cur_val < max_val) {
    dp[cur_pos][cur_val] += dp[cur_pos - 1][cur_val + 1];
    dp[cur_pos][cur_val] %= MOD;
  }
  dp[cur_pos][cur_val] += dp[cur_pos - 1][cur_val];
  dp[cur_pos][cur_val] %= MOD; 
}

//-----------------------------------------------------------------------------

int main() {
  sync_cin;

  int n; cin >> n;
  int m; cin >> m;

  vector<int> x(n);
  cin >> x;

  vector<vector<int>> dp(n, vector<int>(m + 1, 0));
  for (int jj = 1; jj <= m; ++jj) {
    if (x[0] == 0) {
      dp[0][jj] = 1;
    } else {
      dp[0][jj] = x[0] == jj ? 1 : 0;
    }
  }

  for (int ii = 1; ii < n; ++ii) {
    if (x[ii] == 0) {
      for (int jj = 1; jj <= m; ++jj) {
        update_dp(ii, jj, m, dp);
      }
    } else {
      update_dp(ii, x[ii], m, dp);
    }
  }

  int ans = 0;
  for (int jj = 1; jj <= m; ++jj) {
    ans += dp[n - 1][jj];
    ans %= MOD;
  }

  cout << ans << endl;
  return 0;
}
