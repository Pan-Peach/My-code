#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+7;


class Node{
    public:
    int v,len;
    Node(int v,int len):v(v),len(len){}

    bool operator<(const Node& other) const {
        return len > other.len;
    }
};

void Dijkstra(vector<vector<Node>>& g,int s){
    vector<int> dist(g.size(),INF);
    vector<int> pre(g.size(),-1);
    vector<vector<int>> path(g.size());
    path[s].push_back(s);
    dist[s]=0;
    priority_queue<Node> pq;
    pq.push(Node(s,0));

    while(!pq.empty()){
        Node curr=pq.top();
        pq.pop();
        int u=curr.v;
        if(curr.len>dist[u]) continue;
        for(auto& neighbor:g[u]){
            int v=neighbor.v;
            int len=neighbor.len;
            if(dist[u]+len<dist[v]){
                dist[v]=dist[u]+len;
                path[v]=path[u];
                path[v].push_back(v); 
                pq.push(Node(v,dist[v]));
            }
            else if(dist[u]+len==dist[v]){
                vector<int> newpath=path[u];
                newpath.push_back(v);
                if(newpath.size()<path[v].size()){
                    path[v]=newpath;
                }
                else if(newpath.size()==path[v].size() && newpath<path[v]){
                    path[v]=newpath;
                }
            }
        }
    }

    for(int i=1;i<g.size();i++){
        vector<int> p = path[i];
//        p.push_back(i); 
        if(p.size()){
            for(int i=0;i<p.size();i++){
                if(i) cout<<"->";
                cout<<p[i];
            }
            cout<<endl;
        }
    }
     
}

int main(){
    int n,e;
    cin>>n>>e;
    vector<vector<Node>> g(n);
    for(int i=0;i<e;i++){
        int a,b,len;
        cin>>a>>b>>len;
        g[a].push_back(Node(b,len));
    }
    Dijkstra(g,0);
    return 0;
}