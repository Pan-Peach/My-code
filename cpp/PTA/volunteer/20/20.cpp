#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  int n;
  cin >> T;
  while (T--) {
    queue<int> q;
    cin >> n;
    string op;
    int num;
    while (n--) {
      cin >> op;
      if (op == "ENQUEUE") {
        cin >> num;
        q.push(num);
      } else if (op == "DEQUEUE") {
        if (!q.empty())
          q.pop();
      } else if (op == "REVERSE") {
        int len = q.size();
        int x;
        for (int i = 0; i < len; i++) {
          x = q.front();
          q.pop();
          q.push(-x);
        }
      } else if (op == "MAXIMUM") {
        if (q.empty())
          continue;
        int len = q.size();
        int x, maxn = -1000000;
        for (int i = 0; i < len; i++) {
          x = q.front();
          q.pop();
          maxn = max(maxn, x);
          q.push(x);
        }
        cout << maxn << endl;
      }
    }
    if (n != 0)
      cout << endl;
  }
}
