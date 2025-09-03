#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,c,ans,a[1001],sum[1000];

void dfs(ll index,ll x){
    ans=max(ans,x);
    if(index==0) return;
    if(x+sum[index]<=c){
        ans=max(ans,x+sum[index]);
        return;
    } 
    if(x+a[index]<=c){
        dfs(index-1,x+a[index]);
    }
    dfs(index-1,x);
}

int main(){
    cin>>n>>c;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    } 
    dfs(n,0);
    cout<<ans;
    return 0;
}