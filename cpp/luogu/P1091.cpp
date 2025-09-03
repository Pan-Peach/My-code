#include<iostream>
using namespace std;

const int maxn=111;
int high[maxn],ans=maxn,n,dpz[maxn],dpf[maxn],cnt=0;

/*void quchong(){
    for(int i=0;i<n-1;i++){
        int tmp=high[i];
        for(int j=i+1;j<n;j++){
            if(high[j]==tmp && tmp !=1){
                high[j]=1;
                cnt++;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(high[i]==1){
            high[i]=high[i+1];
            high[i+1]=1;
        }
    }
}*/

void initialize(){
    for(int i=0;i<n;i++){
        dpz[i]=1;dpf[i]=1;
    }
}

void dp(){
    for(int i=1;i<n;i++){
        int max=0;
        for(int j=0;j<i;j++){
            if(dpz[j]>=max && high[j]<high[i]){ dpz[i]=dpz[j]+1; max=dpz[j]; }
       }
    }
    for(int i=n-2;i>=0;i--){
        int max=0;
        for(int j=n-1;j>i;j--){
            if(dpf[j]>=max && high[j]<high[i]){ dpf[i]=dpf[j]+1; max=dpf[j]; }
        }
    }
}

void solve(){
    n-=cnt;
    initialize();
    dp();
    for(int i=0;i<n;i++){
        int tmp;
        tmp=n-dpz[i]-dpf[i]+1;
        if(ans>tmp) ans=tmp;
    }
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>high[i];
    solve();
    cout<<ans;
    return 0;
}