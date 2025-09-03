#include<bits/stdc++.h>
using namespace std;

class DSU{
    public:
    vector<int> parent;
    DSU(int n){
        parent.resize(n+1);
        for(int i=0;i<=n;i++){
            parent[i] = i;
        }
    }
    int find(int x){
        if(parent[x]!=x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void unite(int x,int y){
        if(x>=y){
            parent[y] = x;
        }
        else{
            parent[x] = y;
        }
    }
    bool same(int x,int y){
        return find(x)==find(y);
    }

};


void dfs(vector<vector<int>> &G, vector<bool> &flag, int u,int max,DSU &dsu,int last){
    if(flag[u]) return;
    flag[u] = true;
    if(u<=max){
        dsu.unite(dsu.find(u),dsu.find(max));
    }
    for(int i=0;i<G[u].size();i++){
        if(!flag[G[u][i]]){
            dfs(G,flag,G[u][i],max,dsu,u);
        }
    }
}

int main(){
    int n,m,u,v;
    cin>>n>>m;
    DSU dsu(n);
    vector<vector<int>> G(n+1);
    for(int i=0;i<m;i++){
        cin>>u>>v;
        G[v].push_back(u);
    }
    vector<bool> flag(n+1,0);
    for(int i=n;i>=1;i--){
        if(!flag[i]){
            dfs(G,flag,i,i,dsu,i);
        }
    }
    for(int i=1;i<=n;i++){
        cout<<dsu.find(i)<<" ";
    }   
    return 0;
}