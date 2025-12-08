#include <bits/stdc++.h>
using namespace std;

void setMins(vector<int> a, unordered_set<int> b) {
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < a.size(); i++) {
    if (b.find(a[i]) == b.end())
      pq.push(a[i]);
  }
  while (!pq.empty()) {
    int c = pq.top();
    cout << c << ' ';
    pq.pop();
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  unordered_set<int> b;
  for (int i = 0; i < m; i++) {
    int tmp;
    cin >> tmp;
    b.insert(tmp);
  }
  setMins(a, b);

  return 0;
}
