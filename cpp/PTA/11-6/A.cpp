#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10001;

class BinaryTree {
private:
  struct Node {
    int data;
    int left;
    int right;
    int pa;
    Node(int val) : data(val), left(-1), right(-1), pa(-1) {}
    Node() : data(0), left(-1), right(-1), pa(-1) {}
  };
  Node nodes[MAXN];
  int poolIdx = 0;
  int newNode(int val) {
    int idx = ++poolIdx;
    nodes[idx] = Node(val);
    return idx;
  }

public:
  int root = 0;
  BinaryTree() {}

  int buildByPreorder(int idx, queue<int> &preorder) {
    if (preorder.empty())
      return -1;
    int val = preorder.front();
    preorder.pop();
    if (val == 0)
      return -1;
    else {
      nodes[idx].data = val;
      int leftIdx = newNode(0);
      nodes[idx].left = leftIdx;
      nodes[leftIdx].pa = idx;
      buildByPreorder(leftIdx, preorder);
      int rightIdx = newNode(0);
      nodes[idx].right = rightIdx;
      nodes[rightIdx].pa = idx;
      buildByPreorder(rightIdx, preorder);
      return idx;
    }
  }

  void buildPa() {
    for (int i = 0; i < poolIdx; i++) {
      int lidx = nodes[i].left;
      int ridx = nodes[i].right;
      if (lidx != -1)
        nodes[lidx].pa = i;
      if (ridx != -1)
        nodes[ridx].pa = i;
    }
  }

  void preorder(int idx) {
    if (idx == -1)
      return;
    cout << nodes[idx].data << " ";
    preorder(nodes[idx].left);
    preorder(nodes[idx].right);
  }

  void inorder(int idx) {
    if (idx == -1 || nodes[idx].data == 0)
      return;
    inorder(nodes[idx].left);
    cout << nodes[idx].data << " ";

    inorder(nodes[idx].right);
  }

  bool query(int idx, int val) {
    if (idx == -1)
      return false;
    if (nodes[idx].data == val) {
      if (nodes[idx].pa == -1)
        cout << 0 << endl;
      else
        cout << nodes[nodes[idx].pa].data << endl;
      return true;
    }
    return query(nodes[idx].left, val) || query(nodes[idx].right, val);
  }

  void deleteSubtree(int idx) {
    int lidx = nodes[idx].left;
    int ridx = nodes[idx].right;
    if (lidx != -1)
      deleteNode(lidx);
    if (ridx != -1)
      deleteNode(ridx);
    deleteNode(idx);
  }

  int getIdx(int idx, int val) {
    if (nodes[idx].data == val)
      return idx;
    int lidx = nodes[idx].left;
    int ridx = nodes[idx].right;
    if (lidx != -1)
      return getIdx(lidx, val);
    if (ridx != -1)
      return getIdx(ridx, val);
    return -1;
  }

  void deleteNode(int idx) {
    int pa = nodes[idx].pa;
    if(pa==-1) return;
    int left = nodes[pa].left;
    int right = nodes[pa].right;
    if (left == idx)
      nodes[pa].left = -1;
    if (right == idx)
      nodes[pa].right = -1;
    return;
  }
};

int main() {
  string s;
  queue<int> preorder;
  getline(cin, s);
  for (size_t i = 0; i < s.size();) {
    while (i < s.size() && s[i] == ' ')
      i++;
    if (i >= s.size())
      break;
    int num = 0;
    while (i < s.size() && isdigit(s[i])) {
      num = num * 10 + (s[i] - '0');
      i++;
    }
    preorder.push(num);
  }

  BinaryTree tree;
  tree.buildByPreorder(tree.root, preorder);
  int m,k;
  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> k;
    int idx = tree.getIdx(tree.root, k);
    if (idx == -1) {
      cout << 0 << endl;
    } else {
      tree.deleteSubtree(idx);
      tree.inorder(tree.root);
      cout << endl;
    }
  }
  return 0;
}
