#include<bits/stdc++.h>
using namespace std;

int dir[8][2]={
   {2,1},{-1,2},{-2,-1},{1,-2},{2,-1},{1,2},{-2,1},{-1,-2} 
};

struct Point
{
    int x;
    int y;
    Point(int x=0,int y=0) : x(x),y(y) {}
};

bool inboard(int n,int m,Point it){
    if(it.x>=0&&it.x<n&&it.y>=0&&it.y<m) return true;
    return false;
}

void bfs(int n,int m,int x0,int y0){
    vector<vector<int>> board(n,vector<int>(m,0));
    vector<vector<bool>> visited(n,vector<bool>(m,false));
    queue<Point> queue;
    queue.push(Point(x0,y0));
    int cnt=0,t=0;
    int rest[1000];
    memset(rest,0,sizeof rest);
    rest[0]=1;
    visited[x0][y0]=true;
    while(!queue.empty()){
        Point now=queue.front();
        queue.pop();
        if(rest[t]==0) t++;
        rest[t]--;
        for(int i=0;i<8;i++){
            int x=now.x,y=now.y;
            x+=dir[i][0];y+=dir[i][1];
            if(inboard(n,m,Point(x,y))
            &&!visited[x][y]){
                queue.push(Point(x,y));
                visited[x][y]=true;
                board[x][y]=t+1;
                rest[t+1]++;
            }
        }

    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(board[i][j]==0&&!visited[i][j]) board[i][j]=-1;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%-5d",board[i][j]);
        }
        cout<<'\n';
    }
    return;
}

int main(){

    int n,m,x,y;
    cin>>n>>m>>x>>y;
    bfs(n,m,x-1,y-1);

    return 0;

}