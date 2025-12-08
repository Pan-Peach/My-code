#include <bits/stdc++.h>
using namespace std;

class Node {
public:
  int u, val;

  Node(int u, int v) : u(u), val(v) {};

  bool operator<(const Node &other) const { return u < other.u; }
};

void output(vector<Node> &g, int i) {
  cout << i << ':';
  for (auto n : g) {
    int u, v;
    u = n.u;
    v = n.val;
    cout << '(' << i << ',' << u << ',' << v << ')';
  }
  cout << endl;
  return;
}

int main() {
  int n, e;
  cin >> n >> e;
  vector<vector<Node>> g(n + 1);
  for (int i = 0; i < e; i++) {
    int f, t, v;
    cin >> f >> t >> v;
    g[f].push_back(Node(t, v));
  }
  for (int i = 0; i < n; i++) {
    if (g[i].size()) {
      output(g[i], i);
    }
  }
  return 0;
}
