#include<bits/stdc++.h>
using namespace std;

int min(int a,int b){
    if(a>b) return b;
    return a;
}

int main(){
    int n,w,dp[110000],a[10100];
    memset(dp,0x3f3f,sizeof dp);
    dp[0]=0;
    cin>>n>>w;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=1;i<=w+4;i++){
        for(int j=0;j<n;j++){
            if(i>=a[j]){      
                dp[i]=min(dp[i],dp[i-a[j]]+1);
            }
        }
    }
    cout<<dp[w];
    return 0;
}