#include<bits/stdc++.h>
using namespace std;

const int maxn=1e8+1;
bitset<maxn> sieve;

void inisieve(){
    sieve.set();
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
    int n,m,ans=0,l,r;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        cin>>l>>r;
        if(l<=r&&l>=1&&r<=m){
            for(int j=l;j<=r;j++){
                if(sieve[j]) ans++;
            }
            printf("%d\n",ans);
        }
        else printf("Crossing the line\n");
        ans=0;
    }

    return 0;
}