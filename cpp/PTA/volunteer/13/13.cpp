#include <bits/stdc++.h>
using namespace std;

class StackQueue {
public:
  stack<int> s1, s2;

  void push(int e) { s1.push(e); }

  void pop() {
    int cnt = 0;
    if (!s2.empty()) {
      cout << s2.top() << " " << ++cnt << endl;
      s2.pop();
      return;
    }
    while (!s1.empty()) {
      int cur = s1.top();
      s1.pop();
      s2.push(cur);
      cnt += 2;
    }
    if (s2.empty()) {
      cout << "ERROR" << endl;
      return;
    }
    cout << s2.top() << " ";
    s2.pop();
    cnt++;
    cout << cnt << endl;
    return;
  }
};

int main() {
  StackQueue sq;
  int n;
  cin >> n;
  char op;
  int e;
  while (n--) {
    cin >> op;
    if (op == 'I') {
      cin >> e;
      sq.push(e);
    } else {
      sq.pop();
    }
  }
  return 0;
}
