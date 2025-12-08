#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void err_invalid() { cout << "错误：表达式不规范。" << endl; }

void err_divide() { cout << "错误：除法操作分母为零。" << endl; }

void err_mod() { cout << "错误：取模操作除数为零。" << endl; }

void err_wresult() { cout << "1000000000" << endl; }

void solve(string &raw) {
  stringstream ss(raw);
  stack<ll> st;
  string tok;

  while (ss >> tok) {
    if (isdigit(tok[0]) || tok.size() > 1 && isdigit(tok[1]))
      st.push(stoll(tok));
    else {
      if (st.size() < 2) {
        err_invalid();
        return;
      }
      ll r;
      ll b = st.top();
      st.pop();
      ll a = st.top();
      st.pop();
      switch (tok[0]) {
      case '+':
        r = a + b;
        break;
      case '-':
        r = a - b;
        break;
      case '*':
        r = a * b;
        break;
      case '/':
        if (b == 0) {
          err_divide();
          err_wresult();
          return;
        } else {
          r = a / b;
          break;
        }
      case '%':
        if (b == 0) {
          err_mod();
          err_wresult();
          return;
        } else {
          r = a % b;
          break;
        }
      }
      st.push(r);
    }
  }
  if (st.size() > 1 || st.empty()) {
    err_invalid();
    err_wresult();
    return;
  } else {
    cout << st.top() << endl;
  }
  return;
}

int main() {
  string raw;
  getline(cin, raw);
  solve(raw);
  return 0;
}
