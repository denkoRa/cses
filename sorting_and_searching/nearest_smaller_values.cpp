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
#include <stack>

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
typedef pair<int, int> ii;

//-----------------------------------------------------------------------------

int main() {
  sync_cin;

  int n; cin >> n;
  stack<ii> st;
  for (int ii = 0; ii < n; ++ii) {
    int x; cin >> x;
    while (!st.empty() && st.top().first >= x) {
      st.pop();
    }
    if (st.empty()) {
      cout << 0 << " ";
    } else {
      cout << st.top().second << " ";
    }
    st.push(make_pair(x, ii + 1));
  }

  cout << endl;
  return 0;
}
