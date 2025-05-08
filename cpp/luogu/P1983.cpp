
#include<bits/stdc++.h>
using namespace std;



int tpsort(vector<vector<int>> &graph,vector<bool> visited,vector<int>& in_degree
,vector<int>& out_degree,int n,int orin){
    queue<int> q;
    vector<int> dp(in_degree.size(),0);
    vector<bool> vis(n+1,false);
    for(int i=1;i<=n;i++){
        if(in_degree[i]==0){
            q.push(i);
            vis[i]=true;
            if(i<=orin) dp[i]=1;
        }
    }

    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<graph[u].size();i++){
            int v=graph[u][i];
            if(vis[v]){
                continue;
            }
            if(v<=orin){
                dp[v]=max(dp[v],dp[u]+1);
            }
            else{
                dp[v]=max(dp[v],dp[u]);
            }   
            in_degree[v]--;
            if(in_degree[v]==0){
                q.push(v);
                vis[v]=true;
            }
        }
    }
    int maxn=0;
    for(int i=1;i<=orin;i++){
        maxn=max(maxn,dp[i]);
    }
    return maxn;
}

int main(){
    int n,m,orin;
    cin>>n>>m;
    orin=n;
    vector<vector<int>> graph(n+1);
    vector<int> in_degree(n+1,0);
    vector<int> out_degree(n+1,0);
    vector<bool> vis(n+1,false);

    for(int i=0;i<m;i++){
        int s,first,end;
        cin>>s;
        for(int j=1;j<=s;j++){
            int a;
            cin>>a;
            if(j==1){
                first=a;
            }
            if(j==s){
                end=a;
            }
            vis[a]=true;
        }
        graph.push_back(vector<int>());
        in_degree.push_back(0);
        out_degree.push_back(0);
        n++;
        for(int k=first;k<=end;k++){
            if(vis[k]){
                graph[n].push_back(k);
                in_degree[k]++;
                out_degree[n]++;
                vis[k]=false;
            }
            else{
                graph[k].push_back(n);
                in_degree[n]++;
                out_degree[k]++;
            }
        }
    }

    int ans=tpsort(graph,vis,in_degree,out_degree,n,orin);
    cout<<ans<<endl;

    return 0;
}