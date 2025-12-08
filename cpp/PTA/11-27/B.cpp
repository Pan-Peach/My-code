#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+7;

struct Edge{
    int to,len;
    Edge(int to,int len):to(to),len(len){}
};

void KeyPath(vector<vector<Edge>>& g,vector<int>& indeg){
    int n=g.size()-1;
    vector<int> ve(n+1,0);
    vector<int> vl(n+1,INF);
    int s,e;
    for(int i=1;i<=n;i++){
        if(indeg[i]==0){
            s=i;
            break;
        }
    }
    ve[s]=0;

    queue<int> q;
    q.push(s);
    vector<int> topo;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        topo.push_back(u);
        for(auto& edge:g[u]){
            int v=edge.to;
            indeg[v]--;
            if(indeg[v]==0){
                q.push(v);
            }
        }
        for(auto& edge:g[u]){
            int v=edge.to;
            int len=edge.len;
            if(ve[u]+len>ve[v]){
                ve[v]=ve[u]+len;
            }
        }
    }
    if(topo.size()<n){
        cout<<"unworkable project"<<endl;
        return;
    }
    e=topo.back();
    vl[e]=ve[e];
    //计算vl
    for(int i=topo.size()-1;i>=0;i--){
        int u=topo[i];
        for(auto& edge:g[u]){
            int v=edge.to;
            int len=edge.len;
            if(vl[v]-len<vl[u]){
                vl[u]=vl[v]-len;
            }
        }
    }

    cout<<ve[e]<<endl;
    //输出关键路径
    for(int u=1;u<=n;u++){
        for(auto& edge:g[u]){
            int v=edge.to;
            int len=edge.len;
            if(ve[u]==vl[v]-len){
                cout<<u<<"->"<<v<<endl;
            }
        }
    }
    return;
}

int main(){
    int n,e;
    while(cin>>n>>e){
        vector<vector<Edge>> g(n+1);
        vector<int> indeg(n+1,0);
        for(int i=1;i<=e;i++){
            int u,v,len;
            cin>>u>>v>>len;
            g[u].push_back(Edge(v,len));
            indeg[v]++;
        }
        KeyPath(g,indeg);
    }
    
    return 0;
}