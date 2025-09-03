#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
const int MOD=998244353;
const int size=1000005;
int popcnt_table[size];
bool vis[size];

void precount(){
    for(int i=1;i<size;i++){
        if(vis[i]){
            continue;
        }
        if(__builtin_popcount(i)&1){
            for(ll j=i;j<size;j<<=1){
                popcnt_table[j]=-1;
                vis[j]=1;
            }
        }
        else{
            for(ll j=i;j<size;j<<=1){
                popcnt_table[j]=1;
                vis[j]=1;
            }
        }
        
    }
    return;
}

ll popcnt(ll x) {
    if(x<size){
        return popcnt_table[x];
    }
    return __builtin_popcountll(x)&1?-1:1;
}

ll fastpow(ll a, ll b) {
    a%=MOD;
    if(b==0){
        return 1;
    }
    if(a==0){
        return 0;
    }
    ll res = 1;
    while (b) {
        if (b & 1) res = ((res%MOD) * (a % MOD))%MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res%MOD;
}

ll func(ll l,ll r,ll x,ll k){
    ll ans=0;
    if(k==0){
        for(ll i=l;i<=r;i++){
            ans=(ans+popcnt(i))%MOD;
        }
        return ans;
    }
    if(k==1){
        for(ll i=l;i<=r;i++){
            ll left=popcnt(i);
            ll right=(i+x)%MOD;
            ans=((left*right)%MOD+ans)%MOD;
        }
        return ans%MOD;
    }
    for(ll i=l;i<=r;i++){
        ll left=popcnt(i);
        ll right=(i+x)%MOD;
        right=fastpow(right,k);
        ans=((left*right)%MOD+ans)%MOD;
    }
    return ans%MOD;
}


int main(){
    popcnt_table[0]=1;
    vis[0]=1;
    precount();
    ll n,x,k;
    cin>>n>>x>>k;
    cout<<func(0,n,x,k);
    return 0;
}