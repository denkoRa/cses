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
#include <list>

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
 
  int n, k; cin >> n >> k;
 
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

  multiset<int> s;
  int ans = 0;
  for (int ii = 0; ii < k; ++ii) {
    s.insert(0);
  }

  for (int ii = 0; ii < n; ++ii) {
    multiset<int>::iterator iter = s.upper_bound(movies[ii].first);
    if (iter == s.begin()) {
      continue;
    }
    --iter;
    s.erase(iter);
    s.insert(movies[ii].second);
    ++ans;
  }

  cout << ans << endl;
  return 0;
}
