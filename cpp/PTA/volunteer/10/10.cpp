#include <bits/stdc++.h>
using namespace std;

void kadane(vector<int> &a) {
  int current_max = a[0], global_max = a[0], start = 0, end = 0, tmp_start = 0;
  int len = a.size();
  int cur;
  for (int i = 1; i < len; i++) {
    cur = a[i];
    bool iszero = 0;
    if (current_max == 0)
      iszero = 1;
    current_max = max(current_max + cur, cur);
    if (current_max == cur && !iszero)
      tmp_start = i;
    if (current_max > global_max) {
      global_max = current_max;
      start = tmp_start;
      end = i;
    }
  }
  if (global_max > 0) {
    printf("%d\n%d %d", global_max, start, end);
  } else {
    printf("0\n-1 -1");
  }
  return;
}

int main() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  kadane(a);
  return 0;
}
