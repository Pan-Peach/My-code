#include<bits/stdc++.h>
using namespace std;
const int maxn=1000000;

class DSU{
    private:
        int pa[maxn];
    public:
        DSU(){
            for(int i=1;i<=maxn;i++){
                pa[i]=i;
            }
        }

        int find(int x){
            if(x==pa[x]) return x;
            return pa[x]=find(pa[x]);
        }

        void unite(int x,int y){
            x=find(x);y=find(y);
            pa[x]=y;
            return;
        }
}dsu;

int main(){
    int n,m,z,x,y;
    cin>>n>>m;

    for(int i=0;i<m;i++){
        cin>>z>>x>>y;
        if(z==1){
            dsu.unite(x,y);
        }
        else if(z==2){
            if(dsu.find(x)==dsu.find(y)){
                cout<<"Y";
            }
            else cout<<"N";
            if(i<m) cout<<'\n';
        }
    }

    return 0;
}