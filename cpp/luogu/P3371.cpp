#include<bits/stdc++.h>
using namespace std;
const int INF=pow(2,31)-1;

struct Point{
    int name;
    int dis;
    Point(int na,int di){
        name=na;
        dis=di;
    }
    Point(){
        name=0;dis=0;
    }

    inline bool operator < (const Point& p) const
    {
        return dis>p.dis;
    }
};

void dijkstra(int n, int str,vector<vector<pair<int,int>> >& adj){
    priority_queue<Point> pq;
    pq.push(Point(str,0));
    vector<int> dis(n+1,INF);
    dis[str]=0;
    vector<bool> flag(n+1,false);

    while(!pq.empty()){
        int u=pq.top().name;
        pq.pop();
        if(flag[u]) continue;
        flag[u]=true;
        for(auto edge:adj[u]){
            int v=edge.first,w=edge.second;
            if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                pq.push(Point(v,dis[v]));
            }
        }

    }
    for(int i=1;i<dis.size();i++){
        if(i>1) cout<<' ';
        cout<<dis[i];
    }
    return;
}

int main(){
    int n,m,s,u,v,w;
    cin>>n>>m>>s;
    vector< vector<pair<int,int>> > adj(n+1);
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }

    dijkstra(n,s,adj);
    return 0;
}