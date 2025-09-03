#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;

class point{
    public:
    int x,y;
    point(int x,int y):x(x),y(y){}
    point ():x(0),y(0){}
};

class base:public point{
    public:
    int r,t;
    base(int x,int y,int r,int t):point(x,y),r(r),t(t){}
    base():point(),r(0),t(0){}

    bool cover(point &p){
        if(abs(x-p.x)<=r&&abs(y-p.y)<=r) return 1;
        return 0;
    }
};

class edge{
    public:
    int v,w;
    edge(int v,int w):v(v),w(w){}
    edge():v(0),w(0){}

    bool operator<(const edge &e)const{
        return w>e.w;
    }
};

int Dijkstra(vector<vector<edge>>& graph,int s,int t){
    vector<int> dis(graph.size(),INF);
    dis[s]=0;
    priority_queue<edge> pq;
    vector<bool> vis(graph.size(),0);
    pq.push(edge(s,0));
    while(!pq.empty()){
        edge e=pq.top();
        pq.pop();
        if(vis[e.v]) continue;
        vis[e.v]=1;
        for(auto i:graph[e.v]){
            if(dis[e.v]+i.w<dis[i.v]){
                dis[i.v]=dis[e.v]+i.w;
                pq.push(edge(i.v,dis[i.v]));
            }
        }
    }
   
    return dis[t];
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<point> p(n+1);
    vector<vector<edge>> graph(n+m+1);
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    vector<base> b(m+1);
    for(int i=1;i<=m;i++){
        cin>>b[i].x>>b[i].y>>b[i].r>>b[i].t;
        for(int j=1;j<=n;j++){
            if(b[i].cover(p[j])){
                graph[j].push_back(edge(n+i,b[i].t));
                graph[i+n].push_back(edge(j,b[i].t));
            }
        }
    }
    
    int ans=Dijkstra(graph,1,n);
    if(ans==INF){
        cout<<"Nan";
    }else{
        cout<<ans/2;
    }
    return 0;
}