#include <bits/stdc++.h>
using namespace std;

void judge(int m, string &s) {
  int num = 0;
  for (int i = 0; i < s.length(); i++) {
    char cur = s[i];
    if (cur == 'S')
      num++;
    else if (cur == 'X')
      if (num >= 1)
        num--;
      else {
        cout << "NO" << endl;
        return;
      }
    if (num > m) {
      cout << "NO" << endl;
      return;
    }
  }
  if (num != 0)
    cout << "NO" << endl;
  else
    cout << "YES" << endl;
  return;
}

int main() {
  int n, m;
  cin >> n >> m;
  string s;
  for (int i = 0; i < n; i++) {
    cin >> s;
    judge(m, s);
  }
  return 0;
}
