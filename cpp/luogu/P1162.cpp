#include<bits/stdc++.h>
using namespace std;

int coordinate[30][30];int n;
bool shao=0;

struct node{int x,y;};

int dir[4][2]{
    {-1,0},
    {0,1},
    {1,0},
    {0,-1},
};

void bfs(int dx,int dy){
    queue<node> q;
    node start,next;
    start.x=dx;start.y=dy;
    q.push(start);
    while(!q.empty()){
        start=q.front();
        if(coordinate[start.x][start.y]==1){
            q.pop();
            continue;
        }
        for(int i=0;i<4;i++){
            next.x=start.x+dir[i][0];
            next.y=start.y+dir[i][1];
            if(next.x<0||next.x>=n||next.y<0||next.y>=n) continue;
            if(coordinate[next.x][next.y]==1||coordinate[next.x][next.y]==2||coordinate[next.x][next.y]==3) continue;
            q.push(next);
        }
        q.pop();
        coordinate[start.x][start.y]=3;
    }
    if(q.empty()){
        coordinate[dx][dy]=3;
        shao=1;
    }
    return;
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>coordinate[i][j];
        }
    } 
    for(int i=0;i<n;i++){
        if(coordinate[i][0]==0) bfs(i,0);
    }
    for(int i=0;i<n;i++){
        if(coordinate[i][n-1]==0) bfs(i,n-1);
    }
    for(int i=0;i<n;i++){
        if(coordinate[0][i]==0) bfs(0,i);
    }
    for(int i=0;i<n;i++){
        if(coordinate[n-1][i]==0) bfs(n-1,i);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(coordinate[i][j]==0) coordinate[i][j]=2;
            if(coordinate[i][j]==3) coordinate[i][j]=0;
        }
    }                     
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<coordinate[i][j]<<' ';
        }
        cout<<'\n';
    }  
    return 0;
}