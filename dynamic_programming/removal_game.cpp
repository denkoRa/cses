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

  int n; cin >> n;
  vector<ll> x(n);
  cin >> x;

  vector<vector<ll>> dp(n, vector<ll>(n, 0));
  ll sum = 0;
  for (int ii = n - 1; ii >= 0; --ii) {
    sum += x[ii];
    for (int jj = ii; jj < n; ++jj) {
      if (ii == jj) {
        dp[ii][jj] = x[ii];
      }
      const ll take_left = x[ii] - (ii < n - 1 ? dp[ii + 1][jj] : 0);
      const ll take_right = x[jj] - (jj > 0 ? dp[ii][jj - 1] : 0);
      dp[ii][jj] = max(take_left, take_right);
    }
  }

  cout << (dp[0][n - 1] + sum) / 2 << endl;
  return 0;
}
