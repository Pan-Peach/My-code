#include<bits/stdc++.h>
using namespace std;

class item{
public:
    int v,p;
    item(): v(0),p(0){}
};

int main(){
    int n,m;
    cin>>n>>m;
    vector<item> list(m+1);
    for(int i=1;i<=m;i++){
        cin>>list[i].v>>list[i].p;
    }
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    for(int i=1;i<=m;i++){
        int v=list[i].v,p=list[i].p;
        for(int j=1;j<=n;j++){
            if(v<=j){
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-v]+v*p);
            }
            else{
                dp[i][j]=dp[i-1][j];
            }
        }
    }
    cout<<dp[m][n];
    return 0;
}