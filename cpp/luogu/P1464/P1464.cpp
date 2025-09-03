#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll mem[22][22][22];
ll w(ll a,ll b,ll c){
    if(a<=0||b<=0||c<=0){
        mem[0][0][0]=1;
        return 1;
    }
    else if(a>20||b>20||c>20){
        mem[20][20][20]=w(20,20,20);
        return mem[20][20][20];
    }
    if(mem[a][b][c]) return mem[a][b][c];
    else if(a<b&&b<c){
        mem[a][b][c]= w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c);
        return mem[a][b][c];
    }
    else{
        mem[a][b][c]= w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
        return mem[a][b][c];
    }
}

int main(){
//   freopen("P1464_1.in","r",stdin);
    ll a,b,c,ans;
    while(~scanf("%lld%lld%lld",&a,&b,&c)){
        if(a==-1&&b==-1&&c==-1) break;
        ans=w(a,b,c);
        printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,ans);
    }
    return 0;
}