#include<bits/stdc++.h>
using namespace std;

int main(){
    int v,n;
    cin>>v>>n;
    vector<int> dp(v+1,0);
    vector<int> vol(n);
    for(int i=0;i<n;i++){
        int vl;
        cin>>vl;
        vol[i]=vl;
    }
    for(int i=0;i<n;i++){
        for(int j=v;j>=0;j--){
            if(j>=vol[i]) dp[j]=max(dp[j],dp[j-vol[i]]+vol[i]);
        }
    }
    int ans=0;
    
    cout<<v-dp[v];
    return 0;
}