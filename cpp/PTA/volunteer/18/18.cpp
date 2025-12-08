#include <bits/stdc++.h>
using namespace std;

struct Node {
  int r, c, v;
  bool operator<(const Node &b) const {
    if (r != b.r)
      return r < b.r;
    return c < b.c;
  }
  bool operator==(const Node &b) const { return r == b.r && c == b.c; }
};

int main() {
  int m, n;
  cin >> m >> n;
  vector<Node> a(m), b(n);
  for (int i = 0; i < m; i++)
    cin >> a[i].r >> a[i].c >> a[i].v;
  for (int i = 0; i < n; i++)
    cin >> b[i].r >> b[i].c >> b[i].v;

  vector<Node> c;
  c.reserve(m + n);
  for (auto v : a)
    c.push_back(v);
  for (auto v : b) {
    c.push_back(v);
  }
  sort(c.begin(), c.end());

  vector<Node> out;
  int pos = -1;
  out.reserve(m + n);
  for (auto v : c) {
    if (pos == -1) {
      out.push_back(v);
      pos++;
    } else {
      if (v == out[pos])
        out[pos].v += v.v;
      else {
        out.push_back(v);
        pos++;
      }
    }
  }

  for (auto &u : out)
    if (u.v != 0)
      cout << u.r << ' ' << u.c << ' ' << u.v << endl;

  return 0;
}
