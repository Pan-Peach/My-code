#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;

void Floyd(vector<vector<int>>& adj){
    int n=adj.size()-1;
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                adj[i][j]=min(adj[i][j],max(adj[i][k],adj[k][j]));
            }
        }
    }
    return;
}

int main(){
    int n,m,t;
    cin>>n>>m>>t;
    vector<vector<int>> adj(n+1,vector<int>(n+1,INF));
    for(int i=1;i<=n;i++){
        adj[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a][b]=c;
    }
    Floyd(adj);
    for(int i=1;i<=t;i++){
        int a,b;
        cin>>a>>b;
        if(adj[a][b]==INF){
            cout<<"-1"<<endl;
        }else{
            cout<<adj[a][b]<<endl;
        }
    }
    return 0;
}