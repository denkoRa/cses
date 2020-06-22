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
#include <cmath>

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
void compress(it start, it end, const int start_value) {
  typedef typename remove_reference<decltype(*start)>::type T;
  map<T, vector<it>> m;
  for (it ii = start; ii != end; ii++) {
    m[*ii].push_back(ii);
  }
  int t = start_value;
  for (auto& [x, v] : m) {
    for (auto& i : v) {
      *i = t;
    }
    ++t;
  }
}

//-----------------------------------------------------------------------------

struct Query {
  int left;
  int right;
  int bucket_idx;
  int idx;
  Query(int l, int r, int b, int i) : left(l), right(r), bucket_idx(b),
                                      idx(i) {
  }

  bool operator<(const Query& other) const {
    return bucket_idx < other.bucket_idx ||
           (bucket_idx == other.bucket_idx && right < other.right);
  }
};

void Remove(int num, vector<int>& freq, int *num_unique) {
  if (freq[num] == 1) {
    --(*num_unique);
  }
  --freq[num];
}

void Add(int num, vector<int>& freq, int *num_unique) {
  if (freq[num] == 0) {
    ++(*num_unique);
  }
  ++freq[num];
}

int main() {
  sync_cin;

  int n, q; cin >> n >> q;

  vector<int> x(n);
  cin >> x;

  compress(x.begin(), x.end(), 1);
  int bucket_boundary = 555;

  vector<Query> queries;
  int idx = 0;
  while (idx < q) {
    int a, b;
    cin >> a >> b;
    int bucket_idx = a / bucket_boundary;
    queries.emplace_back(--a, --b, bucket_idx, idx++);
  }

  sort(queries.begin(), queries.end());
  vector<int> res(q);
  int current_l = queries[0].left;
  int current_r = current_l;
  vector<int> freq(int(2e5 + 1), 0);
  int num_unique = 1;
  ++freq[x[queries[0].left]];

  for (auto query : queries) {
    int l = query.left, r = query.right;
    while (current_l < l) {
      Remove(x[current_l], freq, &num_unique);
      ++current_l;
    }
    while (current_l > l) {
      --current_l;
      Add(x[current_l], freq, &num_unique);
    }
    while (current_r < r) {
      ++current_r;
      Add(x[current_r], freq, &num_unique);
    }
    while (current_r > r) {
      Remove(x[current_r], freq, &num_unique);
      --current_r;
    }
    res[query.idx] = num_unique;
  }

  cout << res;
  return 0;
}
