#include <bits/stdc++.h>
using namespace std;

struct Train {
  int num = 0, idx = 0;
  Train(int num, int idx) : num(num), idx(idx) {}
};

class Track {
public:
  queue<Train> buf;

  Train front() const { return buf.empty() ? Train(-1, -1) : buf.front(); }
  Train back() const { return buf.empty() ? Train(-1, -1) : buf.back(); }
  void pop() {
    if (!buf.empty())
      buf.pop();
  }

  Track() {};

  void push(Train train) { buf.push(train); }

  bool empty() { return buf.empty(); }

  bool operator<(const Track &track) const {
    return this->back().num > track.back().num;
  }
};

void popbuf(vector<Track> &buf, vector<int> &out, int &want) {
  bool progress = 0;
  do {
    progress = 0;
    for (auto &track : buf) {
      Train front = track.front();
      Train back = track.back();
      if (front.num == want) {
        out.push_back(front.idx);
        want++;
        track.pop();
        progress = 1;
      }
    }

  } while (progress);
}

void solve(int n, int k, vector<int> &ori) {
  vector<Track> buf(k);
  vector<int> out;
  int want = 1;
  for (int i = 0; i < n; i++) {
    int v = ori[i];
    bool done = 0;
    bool isempty = 1;
    int max = -2;
    Track *maxtrack = nullptr;
    if (v == want) {
      out.push_back(i);
      want++;
      done = 1;
    } else {
      popbuf(buf, out, want);
      for (auto &track : buf) {
        Train front = track.front();
        Train back = track.back();
        if (front.num == want) {
          out.push_back(front.idx);
          want++;
          track.pop();
          done = 1;
        }
        if (v > back.num) {
          if (max < back.num) {
            max = back.num;
            maxtrack = &track;
          }
        }
      }
      if (maxtrack) {
        maxtrack->push(Train(v, i));
        done = 1;
      }
    }
    if (done == 0) {
      cout << "错误：任务不可能完成。" << endl;
      return;
    }
  }
  popbuf(buf, out, want);
  if (want <= n) {
    cout << "错误：任务不可能完成。" << endl;
    return;
  }
  for (auto v : out) {
    cout << v << endl;
  }
}

int main() {
  int n, k;
  cin >> n >> k;
  vector<int> ori(n);
  for (int i = 0; i < n; i++) {
    cin >> ori[i];
  }
  solve(n, k, ori);
  return 0;
}
