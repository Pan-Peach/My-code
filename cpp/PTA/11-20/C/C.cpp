#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> &g, int n, vector<bool> &vis) {
  if (!vis[n])
    cout << n << ' ';
  vis[n] = 1;
  for (auto v : g[n]) {
    if (!vis[v])
      dfs(g, v, vis);
  }
  return;
}

int main() {
  int n, e;
  cin >> n >> e;
  vector<vector<int>> g(n);
  vector<bool> vis(n, 0);
  for (int i = 0; i < e; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
  }
  for (auto &nl : g) {
    sort(nl.begin(), nl.end());
  }
  for (int i = 0; i < n; i++)
    dfs(g, i, vis);
  return 0;
}
