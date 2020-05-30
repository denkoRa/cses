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

struct Project {
  int start, end, reward;
};

int main() {
  sync_cin;

  int n; cin >> n;
  map<int, vector<int>> starts;
  map<int, vector<int>> ends;
  vector<Project> projects(n);
  vector<int> times;

  for (int ii = 0; ii < n; ++ii) {
    int a, b, p;
    cin >> a >> b >> p;
    times.push_back(a);
    times.push_back(b);
    starts[a].push_back(ii);
    ends[b].push_back(ii);
    projects[ii].reward = p;
  }

  sort(times.begin(), times.end());

  int time = 0;
  map<int, vector<int>> end_map;
  for (int ii = 0; ii < sz(times); ++ii) {
    if (ii == 0 || times[ii] > times[ii - 1]) {
      ++time;
      const vector<int>& v1 = starts[times[ii]];
      if (!v1.empty()) {
        for (int jj = 0; jj < sz(v1); ++jj) {
          const int idx = v1[jj];
          projects[idx].start = time;
        }
      }
      const vector<int>& v2 = ends[times[ii]];
      if (!v2.empty()) {
        for (int jj = 0; jj < sz(v2); ++jj) {
          const int idx = v2[jj];
          projects[idx].end = time;
          end_map[time].push_back(idx);
        }
      }
    }
  }

  vector<ll> dp(time + 1, 0LL);
  dp[0] = 0;
  for (int ii = 1; ii <= time; ++ii) {
    const vector<int>& ending_projects = end_map[ii];
    dp[ii] = dp[ii - 1];
    if (sz(ending_projects) > 0) {
      for (int jj = 0; jj < sz(ending_projects); ++jj) {
        const int idx = ending_projects[jj];
        dp[ii] = max(dp[ii], dp[projects[idx].start - 1] + projects[idx].reward);
      }
    }
  }

  cout << dp[time] << endl;
  return 0;
}
