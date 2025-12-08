#include <bits/stdc++.h>
using namespace std;

void solve(string raw) {
  int l = 0, r = 0;
  stack<char> st;
  for (int i = 0; i < raw.size(); i++) {
    char c = raw[i];
    if (c == '(')
      st.push(c);
    else {
      if (st.empty()) {
        l++;
      } else {
        st.pop();
      }
    }
  }
  if (!st.empty()) {
    r = st.size();
  }
  if (r + l > 0) {
    cout << r + l << endl;
    while (l--)
      cout << '(';
    cout << raw;
    while (r--)
      cout << ')';
    cout << endl;
  } else
    cout << "Match" << endl;
}

int main() {
  string s;
  while (getline(cin, s)) {
    solve(s);
  }
  return 0;
}
