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
  vector<int> x(n);
  cin >> x;

  int sum = 0;
  for_each(x.begin(), x.end(), [&sum](int num) { sum += num; });

  vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));
  dp[0][0] = 1;
  for (int ii = 1; ii <= n; ++ii) {
    for (int ss = 0; ss <= sum; ++ss) {
      dp[ii][ss] += dp[ii - 1][ss];
      if (x[ii - 1] <= ss) {
        dp[ii][ss] += dp[ii - 1][ss - x[ii - 1]];
      }
    }
  }

  vector<int> ans;
  for (int ii = 1; ii <= sum; ++ii) {
    if (dp[n][ii]) {
      ans.emplace_back(ii);
    }
  }
  cout << sz(ans) << endl;
  for_each(ans.begin(), ans.end(), [](int x) { cout << x << " "; });
  return 0;
}
