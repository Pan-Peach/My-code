#include <bits/stdc++.h>
using namespace std;

void buildNext(string s, vector<int> &next) {
  int n = s.size();
  int k = -1;
  next[0] = -1;
  for (int i = 0; i < n; i++) {
    while (k >= 0 && s[k] != s[i])
      k = next[k];
    next[i + 1] = ++k;
  }
  return;
}

int main() {
  string s;
  cin >> s;
  int n = s.size();
  vector<int> next(n + 1, 0);
  buildNext(s, next);
  int len = next[next[n]];
  if (len < 0)
    len = 0;
  int ans = s.size() - 2 * len;
  if (ans < 0)
    ans = 0;
  cout << ans;
  return 0;
}
