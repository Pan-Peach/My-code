#include<bits/stdc++.h>
using namespace std;

int n,ans,num;int a[10][10];
bool visit[10][10];

inline void dfs(int x,int y,int time){
    for(int i=x;i<=n;i++){
        for(int j=y;j<=n;j++){
            if(i==x&&j==y) continue;
            if(a[i][j]&&!visit[i][j]){
                num+=a[i][j];
                visit[i][j]=1;
                dfs(i,j,time);
                visit[i][j]=0;
                num-=a[i][j];
            }
        }
    }
    if(time==1) dfs(1,1,2);
    if(time==2){
        ans=max(ans,num);
        return;
    }
}

int main(){
    cin>>n;
    int x,y,tmp;
    for(int i=0;i<100;i++){
        cin>>x>>y>>tmp;
        a[x][y]=tmp;
        if(x==0&&y==0) break;
    }
    dfs(1,1,1);
    ans+=a[1][1];
    cout<<ans;
    return 0;
}