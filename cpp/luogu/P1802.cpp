#include<bits/stdc++.h>
using namespace std;
typedef int ll;
#define int long long


class Friend{
    public:
    int lose,win,use;
    Friend(int a, int b, int c){
        lose=a;
        win=b;
        use=c;
    }
};

int main(){
    int n,x;
    vector<Friend> f;
    cin>>n>>x;
    for(int i=0;i<n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        f.push_back(Friend(a,b,c));
    }
    vector<int> dp(x+1,0);
    for(int i=0;i<n;i++){
        for(int j=x;j>=0;j--){
            if(j>=f[i].use) dp[j]=max(dp[j]+f[i].lose,dp[j-f[i].use]+f[i].win);
            else dp[j]=dp[j]+f[i].lose;
        }
        
    }
    cout<<dp[x]*5;
    return 0;
}