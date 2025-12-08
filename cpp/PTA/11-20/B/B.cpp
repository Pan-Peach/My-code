#include <bits/stdc++.h>
using namespace std;

struct State {
  int x, y, time, used;

  State(int x, int y, int time, int used)
      : x(x), y(y), time(time), used(used) {}
};

const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

bool isin(int x, int y, int n, int m) {
  return x >= 0 && x < n && y >= 0 && y < m;
}

void bfs(vector<vector<int>> &g, int T, int sx, int sy, int tx, int ty) {
  vector<vector<vector<int>>> vis(
      g.size(),
      vector<vector<int>>(g[0].size(),
                          vector<int>(2, 0))); // vis[x][y][used] 初始为 0
  vis[sx][sy][0] = 1;
  int n = g.size();
  int m = g[0].size();
  queue<State> q;
  q.push(State(sx, sy, 0, 0));
  while (!q.empty()) {
    State s = q.front();
    q.pop();
    int x = s.x, y = s.y;
    if (x == tx && y == ty) {
      cout << s.time-T+1 << endl;
      return;
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] != 1 &&
          !vis[nx][ny][s.used]) {
        q.push(State(nx, ny, s.time + 1, s.used));
        vis[nx][ny][s.used] = 1;
      }
    }

    // if (!s.used) {
    //   for (int i = 0; i < 4; i++) {
    //     bool able = 1;
    //     int nx = x, ny = y;
    //     nx+= dx[i];
    //     ny+= dy[i];
    //     if(isin(nx,ny,n,m)==0 || g[nx][ny]==1) continue;
    //     for (int j = 1; j < T; j++) {
    //       nx += dx[i];
    //       ny += dy[i];
    //       if (!(nx >= 0 && nx < n && ny >= 0 && ny < m)) break;
    //       if (g[nx][ny] == 1 || vis[nx][ny][s.used]) {
    //         able = 0;
    //         break;
    //       }
    //       if (able) {
    //         q.push(State(nx, ny, s.time + 1, 1));
    //         vis[nx][ny][1] = 1;
    //       }
    //     }
    //   }
    // }
  }

  cout << "can not save" << endl;
  return;
}

int main() {
  int n, m, T, sx, sy, tx, ty;
  while (cin >> n >> m >> T) {
    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> g[i][j];
        if (g[i][j] == 3) {
          sx = i;
          sy = j;
        } else if (g[i][j] == 4) {
          tx = i;
          ty = j;
        }
      }
    }

    bfs(g, T, sx, sy, tx, ty);
  }
  return 0;
}
