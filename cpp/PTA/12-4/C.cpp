#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+7;

struct Edge{
    int  from,to,len;
    Edge(int from,int to,int len):from(from),to(to),len(len){}

    bool operator<(const Edge& other) const {
        return len < other.len;
    }
    
};

class UnionSet{
    private:
        vector<int> parent;

    public:
        UnionSet(int n){
            parent.resize(n+1);
            for(int i=0;i<=n;i++){
                parent[i]=i;
            }
        }

        int Find(int x){
            if(parent[x]!=x){
                parent[x]=Find(parent[x]);
            }
            return parent[x];
        }

        void Merge(int x,int y){
            int fx=Find(x);
            int fy=Find(y);
            if(fx!=fy){
                parent[fx]=fy;
            }
        }
};

void Kruskal(int n,vector<Edge>& edges){
    int cnt=0;
    sort(edges.begin(),edges.end());
    UnionSet us(n);
    int cost=0;
    for(auto& edge:edges){
        if(cnt==n) break;
        int u=edge.from;
        int v=edge.to;
        int len=edge.len;
        if(us.Find(u)!=us.Find(v)){
            us.Merge(u,v);
            cost+=len;
            cnt++;
        }
    }
    cout<<cost<<endl;
    return;
}

void Prim(vector<vector<int>>& g){
    int n=g.size();
    vector<bool> vis(n,false);
    vector<int> dist(n,INF);
    dist[0]=0;
    vis[0]=true;
    int cost=0;
    for(int i=1;i<n;i++){
        dist[i]=g[0][i];
    }
    for(int i=1;i<n;i++){
        int minn=INF;
        int idx=-1;
        for(int j=0;j<n;j++){
            if(!vis[j] && dist[j]<minn){
                minn=dist[j];
                idx=j;
            }
        }
        vis[idx]=true;
        cost+=minn;
        for(int j=0;j<n;j++){
            if(!vis[j] && g[idx][j]<dist[j]){
                dist[j]=g[idx][j];
            }
        }
    }

    cout<<cost<<endl;
}

int main(){
    int n,e;
    cin>>n>>e;
    vector<vector<int>> g(n+1,vector<int>(n+1,INF));
    
    for(int i=0;i<n;i++){
        int w;
        cin>>w;
        g[n][i]=w;
        g[i][n]=w;
    }

    for(int i=0;i<e;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u][v]=w;
        g[v][u]=w;
    }
    
    Prim(g);
    return 0;
}