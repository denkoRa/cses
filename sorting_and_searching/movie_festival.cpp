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

int main() {
  sync_cin;

  int n; cin >> n;
  vector<pii> movies;
  for (int ii = 0; ii < n; ++ii) {
    int a, b; cin >> a >> b;
    movies.emplace_back(a, b);
  }

  sort(movies.begin(), movies.end(),
       [](pii a, pii b) -> bool {
         return a.second < b.second ||
                (a.second == b.second && a.first < b.first);
       });

  int cur_end = movies[0].second;
  int ans = 1;
  for (int ii = 1; ii < sz(movies); ++ii) {
    if (movies[ii].first >= cur_end) {
      cur_end = movies[ii].second;
      ++ans;
    }
  }

  cout << ans << endl;

  return 0;
}
