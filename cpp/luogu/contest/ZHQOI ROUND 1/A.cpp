#include<bits/stdc++.h>
using namespace std;

class DSU{
    public:
    vector<int> parent;

    DSU(int n){
        parent.resize(n);
        for(int i=0;i<=n;i++){
            parent[i]=i;
        }
    }

    int find(int x){
        return parent[x]==x?x:parent[x]=find(parent[x]);
    }

    void merge(int x,int y){
        parent[find(x)]=find(y);
    }
};

int Kruskal(vector<pair<int,int>>& edges,DSU& dsu,int n,map<pair<int,int>,int>& mp){
    sort(edges.begin(),edges.end());
    int nedge=0;
    
    for(auto edge:edges){
        if(dsu.find(edge.first)!=dsu.find(edge.second)){
            dsu.merge(edge.first,edge.second);
            mp[edge]=1;
            
            nedge++;
            if(nedge==n-1){
                break;
            }
        }
    }
    if(nedge!=n-1){
        return -1;
    }
    return nedge;
}

int main(){
    int n,m;
    cin>>n>>m;
    DSU dsu(n);
    vector<pair<int,int>> edges(n+1);
    map<pair<int,int>,int> mp;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        edges.push_back({u,v});
        mp[{u,v}]=0;
    }
    int cnt=Kruskal(edges,dsu,n,mp);
    if(cnt<=-1){
        cout<<cnt<<endl;
    }
    else{
        int chose=1;
        cout<<m-cnt+1<<"\n";
        for(auto it:mp){
            if(it.second==0){
                cout<<it.first.first<<' '<<it.first.second<<endl;
            }
            if(chose&&it.second==1){
                cout<<it.first.first<<' '<<it.first.second<<endl;
                chose--;
            }
        }
    }
    return 0;

}