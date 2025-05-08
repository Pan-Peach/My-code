#include<bits/stdc++.h>
using namespace std;
const int size=100001;
#define DEBU

long long data[size];

long long query(int l,int r){
    long long sum=0;
    for(int i=l;i<=r;i++){
        sum+=data[i];
    }
    return sum;
}

void add(int l,int r,int val){
    for(int i=l;i<=r;i++){
        data[i]+=val;
    }
    return;
}

int main(){
    #ifdef DEBU
    freopen("P3372_19.in","r",stdin);
    #endif
    int n,m;
    scanf("%d%d",&n,&m);
    
    for(int i=1;i<=n;i++){
        scanf("%lld",&data[i]);
    }
    printf("%lld\n",query(50001,100000));
    printf("%lld\n",query(1,100000));
    for(int i=0;i<m;i++){
        int op;
        scanf("%d",&op);
        if(op==1){
            int l,r,val;
            scanf("%d%d%d",&l,&r,&val);
            add(l,r,val);
        }
        else if(op==2){
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%lld\n",query(l,r));
        }
        else{}
    }
    return 0;

}
