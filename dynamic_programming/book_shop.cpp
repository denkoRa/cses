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

  int n, x; cin >> n >> x;
  vector<int> h(n), s(n);
  cin >> h >> s;

  vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));

  for (int ii = 1; ii <= n; ++ii) {
    for (int jj = 1; jj <= x; ++jj) {
      const int weight = h[ii - 1];
      const int value = s[ii - 1];
      dp[ii][jj] = dp[ii - 1][jj];
      if (weight <= jj) {
        dp[ii][jj] = max(dp[ii][jj], dp[ii - 1][jj - weight] + value);
      }
    }
  }

  int ans = 0;
  for (int ii = 1; ii <= n; ++ii) {
    ans = max(ans, dp[ii][x]);
  }

  cout << ans << endl;
  return 0;
}
