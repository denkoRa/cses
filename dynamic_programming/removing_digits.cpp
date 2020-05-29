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

bool has_digit(int num, const int digit) {
  while (num) {
    const int d = num % 10;
    if (d == digit) {
      return true;
    }
    num /= 10;
  }
  return false;
}

//-----------------------------------------------------------------------------

int main() {
  sync_cin;
  int n; cin >> n;

  const int INF = int(1e7);
  vector<int> dp(n + 10, INF);

  dp[0] = 0;
  for (int xx = 0; xx <= n; ++xx) {
    for (int dd = 1; dd <= 9; ++dd) {
      const int yy = dd + xx;
      if (has_digit(yy, dd)) {
        dp[yy] = min(dp[yy], dp[xx] + 1);
      }
    }
  }

  cout << dp[n] << endl;
  return 0;
}
