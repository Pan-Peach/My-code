#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int size=10000005;
const float eps=1e-6;
int popcnt_table[size];
bool vis[size];

void precount(){
    for(int i=1;i<size;i++){
        if(vis[i]){
            continue;
        }
        int cnt=__builtin_popcount(i);
        for(ll j=i;j<size;j<<=1){
            popcnt_table[j]=cnt;
            vis[j]=1;
        }
    }
    return;
}

ll popcnt(ll x) {
    if(x<size){
        return popcnt_table[x];
    }
    return __builtin_popcountll(x);
}

ll func(ll x,ll k){
    int x0=x;
    int cnt=popcnt(x);
    if(cnt==k) return 0;
    if(cnt>k){
        for(int i=0;i<=60;i++){
            if(x&(1LL<<i)){
                x^=(1LL<<i);
                cnt--;
                if(cnt==k) break;
            }
        }
    }
    else{
        for(int i=0;i<=60;i++){
            if(!(x&(1LL<<i))){
                x|=(1LL<<i);
                cnt++;
                if(cnt==k) break;
            }
        }
    }
    
    return abs(x0-x);
}

ll func2(ll x,ll k){
    ll ans=0,i=0;
    if(popcnt(x)==k) return 0;
    while(!ans){
        if(popcnt(x+i)==k){
            ans=i;
        }
        if(popcnt(x-i)==k){
            ans=i;
        }
        i++;
    }
    return ans;
}

int main(){
    ll t,x,k;
    cin>>t;
    popcnt_table[0]=0;
    vis[0]=1;
    precount();
    for(int i=0;i<t;i++){
        cin>>x>>k;
        int ans;
        if(abs(x-pow(2,k)-1)<=eps) ans=func(x,k);
        else ans=func2(x,k);
        cout<<ans<<'\n';
    }
    return 0;
}