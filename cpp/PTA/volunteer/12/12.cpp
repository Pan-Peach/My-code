#include <bits/stdc++.h>
using namespace std;

int main() {
  string line;
  getline(cin, line);
  stringstream ss(line);
  string tok, a, b;
  ss >> a;
  ss >> b;
  ss >> tok;
  cout << '(' << a << ')' << tok << '(' << b << ')' << endl;
  return 0;
}
