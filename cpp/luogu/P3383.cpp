#include<bits/stdc++.h>
using namespace std;
const int maxn=1e8+1;

bitset<maxn> sieve;
vector<int> prime;

void inisieve(){
    sieve.set();
    sieve[0]=sieve[1]=0;
    for(int i=2;i<=maxn;i++){
        if(sieve[i]) prime.push_back(i);
        for(int j:prime){
            if(i*j>maxn) break;
            sieve[i*j]=0;
            if(i%j==0) break;
        }
    }
    return;
}

int main(){
    int n,q,k;
    inisieve();
    scanf("%d%d",&n,&q);
    for(int i=0;i<q;i++){
        scanf("%d",&k);
        printf("%d\n",prime[k-1]);
    }

    return 0;
}