#include<bits/stdc++.h>
using namespace std;
const int money=40000;

int m,n,v;
int b[1001],c[1001],dp[1000][money];
vector<int> a[1006];

void dpp(){
    for(int j=1;j<=n;j++){
        sort(a[j].begin(),a[j].end(),greater<int>());                 
    }
    for(int i=1;i<=n;i++){        
        for(int j=0;j<money;j++){
            dp[i][j]=dp[i-1][j];
            int profit=0;
            for(int k=0;k<a[i].size();k++){
                if(j<b[i]+(k+1)*c[i]) break;
                profit+=a[i][k];
                dp[i][j]=max(dp[i][j],dp[i-1][j-b[i]-(k+1)*c[i]]+profit-b[i]-(k+1)*c[i]);

            }
        }
    }
}

int main(){
    cin>>n>>m>>v;
    for(int i=1;i<=n;i++) cin>>b[i]>>c[i];
    for(int i=1;i<=m;i++) {
        int val,t;
        cin>>val>>t;
        t++;
        a[t].push_back(val);
    }
    dpp();
    int cnt;
    for(int j=0;j<money;j++){
        if(dp[n][j]>=v){
            cout<<j;
            break;
        }
    }
    return 0;
}