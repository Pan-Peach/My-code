#include <bits/stdc++.h>
#include <string>
using namespace std;

class Txt {
private:
  string raw;
  list<char> txt;
  list<char>::iterator cursor;
  bool mode = 0;

public:
  Txt(string raw) : raw(raw) { cursor = txt.begin(); };

  void do_backspace() {
    if (cursor != txt.begin()) {
      cursor = txt.erase(prev(cursor));
    }
  }

  void put_char(char c) {
    if (!mode) {
      cursor = txt.insert(cursor, c);
      cursor++;
    } else {
      if (cursor != txt.end()) {
        *cursor = c;
        cursor++;
      } else {
        txt.push_back(c);
        cursor = txt.end();
      }
    }
  }

  void makeTxt() {
    txt.clear();
    int len = raw.size();
    for (int i = 0; i < len; i++) {
      char cur = raw[i];
      if (cur == '[')
        cursor = txt.begin();
      else if (cur == ']')
        cursor = txt.end();
      else if (cur == '{') {
        if (cursor == txt.begin())
          continue;
        cursor--;
      } else if (cur == '}') {
        if (cursor == txt.end())
          continue;
        cursor++;
      } else if (cur == '-')
        mode = !mode;
      else if (cur == '=')
        do_backspace();
      else {
        put_char(cur);
      }
    }
  }

  void output() {
    for (auto c : txt) {
      cout << c;
    }
  }
};

int main() {
  string raw;
  getline(cin, raw);
  Txt T(raw);
  T.makeTxt();
  T.output();

  return 0;
}
