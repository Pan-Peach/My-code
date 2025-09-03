#include<bits/stdc++.h>
using namespace std;

const int maxn=50000;
int high[maxn],dp[maxn],dp2[maxn];int ans1=0,ans2=0;
long long n;

int maxint(int x,int y){
    if(x>y) return x;
    return y;
}

void lis(){
    dp[1]=1;
    for(int i=2;i<=n;i++){
        int max=0;
        for(int j=1;j<i;j++){
            if(dp[j]>max&&high[i]>high[j]){
                max=dp[j];
            }
        }
        dp[i]=max+1;
        ans1=maxint(dp[i],ans1);
    }
    return;
}

void sis(){
    dp2[n]=1;
    for(int i=n-1;i>=1;i--){
        int max=0;
        for(int j=n;j>i;j--){
            if(dp2[j]>max&&high[i]>=high[j]) 
            max=dp2[j];
        }
        dp2[i]=max+1;
        ans2=maxint(dp2[i],ans2);
    }
}

int main(){
//    freopen("P1020_9.in","r",stdin);
//    freopen("P1020.out","w",stdout);
    dp[0]=1;
    while(~scanf("%d",&high[++n]));
    n--;
    lis();
    int ans=ans1;
    sis();
    cout<<ans2<<'\n'<<ans;
    return 0;
}