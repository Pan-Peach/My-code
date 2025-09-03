#include<bits/stdc++.h>
using namespace std;

class DSU{
    public:
    vector<int> pa;
    DSU(int n){
        pa.resize(n+1);
        for(int i=0;i<=n;i++){
            pa[i]=i;
        }
    }
    int find(int x){
        if(pa[x] != x) pa[x] = find(pa[x]);
        return pa[x];
    }
    void unite(int x,int y){
        x=find(x);
        y=find(y);
        if(x!=y){
            pa[x]=y;
        }
        return;
    }
    bool united(){
        int root=find(1);
        for(int i=2;i<pa.size();i++){
            if(find(i)!=root){
                return false;
            }
        }
        return true;
    }
};

class Edge{
    public:
    int x,y,t;
    Edge(int x,int y,int t):x(x),y(y),t(t){}
    bool operator < (const Edge &e) const{
        return t>e.t;
    }
};

int main(){
    int n,m,cnt=0;
    cin>>n>>m;
    DSU dsu(n);
    priority_queue<Edge> edges;
    for(int i=0;i<m;i++){
        int x,y,t;
        cin>>x>>y>>t;
        edges.push(Edge(x,y,t));
    }
    int ans=0;
    while(!edges.empty()){
        Edge edge=edges.top();
        edges.pop();
        if(dsu.find(edge.x)!=dsu.find(edge.y)){
            dsu.unite(edge.x,edge.y);
            ans=edge.t;
            cnt++;
        }
        if(cnt==n-1){
            break;
        }
    }
    if(!dsu.united()){
        cout<<-1<<endl;
        return 0;
    }
    cout<<ans<<endl;
    return 0;
}