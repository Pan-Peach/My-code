#include<bits/stdc++.h>
using namespace std;

class EDGE{
    private:
        vector<vector<int>> D;
        vector<vector<int>> edge;
    public:
        void build(int n){
            edge.resize(n+1);
            for(int i=1;i<=n;i++){
                edge[i].resize(n+1);
                for(int j=1;j<=n;j++){
                    cin>>edge[i][j];
                }
            }
            return;
        }

        void floyd(int n){
            D.assign(edge.begin(),edge.end());
            for(int k=1;k<=n;k++){
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=n;j++){
                        D[i][j]=min(D[i][j],D[i][k]+D[k][j]);
                    }
                }
            }
            return;
        }

        int greed(const vector<int>& list){
            int ans=0;
            if(list.size()-1<=1) return 0;
            for(int i=1;i<list.size()-1;i++){
                ans+=D[list[i]][list[i+1]];
            }
            return ans;
        }
};

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> list(m+1);
    for(int i=1;i<=m;i++) cin>>list[i];
    EDGE edge;
    edge.build(n);
    edge.floyd(n);
    int ans=edge.greed(list);
    cout<<ans;
    return 0;
}