#include<bits/stdc++.h>
using namespace std;

int m,n,p[5000],a[5000];

void sort(){
    for(int i=0;i<m-1;i++){
        int tmp1=p[i+1],tmp2=a[i+1];
        for(int j=i;j>=0;j--){
            if(tmp1<p[j]){
                p[j+1]=p[j];a[j+1]=a[j];
                p[j]=tmp1;a[j]=tmp2;
            }
            else{
                break;
            }
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++) cin>>p[i]>>a[i];
    sort();
    int tot=0,ans=0;
    for(int i=0;i<m;i++){
        if((n-tot)<a[i]){
            ans+=(n-tot)*p[i];
            tot+=(n-tot);
        }
        else{
            ans+=a[i]*p[i];
            tot+=a[i];
        }
        if(tot==n) break;
    }
    cout<<ans;
    return 0;
}