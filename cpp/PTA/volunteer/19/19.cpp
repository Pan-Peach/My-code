#include <bits/stdc++.h>
using namespace std;

int prio(char c) {

  if (c == '*' || c == '/')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return 0;
}

bool isUnaryOp(string &s, int pos) {
  if (pos == 0)
    return true;
  else {
    char prev = s[pos - 1];
    if (prev == '(' || prio(prev))
      return true;
  }
  return false;
}

// bool isUnaryAdd(string &s, int pos) {}

void solve(string s) {

  string tmp;
  stack<char> st;
  for (int i = 0; i < s.size(); i++) {
    char cur = s[i];
    if (isdigit(cur) || cur == '.') {
      tmp.push_back(cur);
    } else if (cur == '@')
      tmp.push_back('-');
    else if (cur == '#')
      tmp.push_back('+');
    else {
      if (tmp.size())
        cout << tmp << ' ';
      tmp.clear();
      if (cur == '(') {
        st.push(cur);
        continue;
      } else if (cur == ')') {
        while (st.top() != '(') {
          cout << st.top() << ' ';
          st.pop();
        }
        st.pop();
        continue;
      }
      bool pushed = 0;
      while (!st.empty()) {
        if (prio(cur) > prio(st.top())) {
          st.push(cur);
          pushed = 1;
          break;
        } else {
          cout << st.top() << ' ';
          st.pop();
        }
      }
      if (!pushed)
        st.push(cur);
    }
  }
  if (tmp.size())
    cout << tmp << ' ';
  while (st.size() > 1) {
    cout << st.top() << ' ';
    st.pop();
  }
  cout << st.top();
  return;
}

int main() {
  string s;
  cin >> s;
  bool isnum = 1;
  for (int i = 1; i < s.size(); i++) {
    if (!isdigit(s[i])) {
      isnum = 0;
      break;
    }
  }
  if (isnum) {
    cout << s;
    return 0;
  }
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '-' && isUnaryOp(s, i))
      s[i] = '@';
    else if (s[i] == '+' && isUnaryOp(s, i))
      s[i] = '#';
  }
  solve(s);
  return 0;
}
