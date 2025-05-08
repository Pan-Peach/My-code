#include<bits/stdc++.h>
using namespace std;
const int INF=12043022;

class house{
public:
    class point{
    public:
        int a,k;
        point():a(0),k(0){}
        point(int a,int k):a(a),k(k){}
    };

    vector<pair<point,vector<int>>> line;
    int n,ans=0;

    house(int num){
        n=num;
        line.resize(n+1);
    }

    void read(){
        for(int i=1;i<=n;i++){
            scanf("%d",&line[i].first.a);
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&line[i].first.k);
        }
    }

    void init(){
        vector<int> dp(n+1,INF);
        dp[1]=0;
/*        for(int i=1;i<=n;i++){
            int k=line[i].first.k;
            for(int j=i+1;j<=min(i+k,n);j++){
                int to=j-line[j].first.a;
                if(to>0&&to!=i){
                    line[to].second.push_back(i);
                    dp[to]=min(dp[to],dp[i]+1);
                }
            }
        }
            */
        queue<int> q;
        q.push(1);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            int k=line[u].first.k;
            for(int j=u+1;j<=min(u+k,n);j++){
                int to=j-line[j].first.a;
                if(to>0&&to!=u&&dp[to]==INF){
                    dp[to]=min(dp[to],dp[u]+1);
                    q.push(to);
                    if(to==n) break;
                }   
            }
        }
        ans=dp[n];
        return;
    }
};

int bfs(house& house){
    int n=house.n;
    queue<int> q;
    vector<int> dp(house.n+1,INF);
    vector<bool> flag(n+1,0);
    dp[n]=0;
    q.push(house.n);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto it:house.line[u].second){
            dp[it]=min(dp[it],dp[u]+1);
            if(flag[it]){
                continue;
            }
            q.push(it);
            flag[it]=1;
        }
    }

    return dp[1];
}

int main(){
    int n;
    scanf("%d",&n);
    house house(n);
    house.read();
    house.init();
    int ans=house.ans;
    if(ans==INF) printf("-1");

    else printf("%d",ans);
    return 0;
}