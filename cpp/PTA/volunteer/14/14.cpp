#include <bits/stdc++.h>
using namespace std;

class Dlist {
private:
  struct Node {
    int val;
    Node *pre, *suc;

    Node() : val(0), pre(nullptr), suc(nullptr) {}
    Node(int v, Node *pre, Node *suc) : val(v), pre(pre), suc(suc) {}
  };

public:
  Node *head = nullptr;
  Node *tail = nullptr;

  Dlist(int n) {
    head = new Node();
    tail = head;
    head->pre = head;
    head->suc = head;
    for (int i = 1; i <= n; i++) {
      push_back(i);
    }
  }

  void push_back(int v) {
    if (!head)
      return;
    Node *cur = new Node(v, tail, head);
    head->pre = cur;
    tail->suc = cur;
    tail = cur;
  }

  void remove(Node *cur) {
    if (cur == head)
      return;
    Node *pre = cur->pre, *suc = cur->suc;
    pre->suc = suc;
    suc->pre = pre;
    delete cur;
  }

  void ysf(int m, int k) {
    Node *cur = head->suc;
    while (head->suc != head) {
      for (int i = 1; i < m; i++) {
        cur = cur->pre;
        if (cur == head)
          cur = cur->pre;
      }
      if (cur == head)
        break;
      cout << cur->val << ' ';
      cur = cur->pre;
      if (cur->suc == head)
        remove(cur->suc->suc);
      else
        remove(cur->suc);
      for (int i = 1; i < k; i++) {
        cur = cur->suc;
        if (cur == head)
          cur = cur->suc;
      }
      if (cur == head)
        break;
      cout << cur->val << ' ';
      cur = cur->suc;
      if (cur->pre == head)
        remove(cur->pre->pre);
      else
        remove(cur->pre);
    }
    return;
  }
  void ysf2(int m) {
    Node *cur = head->suc;
    while (head->suc != head) {
      for (int i = 1; i < m; i++) {
        cur = cur->suc;
        if (cur == head)
          cur = cur->suc;
      }
      cout << cur->val << ' ';
      cur = cur->suc;
      remove(cur->pre);
      if (cur == head)
        cur = cur->suc;
      m++;
    }
  }
};

int main() {
  int n, m, k;
  cin >> n >> m;
  Dlist dl(n);
  dl.ysf2(m);
  return 0;
}
