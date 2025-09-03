#include<bits/stdc++.h>
using namespace std;

class DSU{
    public:
        vector<int> pa;

        DSU(int n){
            pa.resize(n+1);
            for(int i=0;i<=n;i++){
                pa[i] = i;
            }
        }

        int find(int x){
            if(pa[x] == x){
                return x;
            }
            return pa[x] = find(pa[x]);
        }

        void merge(int x, int y){
            pa[find(x)] = find(y);
        }
};



int main(){
    int n,m;
    cin>>n>>m;
    DSU dsu(n);
    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        edges.push_back({z,{x,y}});
    }
    sort(edges.begin(),edges.end());
    int ans = 0,nedge = 0;
    for(auto edge:edges){
        int x = edge.second.first;
        int y = edge.second.second;
        int z = edge.first;
        if(dsu.find(x) != dsu.find(y)){
            dsu.merge(x,y);
            ans += z;
            nedge++;
        }
    }
    if(nedge != n-1){
        cout<<"orz"<<endl;
        return 0;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}