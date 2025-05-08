#include<bits/stdc++.h>
using namespace std;
const int maxn=100002;
int high[maxn];int n;

int lis(){
    int d[maxn];int len=0;
    memset(d,0xff,sizeof d);
    d[0]=high[0];
    for(int i=1;i<n;i++){
        if(high[i]>d[len]){
            d[++len]=high[i];
        }
        else{
            int* t=lower_bound(d,d+len,high[i]);
            (*t)=high[i];
        }
    }
    return len+1;
}

int sis(){
    int d[maxn];int len=0;
    memset(d,0x3f,sizeof d);
    d[0]=high[0];
    for(int i=1;i<n;i++){
        if(high[i]<=d[len]){
            d[++len]=high[i];
        }
        else{
            int t=upper_bound(d,d+len,high[i],greater<int>())-d;
            d[t]=high[i];
        }
    }
    return len+1;
}

int main(){
//  freopen("P1020_11.in","r",stdin);
//  freopen("P1020.out","w",stdout);
    while(~scanf("%d",&high[n++]));
    n--;
    cout<<sis()<<'\n'<<lis();
    return 0;
}