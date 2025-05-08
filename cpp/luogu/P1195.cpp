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
        int root=x;
        while(pa[root]!=root){
            root=pa[root];
        }
        while(pa[x]!=root){
            int t=pa[x];
            pa[x]=root;
            x=t;
        }
        return root;
    }

    void unite(int x,int y){
        x=find(x);
        y=find(y);
        if(x!=y){
            pa[x]=y;
        }
    }
};


int Kruskal(vector<pair<int,pair<int,int>>> &edges,DSU &dsu ,int n,int k){
   int ans=0;
   for(auto edge:edges){
        if(n<=k){
            break;
        }
        int x=edge.second.first;
        int y=edge.second.second;
        int z=edge.first;
        if(dsu.find(x)!=dsu.find(y)){
            dsu.unite(x,y);
            ans+=z;
            n--;
        }
   } 
    if(n>k){
         return -1;
    }
    else{
        return ans;
    }
    return -1;
}

int main(){
    int n,m,k;
    cin>>n>>m>>k;
    DSU dsu(n);
    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,{u,v}});
    }
    if(k>n||m<n-k){
        cout<<"No Answer"<<endl;
        return 0;
    }
    sort(edges.begin(),edges.end());
    int ans=Kruskal(edges,dsu,n,k);
    if(ans==-1){
        cout<<"No Answer"<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}