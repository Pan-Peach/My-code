#include<bits/stdc++.h>
using namespace std;
const int MOD = 80112002;

int tpsort(vector<vector<int>>& adj, vector<int>& indeg, vector<int>& outdeg, vector<int>& dp){
    queue<int> q;
    for(int i=1;i<indeg.size();i++){
        if(indeg[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v:adj[u]){
            dp[v] = (dp[v]+dp[u])%MOD;
            indeg[v]--;
            if(indeg[v] == 0){
                q.push(v);
            }
        }
    }
    int ans=0;
    for(int i=1;i<outdeg.size();i++){
        if(outdeg[i] == 0){
             ans+=dp[i];
             ans%=MOD;
        }
    }
    return ans;
}

int main(){
    int n,m,a,b;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    vector<int> indeg(n+1);
    vector<int> outdeg(n+1);
    vector<int> dp(n+1);
    dp.assign(n+1,0);  

    for(int i=0;i<m;i++){
        cin>>a>>b;
        adj[a].push_back(b);
        indeg[b]++;
        outdeg[a]++;
    }
    for(int i=1;i<=n;i++){
        if(indeg[i] == 0){
            dp[i] = 1;
        }
    }
    cout<<tpsort(adj,indeg,outdeg,dp)<<endl;
    return 0;
}