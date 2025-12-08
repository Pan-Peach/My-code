#include<bits/stdc++.h>
using namespace std;

class UnionSet{
public:
    vector<int> pa,head;

    UnionSet(int n){
        pa.resize(n+1);
        head.resize(n+1);
        for(int i=0;i<=n;i++){
            pa[i]=i;
            head[i]=i;
        }
    }

    void merge(int a, int b){
        int ra=find(a);
        int rb=find(b);
        pa[rb]=ra;
        head[rb]=head[ra];
        return;
    }

    int find(int a){
        if(pa[a]!=a) pa[a] = find(pa[a]);
        return pa[a];
    }
};

int main(){
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int n,m;
        cin>>n>>m;
        UnionSet us(n);
        for(int j=0;j<m;j++){
            int a,b;
            cin>>a>>b;
            us.merge(b,a);
        }
        for(int k=1;k<=n;k++){
            cout<<us.head[us.pa[k]]<<" ";
        }
        cout<<endl;
    }

    return 0;
}