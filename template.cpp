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
#include <bitset>

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

template<typename T>
inline ostream& operator<<(ostream& os, vector<T>& v) {
  for (int ii = 0; ii < sz(v); ++ii) {
    os << v[ii] << " ";
  }
  return os;
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

template<typename it>
void compress(it start, it end) {
  typedef typename remove_reference<decltype(*start)>::type T;
  map<T, vector<it>> m;
  for (it ii = start; ii != end; ii++) {
    m[*ii].push_back(ii);
  }
  int t = 0;
  for (auto& [x, v] : m) {
    for (auto& i : v) {
      *i = t;
    }
    ++t;
  }
}

//-----------------------------------------------------------------------------

int main() {
  sync_cin;
  return 0;
}
