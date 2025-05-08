#include<bits/stdc++.h>
using namespace std;
const  int INF=0x3f3f3f3f;
const int fl=-6677;

int SPFA(vector<vector<pair<int,int>>>& edge,int str,int end,int n){
    vector<int> dis(n+1,INF);
    dis[str]=0;
    vector<int> cnt(n+1,0);
    queue<int> q;

    q.push(str);
    cnt[str]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<edge[u].size();i++){
            int v=edge[u][i].first;
            int w=edge[u][i].second;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                cnt[v]++;
                if(cnt[v]>n){
                    return fl ;
                }
                q.push(v);
            }
        }
    }
    return dis[end];
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>> e(n+1);
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        e[a].push_back({b,-c});
    }
    int ans1=SPFA(e,1,n,n);
    int ans2=SPFA(e,n,1,n);
    if(ans1==fl||ans2==fl) cout<<"Forever love";
    else{
        cout<<min(ans1,ans2);
    }

    return 0;
}
