#include<bits/stdc++.h>
using namespace std;

void Tarjan(int u, int &time, vector<vector<int>>& g, vector<int>& dfn, vector<int>& low, stack<int>& s, vector<int>& inStack, int& ans){
    dfn[u]=low[u]=++time;
    s.push(u);
    inStack[u]=1;
    for(auto v:g[u]){
        if(!dfn[v]){
            Tarjan(v,time,g,dfn,low,s,inStack,ans);
            low[u]=min(low[u],low[v]);
        }
        else if(inStack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        int cnt=0;
        while(true){
            cnt++;
            int x=s.top();
            s.pop();
            inStack[x]=0;
            low[x]=INT_MAX;
            if(x==u){
                if(cnt>1) ans++;
                break;
            }
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> g(n+1);
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
    }
    vector<int> dfn(n+1),low(n+1), inStack(n+1);
    stack<int> s;
    int time=0,ans=0;
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            Tarjan(i,time,g,dfn,low,s,inStack,ans);
        }
    }
    cout<<ans<<endl;
    return 0;
}