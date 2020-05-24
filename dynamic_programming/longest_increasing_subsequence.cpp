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
  vector<int> arr(n); cin >> arr;

  vector<int> lis(n + 1, TYPEMAX(int));
  lis[0] = TYPEMIN(int);

  for (int ii = 0; ii < n; ++ii) {
    auto iter = lower_bound(lis.begin(), lis.end(), arr[ii]);
    const int idx = iter - lis.begin();
    lis[idx] = arr[ii];
  }

  int ans = 0;
  for (int ii = 1; ii <= n; ++ii) {
    if (lis[ii] < TYPEMAX(int)) {
      ans = ii;
    }
  }
  cout << ans << endl;

  return 0;
}
