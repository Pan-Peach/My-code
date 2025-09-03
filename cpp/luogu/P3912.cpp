#include<bits/stdc++.h>
using namespace std;

const int maxn=1e8;
vector<bool> sieve(maxn,true);

void inisieve(){
    sieve[1]=sieve[0]=false;
    int sq=sqrt(maxn);
    for(int i=2;i<sq+1;i++){
        if(sieve[i]){
            for(int j=i*i;j<=maxn;j+=i){
                sieve[j]=false;
            }
        }
    }
}

int main(){
    inisieve();
    int n,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        if(sieve[i]) ans++;
    }
    cout<<ans;
}
