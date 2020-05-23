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
const int N = 7;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
 
//                D   U   L   R
const int di[] = {1, -1,  0,  0};
const int dj[] = {0,  0, -1,  1};
const map<char, int> dc = {{'D', 0}, {'U', 1}, {'L', 2}, {'R', 3}};
 
bool visited[N][N];
 
bool valid(int ii, int jj) {
  if ((ii == 0 || visited[ii - 1][jj]) &&
      (ii == N - 1 || visited[ii + 1][jj])) {
 
    if (jj > 0 && jj < N - 1 && !visited[ii][jj - 1] && !visited[ii][jj + 1]) {
      return false;
    }
  }
 
  if ((jj == 0 || visited[ii][jj - 1]) &&
      (jj == N - 1 || visited[ii][jj + 1])) {
 
    if (ii > 0 && ii < N - 1 && !visited[ii + 1][jj] && !visited[ii - 1][jj]) {
      return false;
    }
  }
  return true;
}
 
void calc_new_coords(int *ii, int *jj, int index) {
  int move_i = di[index];
  int move_j = dj[index];
  *ii = move_i + *ii;
  *jj = move_j + *jj;
}

ll solve(int ii, int jj, int index, const string& path) {
  if (index == N * N - 1) {
    return 1LL;
  }
 
  if (visited[N - 1][0]) {
    return 0;
  }
  
  // Cut the cases where we hit the wall while having free squares on two
  // sides.
  if (!valid(ii, jj)) {
    return 0;
  }
  
  ll ret = 0LL;
  if (path[index] == '?') {
    for (int kk = 0; kk < 4; ++kk) {
      int new_i = ii, new_j = jj;
      calc_new_coords(&new_i, &new_j, kk);
      if (new_i < 0 || new_i >= N || new_j < 0 || new_j >= N) {
        continue;
      }
      if (!visited[new_i][new_j]) {
        visited[new_i][new_j] = true;
        ret += solve(new_i, new_j, index + 1, path);
        visited[new_i][new_j] = false;
      }
    }
  } else {
    int ind = dc.find(path[index])->second;
    int new_i = ii, new_j = jj;
    calc_new_coords(&new_i, &new_j, ind);
    if (new_i < 0 || new_i >= N || new_j < 0 || new_j >= N) {
      return 0;
    }
    if (visited[new_i][new_j]) {
      return 0;
    }
    visited[new_i][new_j] = true;
    ret += solve(new_i, new_j, index + 1, path);
    visited[new_i][new_j] = false;
  }
 
  return ret;
}
 
int main() {
  sync_cin;
 
  string s; cin >> s;
  visited[0][0] = true;
  cout << solve(0, 0, 0, s) << endl;
  return 0;
}