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

  ll n; cin >> n;

  ll ans;
  ll sum = n * (n + 1) / 2;
  if (sum & 1) {
    ans = 0;
  } else {
    ll target_sum = sum / 2;
    vector<vector<ll>> dp(n + 1, vector<ll>(target_sum + 1, 0));
    dp[0][0] = 1;
    for (int ii = 1; ii <= n - 1; ++ii) {
      for (int xx = 0; xx <= target_sum; ++xx) {
        dp[ii][xx] = dp[ii - 1][xx];
        const ll left = xx - ii;
        if (left >= 0) {
          dp[ii][xx] += dp[ii - 1][left];
          dp[ii][xx] %= MOD;
        }
      }
    }
    ans = dp[n - 1][target_sum];
  }

  cout << ans << endl;
  return 0;
}
